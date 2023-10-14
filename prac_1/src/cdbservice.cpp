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

#include "cdbtypes.h"
#include "cdbutils.h"
#include "cdbconstants.h"
#include "cdbservice.h"

CDBService::CDBService(QObject *parent)
    : QObject(parent)
{  }

CDBService::CDBService(const QString &name, QObject *parent)
    : QObject(parent), m_name(name),
      m_isDefault(false)
{
    QDBusConnection systemBus = QDBusConnection::systemBus();
    systemBus.connect(CDBConstants::s_service,
                      m_name,
                      CDBConstants::s_serviceInterface,
                      CDBConstants::s_signalPropertyChanged,
                      this,
                      SLOT(onPropertyChanged(const QString&, const QDBusVariant&)));

    queryProperty();
}

QVariant CDBService::getProperty(const QString &name) const
{
    if (name.isEmpty())
        return {  };

    auto upperName = name;
    upperName.replace(0, 1, upperName.at(0).toUpper());

    return m_properties.contains(upperName)
            ? m_properties.value(upperName)
            : QVariant();
}

QString CDBService::name() const
{
    auto name = m_properties.value(QStringLiteral("Name"));
    return name.toString();
}

bool CDBService::isDefault() const
{
    return m_isDefault;
}

void CDBService::forceUpdate()
{
    queryProperty();
}

QString CDBService::serviceName() const
{
    return m_name;
}

QString CDBService::technicalName() const
{
    return CDBUtils::techPathToName(m_name);
}

QString CDBService::state() const
{
    return m_properties.value(QStringLiteral("State")).toString();
}

QString CDBService::type() const
{
    return m_properties.value(QStringLiteral("Type")).toString();
}

uint CDBService::strength() const
{
    return m_properties.value(QStringLiteral("Strength")).toUInt();
}

bool CDBService::valid() const
{
    return !m_properties.isEmpty();
}

bool CDBService::autoConnect() const
{
    return m_properties.value(QStringLiteral("AutoConnect")).toUInt();
}

bool CDBService::favorite() const
{
    return m_properties.value(QStringLiteral("Favorite")).toUInt();
}

bool CDBService::connected() const
{
    // NOTE: https://github.com/sailfishos/libconnman-qt/blob/master/libconnman-qt/libconnman_p.h#L52
    auto stateString = m_properties.value(QStringLiteral("State")).toString();
    if (stateString == QStringLiteral("online") || stateString == QStringLiteral("ready"))
        return true;

    return false;
}

bool CDBService::connecting() const
{
    // NOTE: https://github.com/sailfishos/libconnman-qt/blob/master/libconnman-qt/libconnman_p.h#L52
    auto stateString = m_properties.value(QStringLiteral("State")).toString();
    if (stateString == QStringLiteral("association") || stateString == QStringLiteral("configuration"))
        return true;

    return false;
}

QStringList CDBService::nameservers() const
{
    return m_properties.value(QStringLiteral("Nameservers")).toStringList();
}

QStringList CDBService::nameserversConfig() const
{
    return m_properties.value(QStringLiteral("NameserversConfig")).toStringList();
}

QStringList CDBService::timeservers() const
{
    return m_properties.value(QStringLiteral("Timeservers")).toStringList();
}

QStringList CDBService::timeserversConfig() const
{
    return m_properties.value(QStringLiteral("TimeserversConfig")).toStringList();
}

QStringList CDBService::domains() const
{
    return m_properties.value(QStringLiteral("Domains")).toStringList();
}

QStringList CDBService::domainsConfig() const
{
    return m_properties.value(QStringLiteral("Domains.Configuration")).toStringList();
}

QVariantMap CDBService::ipv4() const
{
    return qdbus_cast<QVariantMap>(m_properties.value(QStringLiteral("IPv4")));
}

QVariantMap CDBService::ipv4Config() const
{
    return qdbus_cast<QVariantMap>(m_properties.value(QStringLiteral("IPv4.Configuration")));
}

QVariantMap CDBService::ipv6() const
{
    return qdbus_cast<QVariantMap>(m_properties.value(QStringLiteral("IPv6")));
}

QVariantMap CDBService::ipv6Config() const
{
    return qdbus_cast<QVariantMap>(m_properties.value(QStringLiteral("IPv6.Configuration")));
}

QString CDBService::bssid() const
{
    return m_properties.value(QStringLiteral("BSSID")).toString();
}

bool CDBService::hidden() const
{
    return m_properties.value(QStringLiteral("Hidden")).toBool();
}

QStringList CDBService::security() const
{
    return m_properties.value(QStringLiteral("Security")).toStringList();
}

QString CDBService::privateKey() const
{
    return m_properties.value(QStringLiteral("PrivateKey")).toString();
}

