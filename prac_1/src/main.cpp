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

#include <QGuiApplication>
#include <QtQml>
#include <QtSystemInfo/QBatteryInfo>
#include <QtSystemInfo/QDeviceInfo>
#include <QQuickView>

#include <auroraapp.h>

#include "storageinfomodel.h"
#include "featuresiface.h"
#include "simcardsiface.h"
#include "storagesiface.h"

#include "cdbtechnologymodel.h"
#include "cdbservice.h"
#include "cdbnetworkmanager.h"

#include "packageinfoprovider.h"
#include "packagesearcher.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<QBatteryInfo>("ru.omp.SystemInfo", 1, 0, "BatteryInfo");
    qmlRegisterType<QDeviceInfo>("ru.omp.SystemInfo", 1, 0, "DeviceInfo");
    qmlRegisterType<StorageInfoModel>("ru.omp.SystemInfo", 1, 0, "StorageInfoModel");
    qmlRegisterType<FeaturesIface>("ru.omp.SystemInfo", 1, 0, "FeaturesIface");
    qmlRegisterType<SimCardsIface>("ru.omp.SystemInfo", 1, 0, "SimCardsIface");
    qmlRegisterType<StoragesIface>("ru.omp.SystemInfo", 1, 0, "StoragesIface");

    qmlRegisterType<CDBTechnologyModel>("ru.omp.SystemInfo", 1, 0, "CDBTechnologyModel");
    qmlRegisterType<CDBService>("ru.omp.SystemInfo", 1, 0, "CDBService");
    qmlRegisterType<CDBNetworkManager>("ru.omp.SystemInfo", 1, 0, "CDBNetworkManager");
    //    qmlRegisterUncreatableType<CDBService::SecurityType>("ru.omp.SystemInfo", 1, 0,
    //                                                         "SecurityType",
    //                                                         "Cannot create a class of type UncreatableType");

    qmlRegisterType<PackageInfoProvider>("ru.omp.SystemInfo", 1, 0, "PackageInfoProvider");
    qmlRegisterType<PackageSearcher>("ru.omp.SystemInfo", 1, 0, "PackageSearcher");

    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    QScopedPointer<QQuickView> view(Aurora::Application::createView());

    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/SystemInfo.qml")));

    view->show();

    return application->exec();
}
