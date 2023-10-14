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

#ifndef CDBSERVICE_H
#define CDBSERVICE_H

#include <QObject>
#include <QVariantMap>
#include <QtDBus/QDBusVariant>

#include "cdbutils.h"

class CDBService : public QObject
{
    Q_OBJECT

    DECLARE_PROPERTY(QString, name);
    DECLARE_PROPERTY(QString, state)
    DECLARE_PROPERTY(QString, type)
    DECLARE_PROPERTY(uint, strength)
    DECLARE_PROPERTY(bool, autoConnect)
    DECLARE_PROPERTY(bool, valid)
    DECLARE_PROPERTY(bool, favorite)
    DECLARE_PROPERTY(bool, connected)
    DECLARE_PROPERTY(bool, connecting)
    DECLARE_PROPERTY(QStringList, nameservers)
    DECLARE_PROPERTY(QStringList, nameserversConfig)
    DECLARE_PROPERTY(QStringList, timeservers)
    DECLARE_PROPERTY(QStringList, timeserversConfig)
    DECLARE_PROPERTY(QStringList, domains)
    DECLARE_PROPERTY(QStringList, domainsConfig)
    DECLARE_PROPERTY(QVariantMap, ipv4)
    DECLARE_PROPERTY(QVariantMap, ipv4Config)
    DECLARE_PROPERTY(QVariantMap, ipv6)
    DECLARE_PROPERTY(QVariantMap, ipv6Config)
    DECLARE_PROPERTY(QString, bssid)
    DECLARE_PROPERTY(bool, hidden)
    DECLARE_PROPERTY(QStringList, security)
    DECLARE_PROPERTY(int, securityType)
    DECLARE_PROPERTY(QString, privateKey)
    DECLARE_PROPERTY(quint32, maxRate)
    DECLARE_PROPERTY(quint16, frequency)
    DECLARE_PROPERTY(QString, encryptionMode)
    DECLARE_PROPERTY(QString, privateKeyPassphrase)
    DECLARE_PROPERTY(bool, roaming)
    DECLARE_PROPERTY(QString, technicalName)

public:
    enum SecurityType {
        SecurityUnknown,
        SecurityNone,
        SecurityWEP,
        SecurityPSK,
        SecurityIEEE802
    };
    Q_ENUM(SecurityType)

    explicit CDBService(QObject *parent = nullptr);
    explicit CDBService(const QString &name, QObject *parent = nullptr);

    QVariant getProperty(const QString &name) const;
    bool isDefault() const;
    void forceUpdate();
    QString serviceName() const;

private slots:
    void onPropertyChanged(const QString &name, const QDBusVariant &val);

private:
    void queryProperty();

signals:
    void propertyChanged(QString, QVariant);
    void propertyUpdated();
    void defaultChanged(bool);

private:
    QVariantMap m_properties;
    QString m_name;
    bool m_isDefault;
};

#endif // CDBSERVICE_H