int CDBService::securityType() const
{
    const auto &security = m_properties.value(QStringLiteral("Security")).toStringList();

    if (security.contains(QStringLiteral("none")))
        return SecurityNone;
    if (security.contains(QStringLiteral("wep")))
        return SecurityWEP;
    if (security.contains(QStringLiteral("psk")))
        return SecurityPSK;
    if (security.contains(QStringLiteral("ieee8021x")))
        return SecurityIEEE802;

    return SecurityUnknown;
}

quint32 CDBService::maxRate() const
{
    return m_properties.value(QStringLiteral("MaxRate")).toUInt();
}

quint16 CDBService::frequency() const
{
    return m_properties.value(QStringLiteral("Frequency")).toUInt();
}

QString CDBService::encryptionMode() const
{
    return m_properties.value(QStringLiteral("EncryptionMode")).toString();
}

QString CDBService::privateKeyPassphrase() const
{
    return m_properties.value(QStringLiteral("PrivateKeyPassphrase")).toString();
}

bool CDBService::roaming() const
{
    return m_properties.value(QStringLiteral("Roaming")).toBool();
}

void CDBService::onPropertyChanged(const QString &name, const QDBusVariant &val)
{
    m_properties.insert(name, val.variant());

    CHECK_PROPERTY("State", state, name);
    CHECK_PROPERTY("State", connected, name);
    CHECK_PROPERTY("State", connecting, name);
    CHECK_PROPERTY("Strength", strength, name);
    CHECK_PROPERTY("Type", type, name);
    CHECK_PROPERTY("AutoConnect", autoConnect, name);
    CHECK_PROPERTY("Favorite", favorite, name);
    CHECK_PROPERTY("Nameservers", nameservers, name);
    CHECK_PROPERTY("Nameservers.Configuration", nameserversConfig, name);
    CHECK_PROPERTY("Timeservers", timeservers, name);
    CHECK_PROPERTY("Timeservers.Configuration", timeserversConfig, name);
    CHECK_PROPERTY("Domains", domains, name);
    CHECK_PROPERTY("Domains.Configuration", domainsConfig, name);
    CHECK_PROPERTY("IPv4", ipv4, name);
    CHECK_PROPERTY("IPv4.Configuration", ipv4Config, name);
    CHECK_PROPERTY("IPv6", ipv6, name);
    CHECK_PROPERTY("IPv6.Configuration", ipv6Config, name);
    CHECK_PROPERTY("BSSID", bssid, name);
    CHECK_PROPERTY("Hidden", hidden, name);
    CHECK_PROPERTY("Security", security, name);
    CHECK_PROPERTY("SecurityType", securityType, name);
    CHECK_PROPERTY("PrivateKey", privateKey, name);
    CHECK_PROPERTY("MaxRate", maxRate, name);
    CHECK_PROPERTY("Frequency", frequency, name);
    CHECK_PROPERTY("EncryptionMode", encryptionMode, name);
    CHECK_PROPERTY("PrivateKeyPassphrase", privateKeyPassphrase, name);
    CHECK_PROPERTY("Roaming", roaming, name);

    if (name == QStringLiteral("State")) {
        emit connectedChanged(connected());
        emit connectingChanged(connecting());
    }
}

void CDBService::queryProperty()
{
    QDBusInterface interface(CDBConstants::s_service,
                             m_name,
                             CDBConstants::s_serviceInterface,
                             QDBusConnection::systemBus());
    QDBusReply<QVariantMap> reply = interface.call(CDBConstants::s_methodGetProperties);
    if (!reply.isValid())
        return;

    m_properties = reply.value();

    auto defaultNetDev = CDBUtils::defaultRouteName();

    QMapIterator<QString, QVariant> it(reply.value());
    bool isDefault = false;
    bool isConnected = false;
    while (it.hasNext()) {
        it.next();

        if (it.key() == QStringLiteral("State") && it.value().toString().toLower() == QStringLiteral("online"))
            isConnected = true;

        if (it.value().typeName() == QStringLiteral("QDBusArgument")) {
            const auto &entryArg = it.value().value<QDBusArgument>();
            entryArg.beginMap();
            while (!entryArg.atEnd()) {
                QString name;
                QVariant val;
                entryArg.beginMapEntry();
                entryArg >> name >> val;
                entryArg.endMapEntry();

                if (it.key() == QStringLiteral("Ethernet")
                        && name == QStringLiteral("Interface")
                        && val.toString() == defaultNetDev)
                    isDefault = true;
            }
            entryArg.endMap();
        }
    }

    emit propertyUpdated();

    auto oldDef = m_isDefault;
    m_isDefault = (isDefault && isConnected);

    if (oldDef != m_isDefault)
        emit defaultChanged(m_isDefault);
}
