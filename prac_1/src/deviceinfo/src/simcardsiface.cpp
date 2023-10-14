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

#include <QtDBus/QDBusPendingReply>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusMetaType>
#include <QtDBus/QDBusConnectionInterface>

#include "simcardsiface_p.h"
#include "simcardsiface.h"

namespace {
    const QString DBUS_SERVICE = QStringLiteral("ru.omp.deviceinfo");
    const QString DBUS_PATH = QStringLiteral("/ru/omp/deviceinfo/SIM");
    const QString DBUS_IFACE = QStringLiteral("ru.omp.deviceinfo.SIM");
};

Q_DECLARE_METATYPE(QList<QVariantMap>)

SimCardsIfacePrivate::SimCardsIfacePrivate(QObject *parent)
    : QObject(parent)
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

    qDBusRegisterMetaType<QList<QVariantMap>>();

    updateAllData();

    m_iface->connection().connect(m_iface->service(), m_iface->path(), m_iface->interface(), "simCardsEnabledChanged",
                                  this, SLOT(updateSimCardsInfo(QList<QVariantMap>)));
    m_iface->connection().connect(m_iface->service(), m_iface->path(), m_iface->interface(), "preferredDataTransferSimChanged",
                                  this, SLOT(updateSimCardsInfo(QList<QVariantMap>)));
    m_iface->connection().connect(m_iface->service(), m_iface->path(), m_iface->interface(), "preferredVoiceCallSimChanged",
                                  this, SLOT(updateSimCardsInfo(QList<QVariantMap>)));
}

SimCardsIfacePrivate::~SimCardsIfacePrivate()
{
    delete m_iface;
}

bool SimCardsIfacePrivate::available() const
{
    return m_iface->connection().interface()->isServiceRegistered(DBUS_SERVICE).value();
}

qint32 SimCardsIfacePrivate::simCardsCount() const
{
    return m_simCardName.size();
}

qint32 SimCardsIfacePrivate::simCardIndex() const
{
    return m_simCardIndex;
}

QString SimCardsIfacePrivate::simCardName() const
{
    if (m_simCardIndex < 0 || m_simCardIndex >= m_simCardName.size())
        return QStringLiteral("");

    return m_simCardName.at(m_simCardIndex);
}

QString SimCardsIfacePrivate::operatorName() const
{
    if (m_simCardIndex < 0 || m_simCardIndex >= m_operatorName.size())
        return QStringLiteral("");

    return m_operatorName.at(m_simCardIndex);
}

bool SimCardsIfacePrivate::simCardEnabled() const
{
    if (m_simCardIndex < 0 || m_simCardIndex >= m_simCardEnabled.size())
        return false;

    return m_simCardEnabled.at(m_simCardIndex);
}

bool SimCardsIfacePrivate::preferredDataTransfer() const
{
    if (m_simCardIndex < 0 || m_simCardIndex >= m_preferredDataTransfer.size())
        return false;

    return m_preferredDataTransfer.at(m_simCardIndex);
}

bool SimCardsIfacePrivate::preferredVoiceCall() const
{
    if (m_simCardIndex < 0 || m_simCardIndex >= m_preferredVoiceCall.size())
        return false;

    return m_preferredVoiceCall.at(m_simCardIndex);
}

void SimCardsIfacePrivate::setSimCardIndex(qint32 simCardIndex)
{
    simCardIndex = m_simCardName.isEmpty() ? -1 : qBound(0, simCardIndex, m_simCardName.size() - 1);
    if (m_simCardIndex == simCardIndex)
        return;

    m_simCardIndex = simCardIndex;

    emit simCardIndexChanged(m_simCardIndex);
    emit simCardNameChanged(m_simCardName[m_simCardIndex]);
    emit operatorNameChanged(m_operatorName[m_simCardIndex]);
    emit simCardEnabledChanged(m_simCardEnabled[m_simCardIndex]);
    emit preferredDataTransferChanged(m_preferredDataTransfer[m_simCardIndex]);
    emit preferredVoiceCallChanged(m_preferredVoiceCall[m_simCardIndex]);
}

void SimCardsIfacePrivate::updateAllData()
{
    QDBusPendingReply<QList<QVariantMap>> simCardsInfoReply = m_iface->asyncCall(QStringLiteral("getSimCardsInfo"));
    updateSimCardsInfo(simCardsInfoReply.value());
}

