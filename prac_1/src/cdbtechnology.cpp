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
#include "cdbtechnology.h"

CDBTechnology::CDBTechnology(QObject *parent)
    : QObject(parent)
{  }

CDBTechnology::CDBTechnology(const QString &name, QObject *parent)
    : QObject(parent), m_name(name)
{
    QDBusConnection systemBus = QDBusConnection::systemBus();
    systemBus.connect(CDBConstants::s_service,
                      m_name,
                      CDBConstants::s_technologyInterface,
                      CDBConstants::s_signalPropertyChanged,
                      this,
                      SLOT(onPropertyChanged(const QString&, const QDBusVariant&)));

    QDBusInterface interface(CDBConstants::s_service,
                             m_name,
                             CDBConstants::s_technologyInterface,
                             QDBusConnection::systemBus());
    QDBusReply<QVariantMap> propertiesReply = interface.call(CDBConstants::s_methodGetProperties);

    if (propertiesReply.isValid())
        m_properties = propertiesReply.value();
}

QString CDBTechnology::name() const
{
    return m_name.split(QChar('/')).last();
}

QVariant CDBTechnology::getProperty(const QString &name) const
{
    return m_properties.value(name);
}

void CDBTechnology::onPropertyChanged(const QString &name, const QDBusVariant &value)
{
    m_properties.insert(name, value.variant());
    emit propertyChanged(name);
}
