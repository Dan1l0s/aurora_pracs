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
    id: packageInfoPage

    objectName: "packageInfoPage"

    /* The package ID is passed from the package search page and
    installed into the PackageInfoProvider component. */
    property alias packageId: packageInfoProvider.packageId

    /**
     * A component providing detailed information about a package.
     */
    PackageInfoProvider { id: packageInfoProvider; objectName: "packageInfoProvider" }

    /**
     * A component that displays information about a package as a list.
     */
    SilicaFlickable {
        objectName: "view"
        anchors {
            fill: parent
            leftMargin: Theme.horizontalPageMargin
            rightMargin: Theme.horizontalPageMargin
        }

        contentHeight: contentColumn.height

        Column {
            id: contentColumn

            objectName: "content"
            anchors {
                left: parent.left
                right: parent.right
            }

            PageHeader {
                objectName: "pageHeader"
                title: qsTr("Package information")
            }

            Column {
                objectName: "errorColumn"
                visible: packageInfoProvider.hasError
                spacing: Theme.paddingSmall
                anchors {
                    left: parent.left
                    right: parent.right
                }

                Label {
                    objectName: "errorLabel"
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    color: Theme.highlightColor
                    text: packageInfoProvider.errorString
                }
            }

            Column {
                objectName: "infoColumn"
                visible: !packageInfoProvider.hasError
                spacing: Theme.paddingSmall
                anchors {
                    left: parent.left
                    right: parent.right
                }

                DetailItem {
                    objectName: "packageName"
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    label: qsTr("Name")
                    value: packageInfoProvider.name
                }

                DetailItem {
                    objectName: "packageVersion"
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    label: qsTr("Version")
                    value: packageInfoProvider.version
                }

                DetailItem {
                    objectName: "packageLicense"
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    label: qsTr("License")
                    value: packageInfoProvider.license
                }

                DetailItem {
                    objectName: "packageURL"
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    label: qsTr("URL")
                    value: packageInfoProvider.url
                }

                DetailItem {
                    objectName: "packageArchitecture"
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    label: qsTr("Architecture")
                    value: packageInfoProvider.architecture
                }

                DetailItem {
                    objectName: "packageStatus"
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    label: qsTr("Status")
                    value: packageInfoProvider.status
                }

                DetailItem {
                    objectName: "packageSize"
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    label: qsTr("Size")
                    value: packageInfoProvider.size
                }

                DetailItem {
                    objectName: "packageSummary"
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    label: qsTr("Summary")
                    value: packageInfoProvider.summary
                }

                Label {
                    objectName: "packageDescriptionLabel"
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    color: Theme.highlightColor
                    text: qsTr("Description")
                }

                Label {
                    objectName: "packageDescriptionText"
                    anchors {
                        left: parent.left
                        right: parent.right
                    }
                    color: Theme.highlightColor
                    text: packageInfoProvider.description
                    wrapMode: Label.WrapAtWordBoundaryOrAnywhere
                    truncationMode: TruncationMode.None
                }
            }
        }
        VerticalScrollDecorator { objectName: "scrollDecorator" }
    }
}