void SimCardsIfacePrivate::updateSimCardsInfo(const QList<QVariantMap> &simCardsInfo)
{
    if (m_simCardName.size() != simCardsInfo.size()) {
        m_simCardName.resize(simCardsInfo.size());
        m_operatorName.resize(simCardsInfo.size());
        m_simCardEnabled.resize(simCardsInfo.size());
        m_preferredDataTransfer.resize(simCardsInfo.size());
        m_preferredVoiceCall.resize(simCardsInfo.size());

        emit simCardsCountChanged(simCardsInfo.size());
        setSimCardIndex(m_simCardIndex);
    }

    if (simCardsInfo.isEmpty()) {
        return;
    }
    const QVariantMap &simCardInfo = simCardsInfo.at(m_simCardIndex);

    const QString &simCardName = simCardInfo.value(QStringLiteral("simName")).value<QString>();
    if (m_simCardName.at(m_simCardIndex) != simCardName) {
        m_simCardName[m_simCardIndex] = simCardName;
        emit simCardNameChanged(simCardName);
    }

    const QString &operatorName = simCardInfo.value(QStringLiteral("operatorName")).value<QString>();
    if (m_operatorName.at(m_simCardIndex) != operatorName) {
        m_operatorName[m_simCardIndex] = operatorName;
        emit operatorNameChanged(operatorName);
    }

    const bool simCardEnabled = simCardInfo.value(QStringLiteral("enabled")).value<bool>();
    if (m_simCardEnabled.at(m_simCardIndex) != simCardEnabled) {
        m_simCardEnabled[m_simCardIndex] = simCardEnabled;
        emit simCardEnabledChanged(simCardEnabled);
    }

    const bool preferredDataTransfer = simCardInfo.value(QStringLiteral("preferredDataTransfer")).value<bool>();
    if (m_preferredDataTransfer.at(m_simCardIndex) != preferredDataTransfer) {
        m_preferredDataTransfer[m_simCardIndex] = preferredDataTransfer;
        emit preferredDataTransferChanged(preferredDataTransfer);
    }

    const bool preferredVoiceCall = simCardInfo.value(QStringLiteral("preferredVoiceCall")).value<bool>();
    if (m_preferredVoiceCall.at(m_simCardIndex) != preferredVoiceCall) {
        m_preferredVoiceCall[m_simCardIndex] = preferredVoiceCall;
        emit preferredVoiceCallChanged(preferredVoiceCall);
    }
}

SimCardsIface::SimCardsIface(QObject *parent)
    : QObject(parent), m_data(new SimCardsIfacePrivate(this))
{
    connect(m_data.data(), &SimCardsIfacePrivate::simCardsCountChanged,
            this, &SimCardsIface::simCardsCountChanged);
    connect(m_data.data(), &SimCardsIfacePrivate::simCardIndexChanged,
            this, &SimCardsIface::simCardIndexChanged);
    connect(m_data.data(), &SimCardsIfacePrivate::simCardNameChanged,
            this, &SimCardsIface::simCardNameChanged);
    connect(m_data.data(), &SimCardsIfacePrivate::operatorNameChanged,
            this, &SimCardsIface::operatorNameChanged);
    connect(m_data.data(), &SimCardsIfacePrivate::simCardEnabledChanged,
            this, &SimCardsIface::simCardEnabledChanged);
    connect(m_data.data(), &SimCardsIfacePrivate::preferredDataTransferChanged,
            this, &SimCardsIface::preferredDataTransferChanged);
    connect(m_data.data(), &SimCardsIfacePrivate::preferredVoiceCallChanged,
            this, &SimCardsIface::preferredVoiceCallChanged);
}

bool SimCardsIface::available() const
{
    return m_data->available();
}

qint32 SimCardsIface::simCardsCount() const
{
    return m_data->simCardsCount();
}

qint32 SimCardsIface::simCardIndex() const
{
    return m_data->simCardIndex();
}

QString SimCardsIface::simCardName() const
{
    return m_data->simCardName();
}

QString SimCardsIface::operatorName() const
{
    return m_data->operatorName();
}

bool SimCardsIface::simCardEnabled() const
{
    return m_data->simCardEnabled();
}

bool SimCardsIface::preferredDataTransfer() const
{
    return m_data->preferredDataTransfer();
}

bool SimCardsIface::preferredVoiceCall() const
{
    return m_data->preferredVoiceCall();
}

void SimCardsIface::setSimCardIndex(qint32 simCardIndex)
{
    m_data->setSimCardIndex(simCardIndex);
}
