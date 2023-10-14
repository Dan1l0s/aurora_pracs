/*******************************************************************************
**
** Copyright (C) 2022 Open Mobile Platform LLC.
** Contact: https://community.omprussia.ru/open-source
**
** This file is part of the Aurora OS Application Template project.
**
** Redistribution and use in source and binary forms,
** with or without modification, are permitted provided
** that the following conditions are met:
**
** * Redistributions of source code must retain the above copyright notice,
**   this list of conditions and the following disclaimer.
** * Redistributions in binary form must reproduce the above copyright notice,
**   this list of conditions and the following disclaimer
**   in the documentation and/or other materials provided with the distribution.
** * Neither the name of the copyright holder nor the names of its contributors
**   may be used to endorse or promote products derived from this software
**   without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
** THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
** FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
** OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
** EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
*******************************************************************************/

#include <QtCore/QTimer>
#include <QtDBus/QDBusPendingReply>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusConnectionInterface>

#include "featuresiface_p.h"
#include "featuresiface.h"

namespace {
    const QString DBUS_SERVICE = QStringLiteral("ru.omp.deviceinfo");
    const QString DBUS_PATH = QStringLiteral("/ru/omp/deviceinfo/Features");
    const QString DBUS_IFACE = QStringLiteral("ru.omp.deviceinfo.Features");
};

FeaturesIfacePrivate::FeaturesIfacePrivate(QObject *parent)
    : QObject(parent), m_timer(new QTimer(this)),
      m_iface()
{
    m_iface = new QDBusInterface(DBUS_SERVICE, DBUS_PATH, DBUS_IFACE, QDBusConnection::systemBus(), this);
    if (!m_iface->isValid()) {
        delete m_iface;
        // before Aurora OS 4.1.0:
        m_iface = new QDBusInterface(DBUS_SERVICE, DBUS_PATH, DBUS_IFACE, QDBusConnection::sessionBus(), this);
    }
    if (!m_iface->isValid()) {
        return;
    }

    updateAllData();

    connect(m_timer, &QTimer::timeout, this, [this]() {
        updateRamFreeSize();
        updateBatteryCharge();
    });

    m_timer->start(100);
}

FeaturesIfacePrivate::~FeaturesIfacePrivate()
{
    delete m_iface;
}

bool FeaturesIfacePrivate::available() const
{
    return m_iface->connection().interface()->isServiceRegistered(DBUS_SERVICE).value();
}

QString FeaturesIfacePrivate::osName() const
{
    return m_osName;
}

QString FeaturesIfacePrivate::osVersion() const
{
    return m_osVersion;
}

QString FeaturesIfacePrivate::deviceName() const
{
    return m_deviceName;
}

QString FeaturesIfacePrivate::deviceModel() const
{
    return m_deviceModel;
}

quint64 FeaturesIfacePrivate::ramTotalSize() const
{
    return m_ramTotalSize;
}

quint64 FeaturesIfacePrivate::ramUsedSize() const
{
    return m_ramUsedSize;
}

quint64 FeaturesIfacePrivate::ramFreeSize() const
{
    return m_ramFreeSize;
}

quint32 FeaturesIfacePrivate::cpuClockSpeed() const
{
    return m_cpuClockSpeed;
}

quint32 FeaturesIfacePrivate::cpuCoresCount() const
{
    return m_cpuCoresCount;
}

quint32 FeaturesIfacePrivate::batteryCharge() const
{
    return m_batteryCharge;
}

QSize FeaturesIfacePrivate::screenResolution() const
{
    return m_screenResolution;
}

qreal FeaturesIfacePrivate::backCameraResolution() const
{
    return m_backCameraResolution;
}

qreal FeaturesIfacePrivate::frontCameraResolution() const
{
    return m_frontCameraResolution;
}

bool FeaturesIfacePrivate::hasBluetooth() const
{
    return m_hasBluetooth;
}

bool FeaturesIfacePrivate::hasGNSS() const
{
    return m_hasGNSS;
}

bool FeaturesIfacePrivate::hasWlan() const
{
    return m_hasWlan;
}

bool FeaturesIfacePrivate::hasNFC() const
{
    return m_hasNFC;
}

