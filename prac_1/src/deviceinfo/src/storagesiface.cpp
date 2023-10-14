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

#include "storagesiface_p.h"
#include "storagesiface.h"

namespace {
    const QString DBUS_SERVICE = QStringLiteral("ru.omp.deviceinfo");
    const QString DBUS_PATH = QStringLiteral("/ru/omp/deviceinfo/Storages");
    const QString DBUS_IFACE = QStringLiteral("ru.omp.deviceinfo.Storages");
};

StoragesIfacePrivate::StoragesIfacePrivate(QObject *parent)
    : QObject(parent), m_timer(new QTimer(this))
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

    m_iface->connection().connect(m_iface->service(), m_iface->path(), m_iface->interface(), "externalStorageChanged",
                                  this, SLOT(updateExternalStorageInfo(QVariantMap)));

    connect(m_timer, &QTimer::timeout, this, [this]() {
        updateInternalStorageInfo();
        updateInternalUserPartitionInfo();
    });

    m_timer->start(100);
}

StoragesIfacePrivate::~StoragesIfacePrivate()
{
    delete m_iface;
}

bool StoragesIfacePrivate::available() const
{
    return m_iface->connection().interface()->isServiceRegistered(DBUS_SERVICE).value();
}

bool StoragesIfacePrivate::extStorageMounted() const
{
    return m_extStorageMounted;
}

QString StoragesIfacePrivate::extStorageDeviceLabel() const
{
    return m_extStorageDeviceLabel;
}

quint32 StoragesIfacePrivate::extStoragePartitionsCount() const
{
    return m_extStoragePartitionsCount;
}

quint64 StoragesIfacePrivate::extStorageBytesTotal() const
{
    return m_extStorageBytesTotal;
}

quint64 StoragesIfacePrivate::extStorageBytesUsed() const
{
    return m_extStorageBytesUsed;
}

quint64 StoragesIfacePrivate::extStorageBytesFree() const
{
    return m_extStorageBytesFree;
}

QString StoragesIfacePrivate::intStorageDeviceLabel() const
{
    return m_intStorageDeviceLabel;
}

QString StoragesIfacePrivate::intStorageFileSystemType() const
{
    return m_intStorageFileSystemType;
}

quint64 StoragesIfacePrivate::intStorageBytesTotal() const
{
    return m_intStorageBytesTotal;
}

quint64 StoragesIfacePrivate::intStorageBytesUsed() const
{
    return m_intStorageBytesUsed;
}

quint64 StoragesIfacePrivate::intStorageBytesFree() const
{
    return m_intStorageBytesFree;
}

QString StoragesIfacePrivate::intUsrPartsDeviceLabel() const
{
    return m_intUsrPartsDeviceLabel;
}

QString StoragesIfacePrivate::intUsrPartsFileSystemType() const
{
    return m_intUsrPartsFileSystemType;
}

quint64 StoragesIfacePrivate::intUsrPartsBytesTotal() const
{
    return m_intUsrPartsBytesTotal;
}

quint64 StoragesIfacePrivate::intUsrPartsBytesUsed() const
{
    return m_intUsrPartsBytesUsed;
}

quint64 StoragesIfacePrivate::intUsrPartsBytesFree() const
{
    return m_intUsrPartsBytesFree;
}

void StoragesIfacePrivate::updateAllData()
{
    QDBusPendingReply<QVariantMap> externalStorageInfoReply = m_iface->asyncCall(QStringLiteral("getExternalStorageInfo"));
    updateExternalStorageInfo(externalStorageInfoReply.value());
    updateInternalStorageInfo();
    updateInternalUserPartitionInfo();
}

void StoragesIfacePrivate::updateExternalStorageInfo(const QVariantMap &externalStorageInfo)
{
    const bool extStorageMounted = externalStorageInfo.value(QStringLiteral("mounted")).value<bool>();
    if (m_extStorageMounted != extStorageMounted) {
        m_extStorageMounted = extStorageMounted;
        emit extStorageMountedChanged(m_extStorageMounted);
    }

    const QString extStorageDeviceLabel = externalStorageInfo.value(QStringLiteral("deviceLabel")).value<QString>();
    if (m_extStorageDeviceLabel != extStorageDeviceLabel) {
        m_extStorageDeviceLabel = extStorageDeviceLabel;
        emit extStorageDeviceLabelChanged(m_extStorageDeviceLabel);
    }

    const quint32 extStoragePartitionsCount = externalStorageInfo.value(QStringLiteral("countMountedPartitions")).value<quint32>();
    if (m_extStoragePartitionsCount != extStoragePartitionsCount) {
        m_extStoragePartitionsCount = extStoragePartitionsCount;
        emit extStoragePartitionsCountChanged(m_extStoragePartitionsCount);
    }

    const quint64 extStorageBytesTotal = externalStorageInfo.value(QStringLiteral("bytesTotal")).value<quint64>();
    if (m_extStorageBytesTotal != extStorageBytesTotal) {
        m_extStorageBytesTotal = extStorageBytesTotal;
        emit extStorageBytesTotalChanged(m_extStorageBytesTotal);
    }

    const quint64 extStorageBytesUsed = externalStorageInfo.value(QStringLiteral("bytesUsed")).value<quint64>();
    if (m_extStorageBytesUsed != extStorageBytesUsed) {
        m_extStorageBytesUsed = extStorageBytesUsed;
        emit extStorageBytesUsedChanged(m_extStorageBytesUsed);
    }

    const quint64 extStorageBytesFree = externalStorageInfo.value(QStringLiteral("bytesAvailable")).value<quint64>();
    if (m_extStorageBytesFree != extStorageBytesFree) {
        m_extStorageBytesFree = extStorageBytesFree;
        emit extStorageBytesFreeChanged(m_extStorageBytesFree);
    }
}

