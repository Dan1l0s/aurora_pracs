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
import "../js/UiStrings.js" as UiStrings
import "../js/NetworkUiStrings.js" as NetworkUiStrings
import ru.omp.SystemInfo 1.0

Column {
    id: root

    property string title
    property CDBService networkService

    objectName: "networkServiceItem"
    width: parent.width

    SectionHeader {
        id: header

        objectName: "header"
        text: root.title || (networkService ? networkService.name || (networkService.hidden && qsTr("Hidden")) : "")
    }

    InfoLabel {
        objectName: "notValidLabel"
        text: qsTr("Network service is not available")
        visible: !propertiesContainerLoader.active
        font.pixelSize: Theme.fontSizeLarge
    }

    Loader {
        id: propertiesContainerLoader

        objectName: "propertiesContainerLoader"
        active: networkService && networkService.valid
        sourceComponent: propertiesComponent
        width: parent.width
    }

    Component {
        id: propertiesComponent

        Column {
            objectName: "propertiesContainer"
            spacing: root.spacing

            DetailItem {
                id: nameItem

                objectName: "nameItem"
                label: qsTr("Name")
                value: networkService.name || qsTr("Undefined")
                visible: header.text !== value
            }

            DetailItem {
                objectName: "stateItem"
                label: qsTr("State")
                value: NetworkUiStrings.state(networkService.state)
            }

            DetailItem {
                objectName: "errorItem"
                label: qsTr("Error")
                value: networkService.error || qsTr("No error")
                visible: networkService.state === "failure"
            }

            DetailItem {
                objectName: "typeItem"
                label: qsTr("Type")
                value: NetworkUiStrings.type(networkService.type)
            }

            DetailItem {
                objectName: "strengthItem"
                label: qsTr("Strength")
                value: networkService.strength
                visible: networkService.type !== "ethernet"
            }

            DetailItem {
                objectName: "favoriteItem"
                label: qsTr("Favorite")
                value: UiStrings.yesNo(networkService.favorite)
            }

            DetailItem {
                objectName: "autoConnectItem"
                label: qsTr("Auto connect")
                value: UiStrings.yesNo(networkService.autoConnect)
            }

            DetailItem {
                objectName: "connectedItem"
                label: qsTr("Connected")
                value: UiStrings.yesNo(networkService.connected)
            }

            Loader {
                objectName: "connectedPropertiesLoader"
                active: networkService.connected
                sourceComponent: connectedPropertiesComponent
                width: parent.width
            }

            Loader {
                objectName: "cellularPropertiesContainerLoader"
                active: networkService.type === "cellular"
                sourceComponent: cellularPropertiesComponent
                width: parent.width
            }

            Loader {
                objectName: "wifiPropertiesContainerLoader"
                active: networkService.type === "wifi"
                sourceComponent: wifiPropertiesComponent
                width: parent.width
            }
        }
    }

    Component {
        id: connectedPropertiesComponent

        Column {
            objectName: "connectedPropertiesContainer"
            spacing: root.spacing

            DetailItem {
                objectName: "nameserversItem"
                label: qsTr("Nameservers")
                value: networkService.nameservers.join(", ") || qsTr("None")
                visible: networkService.state === "ready" || networkService.state === "online"
            }

            DetailItem {
                objectName: "nameserversConfigItem"
                label: qsTr("Nameservers config")
                value: networkService.nameserversConfig.join(", ") || qsTr("None")
            }

            DetailItem {
                objectName: "timeserversItem"
                label: qsTr("Timeservers")
                value: networkService.timeservers.join(", ") || qsTr("None")
                visible: networkService.state === "ready" || networkService.state === "online"
            }

            DetailItem {
                objectName: "timeserversConfigItem"
                label: qsTr("Timeservers config")
                value: networkService.timeservers.join(", ") || qsTr("None")
            }

            DetailItem {
                objectName: "domainsItem"
                label: qsTr("Domains")
                value: networkService.domains.join(", ") || qsTr("None")
                visible: networkService.state === "ready" || networkService.state === "online"
            }

            DetailItem {
                objectName: "domainsConfigItem"
                label: qsTr("Domains config")
                value: networkService.domainsConfig.join(", ") || qsTr("None")
            }

            DetailItem {
                objectName: "ipv4Item"
                label: qsTr("IPv4")
                value: NetworkUiStrings.ipv4(networkService.ipv4)
            }

            DetailItem {
                objectName: "ipv4ConfigItem"
                label: qsTr("IPv4 Config")
                value: NetworkUiStrings.ipv4(networkService.ipv4Config)
            }

            DetailItem {
                objectName: "ipv6Item"
                label: qsTr("IPv6")
                value: NetworkUiStrings.ipv6(networkService.ipv6)
            }

            DetailItem {
                objectName: "ipv6ConfigItem"
                label: qsTr("IPv6 Config")
                value: NetworkUiStrings.ipv6(networkService.ipv6Config)
            }
        }
    }

    Component {
        id: cellularPropertiesComponent

        Column {
            objectName: "cellularPropertiesContainer"
            spacing: root.spacing

            DetailItem {
                objectName: "roamingItem"
                label: qsTr("Roaming")
                value: UiStrings.yesNo(networkService.roaming)
            }
        }
    }

    Component {
        id: wifiPropertiesComponent

        Column {
            objectName: "wifiPropertiesContainer"
            spacing: root.spacing

            DetailItem {
                objectName: "bssidItem"
                label: qsTr("BSSID")
                value: networkService.bssid
            }

            DetailItem {
                objectName: "hiddenItem"
                label: qsTr("Hidden")
                value: UiStrings.yesNo(networkService.hidden)
            }

            DetailItem {
                objectName: "securityItem"
                label: qsTr("Security")
                value: networkService.security.map(NetworkUiStrings.security).join(", ")
            }

            DetailItem {
                objectName: "securityTypeItem"
                label: qsTr("Security type")
                value: NetworkUiStrings.securityType(networkService.securityType) || qsTr("None")
            }

            DetailItem {
                objectName: "privateKeyItem"
                label: qsTr("Private key")
                value: networkService.privateKey
            }

            DetailItem {
                objectName: "maxRateItem"
                label: qsTr("Max rate")
                value: networkService.maxRate ? NetworkUiStrings.rate(networkService.maxRate) : qsTr("Undefined")
            }

            DetailItem {
                objectName: "frequencyItem"
                label: qsTr("Frequency")
                value: NetworkUiStrings.frequency(networkService.frequency)
            }

            DetailItem {
                objectName: "encryptionModeItem"
                label: qsTr("Encryption mode")
                value: NetworkUiStrings.encryptionMode(networkService.encryptionMode)
            }

            DetailItem {
                objectName: "privateKeyPassphraseItem"
                label: qsTr("Private key passphrase")
                value: networkService.privateKeyPassphrase
            }
        }
    }
}
