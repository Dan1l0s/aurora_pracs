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

#ifndef CDBCONSTANTS_H
#define CDBCONSTANTS_H

#include <QString>

namespace CDBConstants
{
static const QString s_service = QStringLiteral("net.connman");
static const QString s_managerInterface = QStringLiteral("net.connman.Manager");
static const QString s_serviceInterface = QStringLiteral("net.connman.Service");
static const QString s_technologyInterface = QStringLiteral("net.connman.Technology");
static const QString s_path = QStringLiteral("/");
static const QString s_techWiFiPath = QStringLiteral("/net/connman/technology/wifi");
static const QString s_techBluetoothPath = QStringLiteral("/net/connman/technology/bluetooth");
static const QString s_techGPSPath = QStringLiteral("/net/connman/technology/gps");
static const QString s_techPath = QStringLiteral("/net/connman/technology/");

static const QString s_signalPropertyChanged = QStringLiteral("PropertyChanged");
static const QString s_signalServicesChanged = QStringLiteral("ServicesChanged");
static const QString s_signalTechnologyAdded = QStringLiteral("TechnologyAdded");
static const QString s_signalTechnologyRemoved = QStringLiteral("TechnologyRemoved");
static const QString s_methodGetProperties = QStringLiteral("GetProperties");
static const QString s_methodGetServices = QStringLiteral("GetServices");
static const QString s_methodGetTechnologies = QStringLiteral("GetTechnologies");

static const int s_wifiUpdateIntervalMsec = 3000;
}

#endif // CDBCONSTANTS_H
