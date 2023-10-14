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

import QtQuick 2.0
import Sailfish.Silica 1.0
import "../../components"
import "../../js/UiStrings.js" as UiStrings
import "../../js/NetworkUiStrings.js" as NetworkUiStrings
import ru.omp.SystemInfo 1.0

ColumnPage {
    objectName: "networkManagerPage"
    bottomPadding: Theme.paddingLarge

    CDBNetworkManager { id: networkManager; objectName: "networkManager" }

    InfoLabel {
        objectName: "notValidLabel"
        text: qsTr("Network manager is not available")
        visible: !networkManager.valid
    }

    Column {
        objectName: "validColumn"
        width: parent.width
        visible: networkManager.valid

        DetailItem {
            objectName: "availableItem"
            label: qsTr("Available")
            value: UiStrings.yesNo(networkManager.available)
        }

        DetailItem {
            objectName: "stateItem"
            label: qsTr("State")
            value: NetworkUiStrings.state(networkManager.state)
        }

        DetailItem {
            objectName: "connectedItem"
            label: qsTr("Connected")
            value: UiStrings.yesNo(networkManager.connected)
        }

        DetailItem {
            objectName: "connectingItem"
            label: qsTr("Connecting")
            value: UiStrings.yesNo(networkManager.connecting)
        }

        DetailItem {
            objectName: "connectingWifiItem"
            label: qsTr("Connecting Wi-Fi")
            value: UiStrings.yesNo(networkManager.connectingWifi)
        }

        DetailItem {
            objectName: "offlineModeItem"
            label: qsTr("Offline mode")
            value: UiStrings.yesNo(networkManager.offlineMode)
        }

        DetailItem {
            objectName: "sessionModeItem"
            label: qsTr("Session mode")
            value: UiStrings.yesNo(networkManager.sessionMode)
        }

        DetailItem {
            objectName: "inputRequestTimeoutItem"
            label: qsTr("Input request timeout")
            value: networkManager.inputRequestTimeout
        }

        DetailItem {
            objectName: "technologiesPowered"
            label: qsTr("Powered technologies")
            value: networkManager.technologies.join(", ") || qsTr("None")
        }

        NetworkServiceItem {
            objectName: "defaultRouteItem"
            title: qsTr("Default route")
            networkService: networkManager.defaultRoute
        }

        Loader {
            objectName: "connectedWifiLoader"
            active: networkManager.connectedWifi
                    && networkManager.connectedWifi.technicalName !== networkManager.defaultRoute.technicalName
                    && networkManager.connectedWifi.state === "online"
            sourceComponent: connectedWifiComponent
            width: parent.width

            onActiveChanged: if (!active) height = 0
        }
    }

    Component {
        id: connectedWifiComponent

        NetworkServiceItem {
            objectName: "connectedWifiItem"
            title: qsTr("Connected Wi-Fi")
            networkService: networkManager.connectedWifi
        }
    }
}
