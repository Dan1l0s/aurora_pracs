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

#ifndef FEATURES_P_H
#define FEATURES_P_H

#include <QtCore/QObject>
#include <QtCore/QSize>

class QDBusInterface;
class QTimer;

class FeaturesIfacePrivate : public QObject
{
    Q_OBJECT

public:
    explicit FeaturesIfacePrivate(QObject *parent = nullptr);
    ~FeaturesIfacePrivate();

    bool available() const;

    QString osName() const;
    QString osVersion() const;
    QString deviceName() const;
    QString deviceModel() const;
    quint64 ramTotalSize() const;
    quint64 ramUsedSize() const;
    quint64 ramFreeSize() const;
    quint32 cpuClockSpeed() const;
    quint32 cpuCoresCount() const;
    quint32 batteryCharge() const;
    QSize screenResolution() const;
    qreal backCameraResolution() const;
    qreal frontCameraResolution() const;
    bool hasBluetooth() const;
    bool hasGNSS() const;
    bool hasWlan() const;
    bool hasNFC() const;

signals:
    void ramUsedSizeChanged(quint64 ramUsedSize);
    void ramFreeSizeChanged(quint64 ramFreeSize);
    void batteryChargeChanged(quint32 batteryCharge);

private slots:
    void updateAllData();
    void updateRamFreeSize();
    void updateBatteryCharge();

private:
    QTimer *m_timer { nullptr };
    QDBusInterface *m_iface { nullptr };

    QString m_osName { QStringLiteral("") };
    QString m_osVersion { QStringLiteral("") };
    QString m_deviceName { QStringLiteral("") };
    QString m_deviceModel { QStringLiteral("") };
    quint64 m_ramTotalSize { 0ull };
    quint64 m_ramUsedSize { 0ull };
    quint64 m_ramFreeSize { 0ull };
    quint32 m_cpuClockSpeed { 0u };
    quint32 m_cpuCoresCount { 0u };
    quint32 m_batteryCharge { 0u };
    QSize m_screenResolution {  };
    qreal m_backCameraResolution { 0.0 };
    qreal m_frontCameraResolution { 0.0 };
    bool m_hasBluetooth { false };
    bool m_hasGNSS { false };
    bool m_hasWlan { false };
    bool m_hasNFC { false };
};

#endif // FEATURES_P_H
