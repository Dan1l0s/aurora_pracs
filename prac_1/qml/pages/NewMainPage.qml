/*******************************************************************************
**
** Copyright (C) 2022 Open Mobile Platform LLC.
** Contact: https://community.omprussia.ru/open-source
**
** This file is part of the Aurora OS System Info project.
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

import QtQuick 2.6
import Sailfish.Silica 1.0
import "../components"

ListViewPage {
    objectName: "mainPage"
    title: qsTr("New name for 'System info' app")
    model: examplesModel
    delegate: exampleDelegate
    section {
        property: "section"
        criteria: ViewSection.FullString
        delegate: SectionHeader { objectName: "sectionHeader"; text: section }
    }
    headerExtraContent: [
        IconButton {
            objectName: "aboutButton"
            icon.source: "image://theme/icon-m-about"
            anchors.verticalCenter: parent.verticalCenter

            onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
        }
    ]

    ListModel {
        id: examplesModel
        objectName: "examplesModel"

        ListElement {
            name: qsTr("Device Info")
            description: qsTr("Properties of the device and the OS")
            page: "hardware/DeviceInfoPage.qml"
            section: qsTr("Hardware")
        }

        ListElement {
            name: qsTr("Battery")
            description: qsTr("Properties and status of the battery")
            page: "hardware/BatteryInfoPage.qml"
            section: qsTr("Hardware")
        }

        ListElement {
            name: qsTr("Storage")
            description: qsTr("Properties of the mounted volumes")
            page: "hardware/StorageInfoPage.qml"
            section: qsTr("Hardware")
        }

        ListElement {
            name: qsTr("Network Status")
            description: qsTr("Network connection status")
            page: "connections/NetworkManagerPage.qml"
            section: qsTr("Connections")
        }

        ListElement {
            name: qsTr("WLAN")
            description: qsTr("Properties of the WLAN module")
            page: "connections/WlanInfoPage.qml"
            section: qsTr("Connections")
        }

        ListElement {
            name: qsTr("Features")
            description: qsTr("Features info")
            page: "deviceinfo/FeaturesPage.qml"
            section: qsTr("Device Info API")
        }

        ListElement {
            name: qsTr("Sim Cards")
            description: qsTr("SIM cards info")
            page: "deviceinfo/SimCardsPage.qml"
            section: qsTr("Device Info API")
        }

        ListElement {
            name: qsTr("Storages")
            description: qsTr("Storages info")
            page: "deviceinfo/StoragesPage.qml"
            section: qsTr("Device Info API")
        }

        ListElement {
            name: qsTr("Search packages")
            description: qsTr("Properties of the device packages")
            page: "packages/PackagesSearchPage.qml"
            section: qsTr("Packages")
        }
    }

    Component {
        id: exampleDelegate

        ListItem {
            objectName: "exampleItem%1".arg(model.index)
            contentHeight: column.height

            onClicked: pageStack.push(Qt.resolvedUrl(model.page), {
                                          title: model.name,
                                          description: model.description
                                      })

            Column {
                id: column

                objectName: "column"
                anchors {
                    left: parent.left
                    right: parent.right
                    verticalCenter: parent.verticalCenter
                    margins: Theme.horizontalPageMargin
                }
                topPadding: Theme.paddingMedium
                bottomPadding: Theme.paddingMedium

                Label {
                    objectName: "exampleNameLabel"
                    width: parent.width
                    text: model.name
                    truncationMode: TruncationMode.Fade
                }

                Label {
                    objectName: "exampleDescriptionLabel"
                    width: parent.width
                    text: model.description
                    truncationMode: TruncationMode.Fade
                    color: parent.highlighted
                           ? palette.highlightColor
                           : palette.secondaryColor
                    font.pixelSize: Theme.fontSizeSmall
                }
            }
        }
    }
}
