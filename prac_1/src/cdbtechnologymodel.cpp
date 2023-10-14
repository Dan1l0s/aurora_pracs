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

#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>
#include <QtDBus/QtDBus>
#include <QTimer>

#include "cdbtypes.h"
#include "cdbutils.h"
#include "cdbconstants.h"
#include "cdbservice.h"
#include "cdbtechnologymodel.h"

CDBTechnologyModel::CDBTechnologyModel(QObject *parent)
    : QAbstractListModel(parent)
{
    qDBusRegisterMetaType<Service>();
    qDBusRegisterMetaType<ServiceList>();
    qDBusRegisterMetaType<QMap<QString, QVariant>>();
    qDBusRegisterMetaType<DBusObjectList>();

    QTimer::singleShot(0, this, &CDBTechnologyModel::init);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &CDBTechnologyModel::scanWifi);
    m_timer->setInterval(CDBConstants::s_wifiUpdateIntervalMsec);
}

int CDBTechnologyModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_cachedServices.size();
}

QVariant CDBTechnologyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() > m_cachedServices.size())
        return {  };

    auto *service = m_cachedServices.values().at(index.row());
    if (service == nullptr)
        return {  };

    switch (role) {
        case ServiceRole: return QVariant::fromValue(static_cast<QObject *>(service));
    }

    return {  };
}

QHash<int, QByteArray> CDBTechnologyModel::roleNames() const
{
    static const QHash<int, QByteArray> roles {
        {ServiceRole, "networlService"},
    };

    return roles;
}

QString CDBTechnologyModel::name() const
{
    return m_name;
}

bool CDBTechnologyModel::powered() const
{
    return m_powered;
}

bool CDBTechnologyModel::available() const
{
    return m_available;
}

void CDBTechnologyModel::init()
{
    auto dbusConnection = QDBusConnection::systemBus();
    m_available = dbusConnection.interface()->isServiceRegistered(CDBConstants::s_service);
    if (m_available)
        emit availableChanged(m_available);

    dbusConnection.connect(CDBConstants::s_service,
                           CDBConstants::s_techWiFiPath,
                           CDBConstants::s_technologyInterface,
                           CDBConstants::s_signalPropertyChanged,
                           this,
                           SLOT(onTechWiFiChanged(const QString &, const QDBusVariant &)));
    dbusConnection.connect(CDBConstants::s_service,
                           CDBConstants::s_path,
                           CDBConstants::s_managerInterface,
                           CDBConstants::s_signalPropertyChanged,
                           this,
                           SLOT(onServicesChanged(const ServiceList&, const DBusObjectList&)));

    QDBusInterface interface(CDBConstants::s_service,
                             CDBConstants::s_techWiFiPath,
                             CDBConstants::s_technologyInterface,
                             QDBusConnection::systemBus());
    QDBusReply<QVariantMap> reply = interface.call(CDBConstants::s_methodGetProperties);
    if (reply.isValid()) {
        auto poweredVal = reply.value().value(QStringLiteral("Powered"));
        if (poweredVal.isValid() && poweredVal.type() == QVariant::Bool) {
            m_powered = poweredVal.toBool();
            emit poweredChanged(m_powered);
            m_timer->start();
        }
    }

    requestScan();
}

void CDBTechnologyModel::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void CDBTechnologyModel::requestScan()
{
    // NOTE: We need only WiFi
    if (!m_powered)
        return;

    QDBusInterface interface(CDBConstants::s_service,
                             CDBConstants::s_path,
                             CDBConstants::s_managerInterface,
                             QDBusConnection::systemBus());
    QDBusReply<ServiceList> reply = interface.call(CDBConstants::s_methodGetServices);
    if (!reply.isValid())
        return;

    QStringList objectsList;
    for (const auto &obj : reply.value())
        objectsList << obj.first.path();

    for (const auto &serviceName : objectsList) {
        if (!m_cachedServices.contains(serviceName)) {

            QString techName;
            auto defaultServiceTechNameSplit = serviceName.split(QStringLiteral("/"));
            if (!defaultServiceTechNameSplit.isEmpty())
            techName = defaultServiceTechNameSplit.last().split(QStringLiteral("_")).first();
            if (techName != m_name)
                continue;

            beginInsertRows(QModelIndex(), m_cachedServices.size(), m_cachedServices.size());
            m_cachedServices.insert(serviceName, new CDBService(serviceName, this));
            endInsertRows();

            connect(m_cachedServices.value(serviceName), &CDBService::propertyUpdated, this, [this]() {
                if (sender() == nullptr)
                    return;

                auto service = qobject_cast<CDBService *>(sender());
                if (service == nullptr)
                    return;

                auto serviceIndex = m_cachedServices.values().indexOf(service);
                emit dataChanged(this->index(serviceIndex, 0), this->index(serviceIndex, 0));
            });
        }
    }

    for (const auto &name : m_cachedServices.keys()) {
        if (objectsList.contains(name))
            continue;

        auto removedIndex = m_cachedServices.keys().indexOf(name);
        beginRemoveRows(QModelIndex(), removedIndex, removedIndex);
        m_cachedServices.value(name)->deleteLater();
        m_cachedServices.remove(name);
        endRemoveRows();
    }

    for (const auto &service : m_cachedServices.values())
        if (service != nullptr)
            service->forceUpdate();
}

void CDBTechnologyModel::onTechWiFiChanged(const QString &name, const QDBusVariant &val)
{
    if (name != QStringLiteral("Powered"))
        return;

    if (val.variant().type() != QVariant::Bool || val.variant().toBool() == m_powered)
        return;

    m_powered = val.variant().toBool();
    emit poweredChanged(m_powered);

    if (m_powered) {
        requestScan();
        m_timer->start();
        return;
    }

    beginRemoveRows(QModelIndex(), 0, m_cachedServices.size());
    for (auto &service : m_cachedServices.values())
        service->deleteLater();
    m_cachedServices.clear();
    endRemoveRows();

    m_timer->stop();
}

void CDBTechnologyModel::onServicesChanged(const ServiceList &changed, const DBusObjectList &removed)
{
    if (!m_powered)
        return;

    auto keys = m_cachedServices.keys();
    for (const auto &obj : removed) {
        if (!keys.contains(obj.path()))
            continue;

        auto index = keys.indexOf(obj.path());
        beginRemoveColumns(QModelIndex(), index, index);
        m_cachedServices.take(obj.path())->deleteLater();
        endRemoveRows();
    }

    QStringList objectsList;
    for (const auto &obj : changed) {
        if (keys.contains(obj.first.path()))
            continue;

        QString techName = CDBUtils::techPathToName(obj.first.path());
        if (techName != m_name)
            continue;

        beginInsertRows(QModelIndex(), m_cachedServices.size(), m_cachedServices.size());
        m_cachedServices.insert(obj.first.path(), new CDBService(obj.first.path(), this));
        endInsertRows();

        connect(m_cachedServices.value(obj.first.path()), &CDBService::propertyUpdated, this, [this]() {
            if (sender() == nullptr)
                return;

            auto service = qobject_cast<CDBService *>(sender());

            if (service == nullptr)
                return;

            auto serviceIndex = m_cachedServices.values().indexOf(service);
            emit dataChanged(this->index(serviceIndex, 0), this->index(serviceIndex, 0));
        });
    }
}

void CDBTechnologyModel::scanWifi() const
{
    QDBusInterface interface(CDBConstants::s_service,
                             CDBConstants::s_techWiFiPath,
                             CDBConstants::s_technologyInterface,
                             QDBusConnection::systemBus());
    interface.asyncCall(QStringLiteral("Scan"));
}