void StoragesIfacePrivate::updateInternalStorageInfo()
{
    const QDBusPendingReply<QVariantMap> reply = m_iface->asyncCall(QStringLiteral("getInternalStorageInfo"));
    const QVariantMap internalStorageInfo = reply.value();

    const QString intStorageDeviceLabel = internalStorageInfo.value(QStringLiteral("deviceLabel")).value<QString>();
    if (m_intStorageDeviceLabel != intStorageDeviceLabel) {
        m_intStorageDeviceLabel = intStorageDeviceLabel;
        emit intStorageDeviceLabelChanged(m_intStorageDeviceLabel);
    }

    const QString intStorageFileSystemType = internalStorageInfo.value(QStringLiteral("filesystemType")).value<QString>();
    if (m_intStorageFileSystemType != intStorageFileSystemType) {
        m_intStorageFileSystemType = intStorageFileSystemType;
        emit intStorageFileSystemTypeChanged(m_intStorageFileSystemType);
    }

    const quint64 intStorageBytesTotal = internalStorageInfo.value(QStringLiteral("bytesTotal")).value<quint64>();
    if (m_intStorageBytesTotal != intStorageBytesTotal) {
        m_intStorageBytesTotal = intStorageBytesTotal;
        emit intStorageBytesTotalChanged(m_intStorageBytesTotal);
    }

    const quint64 intStorageBytesUsed = internalStorageInfo.value(QStringLiteral("bytesUsed")).value<quint64>();
    if (m_intStorageBytesUsed != intStorageBytesUsed) {
        m_intStorageBytesUsed = intStorageBytesUsed;
        emit intStorageBytesUsedChanged(m_intStorageBytesUsed);
    }

    const quint64 intStorageBytesFree = internalStorageInfo.value(QStringLiteral("bytesAvailable")).value<quint64>();
    if (m_intStorageBytesFree != intStorageBytesFree) {
        m_intStorageBytesFree = intStorageBytesFree;
        emit intStorageBytesFreeChanged(m_intStorageBytesFree);
    }
}

void StoragesIfacePrivate::updateInternalUserPartitionInfo()
{
    const QDBusPendingReply<QVariantMap> reply = m_iface->asyncCall(QStringLiteral("getInternalUserPartitionInfo"));
    const QVariantMap internalUserPartitionInfo = reply.value();

    const QString intUsrPartsDeviceLabel = internalUserPartitionInfo.value(QStringLiteral("deviceLabel")).value<QString>();
    if (m_intUsrPartsDeviceLabel != intUsrPartsDeviceLabel) {
        m_intUsrPartsDeviceLabel = intUsrPartsDeviceLabel;
        emit intUsrPartsDeviceLabelChanged(m_intUsrPartsDeviceLabel);
    }

    const QString intUsrPartsFileSystemType = internalUserPartitionInfo.value(QStringLiteral("filesystemType")).value<QString>();
    if (m_intUsrPartsFileSystemType != intUsrPartsFileSystemType) {
        m_intUsrPartsFileSystemType = intUsrPartsFileSystemType;
        emit intUsrPartsFileSystemTypeChanged(m_intUsrPartsFileSystemType);
    }

    const quint64 intUsrPartsBytesTotal = internalUserPartitionInfo.value(QStringLiteral("bytesTotal")).value<quint64>();
    if (m_intUsrPartsBytesTotal != intUsrPartsBytesTotal) {
        m_intUsrPartsBytesTotal = intUsrPartsBytesTotal;
        emit intUsrPartsBytesTotalChanged(m_intUsrPartsBytesTotal);
    }

    const quint64 intUsrPartsBytesUsed = internalUserPartitionInfo.value(QStringLiteral("bytesUsed")).value<quint64>();
    if (m_intUsrPartsBytesUsed != intUsrPartsBytesUsed) {
        m_intUsrPartsBytesUsed = intUsrPartsBytesUsed;
        emit intUsrPartsBytesUsedChanged(m_intUsrPartsBytesUsed);
    }

    const quint64 intUsrPartsBytesFree = internalUserPartitionInfo.value(QStringLiteral("bytesAvailable")).value<quint64>();
    if (m_intUsrPartsBytesFree != intUsrPartsBytesFree) {
        m_intUsrPartsBytesFree = intUsrPartsBytesFree;
        emit intUsrPartsBytesFreeChanged(m_intUsrPartsBytesFree);
    }
}

