/****************************************************************************
**
** Copyright (C) 2021 Open Mobile Platform LLC.
** Contact: https://community.omprussia.ru/open-source
**
** This file is part of the System Info project.
**
** $QT_BEGIN_LICENSE:BSD$
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of copyright holder nor the names of its contributors
**     may be used to endorse or promote products derived from this software
**     without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
** PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
** CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
** EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
** PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
** LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
** NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>
#include <QtDBus/QtDBus>

#include "cdbconstants.h"
#include "cdbtypes.h"
#include "cdbservice.h"
#include "cdbtechnology.h"
#include "cdbnetworkmanager.h"

CDBNetworkManager::CDBNetworkManager(QObject *parent)
    : QObject(parent), m_defaultService(nullptr),
      m_connectedWiFi(nullptr)
{
    qDBusRegisterMetaType<Service>();
    qDBusRegisterMetaType<ServiceList>();
    qDBusRegisterMetaType<QMap<QString, QVariant>>();
    qDBusRegisterMetaType<DBusObjectList>();

    queryDefaultRoute();
    queryTechnologies();

    QDBusInterface interface(CDBConstants::s_service,
                             CDBConstants::s_path,
                             CDBConstants::s_managerInterface,
                             QDBusConnection::systemBus());

    QDBusReply<QVariantMap> propertiesReply = interface.call(CDBConstants::s_methodGetProperties);
    if (propertiesReply.isValid())
        m_properties = propertiesReply.value();

    QDBusConnection systemBus = QDBusConnection::systemBus();
    systemBus.connect(CDBConstants::s_service,
                      CDBConstants::s_path,
                      CDBConstants::s_managerInterface,
                      CDBConstants::s_signalPropertyChanged,
                      this,
                      SLOT(onPropertyChanged(const QString&, const QDBusVariant&)));
    systemBus.connect(CDBConstants::s_service,
                      CDBConstants::s_path,
                      CDBConstants::s_managerInterface,
                      CDBConstants::s_signalServicesChanged,
                      this,
                      SLOT(onServicesChanged(const ServiceList&, const DBusObjectList&)));
    systemBus.connect(CDBConstants::s_service,
                      CDBConstants::s_path,
                      CDBConstants::s_managerInterface,
                      CDBConstants::s_signalTechnologyAdded,
                      this,
                      SLOT(onTechAdded(const QDBusObjectPath&, const QVariantMap&)));
    systemBus.connect(CDBConstants::s_service,
                      CDBConstants::s_path,
                      CDBConstants::s_managerInterface,
                      CDBConstants::s_signalTechnologyRemoved,
                      this,
                      SLOT(onTechRemoved(const QDBusObjectPath &path)));

    connect(this, &CDBNetworkManager::defaultRouteChanged, this, &CDBNetworkManager::queryDefaultRoute);
}

bool CDBNetworkManager::valid() const
{
    return !m_properties.isEmpty();
}

bool CDBNetworkManager::available() const
{
    auto dbusConnection = QDBusConnection::systemBus();
    return dbusConnection.interface()->isServiceRegistered(CDBConstants::s_service);
}

bool CDBNetworkManager::connected() const
{
    return m_defaultService != nullptr ? m_defaultService->connected() : false;
}

bool CDBNetworkManager::connecting() const
{
    // NOTE: https://github.com/sailfishos/libconnman-qt/blob/master/libconnman-qt/networkmanager.cpp#L1307
    return m_defaultService != nullptr ? m_defaultService->connecting() : false;
}

bool CDBNetworkManager::offlineMode() const
{
    return m_properties.value(QStringLiteral("OfflineMode")).toBool();
}

bool CDBNetworkManager::sessionMode() const
{
    return m_properties.value(QStringLiteral("SessionMode")).toBool();
}

QStringList CDBNetworkManager::technologies() const
{
    QStringList availableTech;
    for (const auto &tech : m_technologies.values())
        if (tech != nullptr && tech->getProperty(QStringLiteral("Powered")).toBool())
            availableTech << tech->name();

    return availableTech;
}

// WARNING: TBD?
//bool CDBNetworkManager::servicesEnabled() const
//{
//    return true;
//}

CDBService* CDBNetworkManager::defaultRoute() const
{
    return connected() && !m_defaultService.isNull() ? m_defaultService.data() : nullptr;
}

CDBService* CDBNetworkManager::connectedWifi() const
{
    return connected() && !m_connectedWiFi.isNull() ? m_connectedWiFi.data() : nullptr;
}

QString CDBNetworkManager::state() const
{
    return m_properties.value(QStringLiteral("State")).toString();
}

int CDBNetworkManager::inputRequestTimeout() const
{
    return m_properties.value(QStringLiteral("InputRequestTimeout")).toUInt();
}

QString CDBNetworkManager::stateToString(CDBNetworkManager::ManagerState state)
{
    switch (state)
    {
        case Idle: return "Idle";
        case Failure: return "Failure";
        case Association: return "Association";
        case Configuration: return "Configuration";
        case Ready: return "Ready";
        case Disconnect: return "Disconnect";
        case Online: return "Onlne";
        case Unknow: return "Unknow";
    }

    return {  };
}

CDBNetworkManager::ManagerState CDBNetworkManager::stringToState(const QString &state)
{
    if (state == QStringLiteral("idle"))
        return ManagerState::Idle;
    if (state == QStringLiteral("failure"))
        return ManagerState::Failure;
    if (state == QStringLiteral("association"))
        return ManagerState::Association;
    if (state == QStringLiteral("configuration"))
        return ManagerState::Configuration;
    if (state == QStringLiteral("ready"))
        return ManagerState::Ready;
    if (state == QStringLiteral("disconnect"))
        return ManagerState::Disconnect;
    if (state == QStringLiteral("online"))
        return ManagerState::Online;

    return ManagerState::Unknow;
}

void CDBNetworkManager::onPropertyChanged(const QString &name, const QDBusVariant &value)
{
    m_properties.insert(name, value.variant());

    CHECK_PROPERTY("State", state, name);
    CHECK_PROPERTY("InputRequestTimeout", inputRequestTimeout, name);
    CHECK_PROPERTY("OfflineMode", offlineMode, name);
    CHECK_PROPERTY("SessionMode", sessionMode, name);

    if (name == QStringLiteral("State"))
        queryDefaultRoute();
}

void CDBNetworkManager::onServicesChanged(const ServiceList &changed, const DBusObjectList &removed)
{
    for (const auto &service : changed)
        if (!m_defaultService.isNull() && service.first.path() == m_defaultService->serviceName()) {
            emit defaultRouteChanged(m_defaultService.data());
            emit connectedWifiChanged(m_connectedWiFi.data());
        }

    for (const auto &obj : removed)
        if (!m_defaultService.isNull() && obj.path() == m_defaultService->serviceName()) {
            m_defaultService.reset();
            emit defaultRouteChanged(m_defaultService.data());
            emit connectedWifiChanged(m_connectedWiFi.data());
        }
}

void CDBNetworkManager::queryDefaultRoute()
{
    auto stateString = m_properties.value(QStringLiteral("State")).toString();
    if (stateString != QStringLiteral("online"))
        return;

    QDBusInterface interface(CDBConstants::s_service,
                             CDBConstants::s_path,
                             CDBConstants::s_managerInterface,
                             QDBusConnection::systemBus());

    QDBusReply<ServiceList> reply = interface.call(CDBConstants::s_methodGetServices);
    if (!reply.isValid())
        return;

    auto defaultRouteName = CDBUtils::defaultRouteName();
    QString defaultServiceName;
    for (const auto &obj : reply.value()) {
        QDBusInterface interface(CDBConstants::s_service,
                                 obj.first.path(),
                                 CDBConstants::s_serviceInterface,
                                 QDBusConnection::systemBus());
        QDBusReply<QVariantMap> reply = interface.call(CDBConstants::s_methodGetProperties);
        if (!reply.isValid())
            continue;

        auto replyVariant = reply.value();

        if (replyVariant.value(QStringLiteral("State")).type() != QVariant::String
                && replyVariant.value(QStringLiteral("State")).toString() != QStringLiteral("online"))
            continue;

        auto techName = CDBUtils::techPathToName(obj.first.path());
        if (techName == QStringLiteral("wifi")) {
            if (m_connectedWiFi != nullptr && m_connectedWiFi->serviceName() != obj.first.path())
                m_connectedWiFi->deleteLater();

            m_connectedWiFi.reset(new CDBService(obj.first.path(), this));
            emit connectedWifiChanged(m_connectedWiFi.data());
        }

        if (replyVariant.value(QStringLiteral("Ethernet")).typeName() != QStringLiteral("QDBusArgument"))
            continue;

        const auto &entryArg = replyVariant.value(QStringLiteral("Ethernet")).value<QDBusArgument>();
        entryArg.beginMap();
        while (!entryArg.atEnd()) {
            QString name;
            QVariant val;
            entryArg.beginMapEntry();
            entryArg >> name >> val;
            entryArg.endMapEntry();

            if (name == QStringLiteral("Interface") && val.toString() == defaultRouteName)
                defaultServiceName = obj.first.path();
        }
        entryArg.endMap();

        if (!defaultServiceName.isEmpty())
            break;
    }

    if (!m_defaultService.isNull() && (m_defaultService->serviceName() == defaultServiceName))
        return;

    if (!defaultServiceName.isEmpty()) {
        m_defaultService.reset(new CDBService(defaultServiceName));

        connect(m_defaultService.data(), &CDBService::connectedChanged,
                this, &CDBNetworkManager::connectedChanged);
        connect(m_defaultService.data(), &CDBService::connectingChanged,
                this, &CDBNetworkManager::connectingChanged);

        if (m_defaultService != nullptr) {
            if (!m_defaultService->isDefault()) {
                m_defaultService->deleteLater();
            } else {
                emit defaultRouteChanged(m_defaultService.data());
                emit connectedChanged(connected());
                emit connectingChanged(connecting());
            }
        }
    }
}

void CDBNetworkManager::queryTechnologies()
{
    QDBusInterface interface(CDBConstants::s_service,
                             CDBConstants::s_path,
                             CDBConstants::s_managerInterface,
                             QDBusConnection::systemBus());

    QDBusReply<ServiceList> reply = interface.call(CDBConstants::s_methodGetTechnologies);
    QStringList availableTech;
    if (!reply.isValid())
        return;

    for (const auto &obj : reply.value()) {
        auto techName = obj.first.path();
        if (m_technologies.contains(techName))
            continue;

        auto *tech = new CDBTechnology(techName);
        if (tech->getProperty(QStringLiteral("Powered")).toBool())
            availableTech << tech->name();

        m_technologies.insert(techName, tech);
        connect(m_technologies.value(techName), &CDBTechnology::propertyChanged, this, [&](const QString &name) {
            if (name == QStringLiteral("Powered")) {
                QStringList availableTech;
                for (const auto &tech : m_technologies.values())
                    if (tech != nullptr && tech->getProperty(QStringLiteral("Powered")).toBool())
                        availableTech << tech->name();
                emit technologiesChanged(availableTech);
            }
        });
    }

    if (m_technologies.isEmpty())
        emit technologiesChanged(availableTech);
}

void CDBNetworkManager::onTechAdded(const QDBusObjectPath &path, const QVariantMap &prop)
{
    Q_UNUSED(path)
    Q_UNUSED(prop)
    queryTechnologies();
}

void CDBNetworkManager::onTechRemoved(const QDBusObjectPath &path)
{
    Q_UNUSED(path)
    queryTechnologies();
}
