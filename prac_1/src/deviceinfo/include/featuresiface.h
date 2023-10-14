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

#ifndef FEATURESIFACE_H
#define FEATURESIFACE_H

#include <QtCore/QObject>
#include <QtCore/QSharedPointer>
#include <QtCore/QString>
#include <QtCore/QSize>

class FeaturesIfacePrivate;

class FeaturesIface : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool available READ available CONSTANT)

    Q_PROPERTY(QString osName READ osName CONSTANT)
    Q_PROPERTY(QString osVersion READ osVersion CONSTANT)
    Q_PROPERTY(QString deviceName READ deviceName CONSTANT)
    Q_PROPERTY(QString deviceModel READ deviceModel CONSTANT)
    Q_PROPERTY(quint64 ramTotalSize READ ramTotalSize CONSTANT)
    Q_PROPERTY(quint64 ramUsedSize READ ramUsedSize NOTIFY ramUsedSizeChanged)
    Q_PROPERTY(quint64 ramFreeSize READ ramFreeSize NOTIFY ramFreeSizeChanged)
    Q_PROPERTY(quint32 cpuClockSpeed READ cpuClockSpeed CONSTANT)
    Q_PROPERTY(quint32 cpuCoresNumber READ cpuCoresNumber CONSTANT)
    Q_PROPERTY(quint32 batteryCharge READ batteryCharge NOTIFY batteryChargeChanged)
    Q_PROPERTY(QSize screenResolution READ screenResolution CONSTANT)
    Q_PROPERTY(qreal backCameraResolution READ backCameraResolution CONSTANT)
    Q_PROPERTY(qreal frontCameraResolution READ frontCameraResolution CONSTANT)
    Q_PROPERTY(bool hasBluetooth READ hasBluetooth CONSTANT)
    Q_PROPERTY(bool hasGnss READ hasGnss CONSTANT)
    Q_PROPERTY(bool hasWlan READ hasWlan CONSTANT)
    Q_PROPERTY(bool hasNfc READ hasNfc CONSTANT)

public:
    explicit FeaturesIface(QObject *parent = nullptr);
    ~FeaturesIface() override = default;

    bool available() const;

    QString osName() const;
    QString osVersion() const;
    QString deviceName() const;
    QString deviceModel() const;
    quint64 ramTotalSize() const;
    quint64 ramUsedSize() const;
    quint64 ramFreeSize() const;
    quint32 cpuClockSpeed() const;
    quint32 cpuCoresNumber() const;
    quint32 batteryCharge() const;
    QSize screenResolution() const;
    qreal backCameraResolution() const;
    qreal frontCameraResolution() const;
    bool hasBluetooth() const;
    bool hasGnss() const;
    bool hasWlan() const;
    bool hasNfc() const;

signals:
    void ramUsedSizeChanged(quint64 ramUsedSize);
    void ramFreeSizeChanged(quint64 ramFreeSize);
    void batteryChargeChanged(quint32 batteryCharge);

private:
    QSharedPointer<FeaturesIfacePrivate> m_data { nullptr };
};

#endif // FEATURESIFACE_H
