/****************************************************************************
**
** Copyright (C) 2020 Open Mobile Platform LLC.
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
**   * Neither the name of Open Mobile Platform LLC copyright holder nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
** PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL OPEN MOBILE PLATFORM LLC OR
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

import QtQuick 2.2
import Sailfish.Silica 1.0
import ru.omp.SystemInfo 1.0

Page {
    id: packageSearchPage

    property string title
    property string description

    objectName: "packageSearchPage"

    /**
     * A component that provides a list of packages by a given name.
     */
    PackageSearcher { id: packageSearcher; objectName: "packageSearcher" }

    /**
     * Component that displays information about packages as a list.
     */
    SilicaListView {
        objectName: "view"
        header: headerDelegate
        model: packageSearcher.packageList
        delegate: itemDelegate
        spacing: Theme.paddingMedium
        anchors.fill: parent
        clip: true

        VerticalScrollDecorator { objectName: "scrollDecorator" }
    }

    Component {
        id: headerDelegate

        Column {
            id: searchStatusBar

            spacing: Theme.paddingMedium

            anchors {
                left: parent.left
                right: parent.right
                leftMargin: Theme.horizontalPageMargin
                rightMargin: Theme.horizontalPageMargin
            }

            PageHeader {
                objectName: "pageHeader"
                title: packageSearchPage.title
                description: packageSearchPage.description
            }

            /**
             * On pressing the Enter key searches
             * for packages matching the given name.
             */
            SearchField {
                id: packageNameInput

                objectName: "searchField"
                width: parent.width
                placeholderText: qsTr("package name")
                enabled: !packageSearcher.searchRunning

                EnterKey.onClicked: {
                    var searchText = packageNameInput.text.trim()
                    packageSearcher.searchPackageByName(searchText)
                    focus = false
                }
            }

            Row {
                id: busyIndicatorRow

                objectName: "busyIndicatorRow"
                spacing: Theme.paddingLarge
                visible: packageSearcher.searchRunning

                BusyIndicator {
                    objectName: "busyIndicator"
                    size: BusyIndicatorSize.Medium
                    running: true
                }

                Label {
                    objectName: "busyIndicatorLabel"
                    anchors.verticalCenter: parent.verticalCenter
                    text: qsTr("Searching for %1").arg(
                              packageSearcher.searchString)
                }
            }

            Label {
                id: notFoundLabel
                objectName: "notFoundLabel"
                width: parent.width
                visible: packageSearcher.searchFailed
                text: qsTr("Nothing was found for %1").arg(
                          packageSearcher.searchString)
            }

            Label {
                id: dataFoundLabel

                objectName: "packageFoundLabel"
                width: parent.width
                visible: packageSearcher.searchSucceeded
                text: qsTr("Search results for %1").arg(
                          packageSearcher.searchString)
            }
        }
    }

    Component {
        id: itemDelegate

        Item {
            objectName: "packageItem%1".arg(index)
            anchors {
                left: parent.left
                right: parent.right
            }
            height: packageColumn.height

            Rectangle {
                objectName: "packageRectangle%1".arg(index)
                anchors.fill: parent
                color: Theme.rgba(Theme.highlightBackgroundColor, Theme.opacityFaint)
            }

            /* A component that allows to go to the page with detailed information
            about the package by clicking on the package info area*/
            MouseArea {
                objectName: "packageMouseArea%1".arg(index)
                anchors.fill: parent
                onClicked: pageStack.push(Qt.resolvedUrl("PackageInfoPage.qml"),
                                          { "packageId": modelData.packageId })
            }

            Column {
                id: packageColumn

                objectName: "packageColumn%1".arg(index)
                anchors {
                    left: parent.left
                    right: parent.right
                }
                spacing: Theme.paddingSmall

                DetailItem {
                    objectName: "packageName%1".arg(index)
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    label: qsTr("Name")
                    value: modelData.name
                }

                DetailItem {
                    objectName: "packageVersion%1".arg(index)
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    label: qsTr("Version")
                    value: modelData.version
                }

                DetailItem {
                    objectName: "packageStatus%1".arg(index)
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    label: qsTr("Status")
                    value: modelData.status
                }

                DetailItem {
                    objectName: "packageArchitecture%1".arg(index)
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    label: qsTr("Architecture")
                    value: modelData.architecture
                }

                DetailItem {
                    objectName: "packageSummary%1".arg(index)
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    label: qsTr("Summary")
                    value: modelData.summary
                }
            }
        }
    }
}