void FeaturesIfacePrivate::updateAllData()
{
    QDBusPendingReply<QString> osInfoReply = m_iface->asyncCall(QStringLiteral("getOsVersion"));
    const QStringList osInfoParts = osInfoReply.value().split(QStringLiteral(" "));
    if (osInfoParts.empty()) {
        m_osName = QStringLiteral("");
        m_osVersion = QStringLiteral("");
    } else {
        m_osName = osInfoParts.first();
        m_osVersion = osInfoParts.last();
    }

    QDBusPendingReply<QString> deviceInfoReply = m_iface->asyncCall(QStringLiteral("getDeviceModel"));
    const QStringList deviceInfoParts = deviceInfoReply.value().split(QStringLiteral(" "));
    if (deviceInfoParts.empty()) {
        m_deviceName = QStringLiteral("");
        m_deviceModel = QStringLiteral("");
    } else {
        m_deviceName = deviceInfoParts.first();
        m_deviceModel = deviceInfoParts.last();
    }

    QDBusPendingReply<quint64> ramTotalSizeReply = m_iface->asyncCall(QStringLiteral("getRamTotalSize"));
    m_ramTotalSize = ramTotalSizeReply.value();

    QDBusPendingReply<quint64> ramFreeSizeReply = m_iface->asyncCall(QStringLiteral("getRamFreeSize"));
    m_ramFreeSize = ramFreeSizeReply.value();
    m_ramUsedSize = m_ramTotalSize - m_ramFreeSize;

    QDBusPendingReply<quint32> cpuClockSpeedReply = m_iface->asyncCall(QStringLiteral("getMaxCpuClockSpeed"));
    m_cpuClockSpeed = cpuClockSpeedReply.value();

    QDBusPendingReply<quint32> cpuCoresCountReply = m_iface->asyncCall(QStringLiteral("getNumberCpuCores"));
    m_cpuCoresCount = cpuCoresCountReply.value();

    QDBusPendingReply<quint32> batteryChargeReply = m_iface->asyncCall(QStringLiteral("getBatteryChargePercentage"));
    m_batteryCharge = batteryChargeReply.value();

    QDBusPendingReply<QString> screenResolutionReply = m_iface->asyncCall(QStringLiteral("getScreenResolution"));
    const QStringList sizeParts = screenResolutionReply.value().split(QStringLiteral("x"));
    m_screenResolution = sizeParts.size() != 2 ? QSize() : QSize(sizeParts.first().toInt(), sizeParts.last().toInt());

    QDBusPendingReply<double> backCameraResolutionReply = m_iface->asyncCall(QStringLiteral("getMainCameraResolution"));
    m_backCameraResolution = static_cast<qreal>(backCameraResolutionReply.value());

    QDBusPendingReply<double> frontCameraResolutionReply = m_iface->asyncCall(QStringLiteral("getFrontalCameraResolution"));
    m_frontCameraResolution = static_cast<qreal>(frontCameraResolutionReply.value());

    QDBusPendingReply<bool> hasBluetoothReply = m_iface->asyncCall(QStringLiteral("hasBluetooth"));
    m_hasBluetooth = hasBluetoothReply.value();

    QDBusPendingReply<bool> hasGNSSReply = m_iface->asyncCall(QStringLiteral("hasGNSS"));
    m_hasGNSS = hasGNSSReply.value();

    QDBusPendingReply<bool> hasWlanReply = m_iface->asyncCall(QStringLiteral("hasWlan"));
    m_hasWlan = hasWlanReply.value();

    QDBusPendingReply<bool> hasNFCReply = m_iface->asyncCall(QStringLiteral("hasNFC"));
    m_hasNFC = hasNFCReply.value();
}

void FeaturesIfacePrivate::updateRamFreeSize()
{
    QDBusPendingReply<quint64> ramFreeSizeReply = m_iface->asyncCall(QStringLiteral("getRamFreeSize"));
    if (m_ramFreeSize != ramFreeSizeReply.value()) {
        m_ramFreeSize = ramFreeSizeReply.value();
        m_ramUsedSize = m_ramTotalSize - m_ramFreeSize;
        emit ramUsedSizeChanged(m_ramUsedSize);
        emit ramFreeSizeChanged(m_ramFreeSize);
    }
}

void FeaturesIfacePrivate::updateBatteryCharge()
{
    QDBusPendingReply<quint32> batteryChargeReply = m_iface->asyncCall(QStringLiteral("getBatteryChargePercentage"));
    if (m_batteryCharge != batteryChargeReply.value()) {
        m_batteryCharge = batteryChargeReply.value();
        emit batteryChargeChanged(m_batteryCharge);
    }
}

FeaturesIface::FeaturesIface(QObject *parent)
    : QObject(parent), m_data(new FeaturesIfacePrivate(this))
{
    connect(m_data.data(), &FeaturesIfacePrivate::ramUsedSizeChanged,
            this, &FeaturesIface::ramUsedSizeChanged);
    connect(m_data.data(), &FeaturesIfacePrivate::ramFreeSizeChanged,
            this, &FeaturesIface::ramFreeSizeChanged);
    connect(m_data.data(), &FeaturesIfacePrivate::batteryChargeChanged,
            this, &FeaturesIface::batteryChargeChanged);
}

bool FeaturesIface::available() const
{
    return m_data->available();
}

QString FeaturesIface::osName() const
{
    return m_data->osName();
}

QString FeaturesIface::osVersion() const
{
    return m_data->osVersion();
}

QString FeaturesIface::deviceName() const
{
    return m_data->deviceName();
}

QString FeaturesIface::deviceModel() const
{
    return m_data->deviceModel();
}

quint64 FeaturesIface::ramTotalSize() const
{
    return m_data->ramTotalSize();
}

quint64 FeaturesIface::ramUsedSize() const
{
    return m_data->ramUsedSize();
}

quint64 FeaturesIface::ramFreeSize() const
{
    return m_data->ramFreeSize();
}

quint32 FeaturesIface::cpuClockSpeed() const
{
    return m_data->cpuClockSpeed();
}

quint32 FeaturesIface::cpuCoresNumber() const
{
    return m_data->cpuCoresCount();
}

quint32 FeaturesIface::batteryCharge() const
{
    return m_data->batteryCharge();
}

QSize FeaturesIface::screenResolution() const
{
    return m_data->screenResolution();
}

qreal FeaturesIface::backCameraResolution() const
{
    return m_data->backCameraResolution();
}

qreal FeaturesIface::frontCameraResolution() const
{
    return m_data->frontCameraResolution();
}

bool FeaturesIface::hasBluetooth() const
{
    return m_data->hasBluetooth();
}

bool FeaturesIface::hasGnss() const
{
    return m_data->hasGNSS();
}

bool FeaturesIface::hasWlan() const
{
    return m_data->hasWlan();
}

bool FeaturesIface::hasNfc() const
{
    return m_data->hasNFC();
}