StoragesIface::StoragesIface(QObject *parent)
    : QObject(parent), m_data(new StoragesIfacePrivate(this))
{
    connect(m_data.data(), &StoragesIfacePrivate::extStorageMountedChanged,
            this, &StoragesIface::extStorageMountedChanged);
    connect(m_data.data(), &StoragesIfacePrivate::extStorageDeviceLabelChanged,
            this, &StoragesIface::extStorageDeviceLabelChanged);
    connect(m_data.data(), &StoragesIfacePrivate::extStoragePartitionsCountChanged,
            this, &StoragesIface::extStoragePartitionsCountChanged);
    connect(m_data.data(), &StoragesIfacePrivate::extStorageBytesTotalChanged,
            this, &StoragesIface::extStorageBytesTotalChanged);
    connect(m_data.data(), &StoragesIfacePrivate::extStorageBytesUsedChanged,
            this, &StoragesIface::extStorageBytesUsedChanged);
    connect(m_data.data(), &StoragesIfacePrivate::extStorageBytesFreeChanged,
            this, &StoragesIface::extStorageBytesFreeChanged);

    connect(m_data.data(), &StoragesIfacePrivate::intStorageDeviceLabelChanged,
            this, &StoragesIface::intStorageDeviceLabelChanged);
    connect(m_data.data(), &StoragesIfacePrivate::intStorageFileSystemTypeChanged,
            this, &StoragesIface::intStorageFileSystemTypeChanged);
    connect(m_data.data(), &StoragesIfacePrivate::intStorageBytesTotalChanged,
            this, &StoragesIface::intStorageBytesTotalChanged);
    connect(m_data.data(), &StoragesIfacePrivate::intStorageBytesUsedChanged,
            this, &StoragesIface::intStorageBytesUsedChanged);
    connect(m_data.data(), &StoragesIfacePrivate::intStorageBytesFreeChanged,
            this, &StoragesIface::intStorageBytesFreeChanged);

    connect(m_data.data(), &StoragesIfacePrivate::intUsrPartsDeviceLabelChanged,
            this, &StoragesIface::intUsrPartsDeviceLabelChanged);
    connect(m_data.data(), &StoragesIfacePrivate::intUsrPartsFileSystemTypeChanged,
            this, &StoragesIface::intUsrPartsFileSystemTypeChanged);
    connect(m_data.data(), &StoragesIfacePrivate::intUsrPartsBytesTotalChanged,
            this, &StoragesIface::intUsrPartsBytesTotalChanged);
    connect(m_data.data(), &StoragesIfacePrivate::intUsrPartsBytesUsedChanged,
            this, &StoragesIface::intUsrPartsBytesUsedChanged);
    connect(m_data.data(), &StoragesIfacePrivate::intUsrPartsBytesFreeChanged,
            this, &StoragesIface::intUsrPartsBytesFreeChanged);
}

bool StoragesIface::available() const
{
    return m_data->available();
}

bool StoragesIface::extStorageMounted() const
{
    return m_data->extStorageMounted();
}

QString StoragesIface::extStorageDeviceLabel() const
{
    return m_data->extStorageDeviceLabel();
}

quint32 StoragesIface::extStoragePartitionsCount() const
{
    return m_data->extStoragePartitionsCount();
}

quint64 StoragesIface::extStorageBytesTotal() const
{
    return m_data->extStorageBytesTotal();
}

quint64 StoragesIface::extStorageBytesUsed() const
{
    return m_data->extStorageBytesUsed();
}

quint64 StoragesIface::extStorageBytesFree() const
{
    return m_data->extStorageBytesFree();
}

QString StoragesIface::intStorageDeviceLabel() const
{
    return m_data->intStorageDeviceLabel();
}

QString StoragesIface::intStorageFileSystemType() const
{
    return m_data->intStorageFileSystemType();
}

quint64 StoragesIface::intStorageBytesTotal() const
{
    return m_data->intStorageBytesTotal();
}

quint64 StoragesIface::intStorageBytesUsed() const
{
    return m_data->intStorageBytesUsed();
}

quint64 StoragesIface::intStorageBytesFree() const
{
    return m_data->intStorageBytesFree();
}

QString StoragesIface::intUsrPartsDeviceLabel() const
{
    return m_data->intUsrPartsDeviceLabel();
}

QString StoragesIface::intUsrPartsFileSystemType() const
{
    return m_data->intUsrPartsFileSystemType();
}

quint64 StoragesIface::intUsrPartsBytesTotal() const
{
    return m_data->intUsrPartsBytesTotal();
}

quint64 StoragesIface::intUsrPartsBytesUsed() const
{
    return m_data->intUsrPartsBytesUsed();
}

quint64 StoragesIface::intUsrPartsBytesFree() const
{
    return m_data->intUsrPartsBytesFree();
}
