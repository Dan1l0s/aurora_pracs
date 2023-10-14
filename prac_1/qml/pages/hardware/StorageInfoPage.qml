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

import QtQuick 2.6
import Sailfish.Silica 1.0
import ru.omp.SystemInfo 1.0
import "../../components"
import "../../js/UiStrings.js" as UiStrings
import "../../js/StorageInfoUiStrings.js" as StorageInfoUiStrings

ListViewPage {
    objectName: "storageInfoPage"
    model: storageInfoModel
    delegate: itemDelegate

    StorageInfoModel { id: storageInfoModel; objectName: "storageInfoModel" }

    Component {
        id: itemDelegate

        Column {
            objectName: "storageItem%1".arg(index)
            width: parent.width
            bottomPadding: Theme.paddingLarge

            SectionHeader {
                objectName: "displayNameItem"
                text: model.displayName
            }

            DetailItem {
                objectName: "nameItem"
                label: qsTr("Name")
                value: model.name
            }

            DetailItem {
                objectName: "rootPathItem"
                label: qsTr("Path")
                value: model.rootPath
            }

            DetailItem {
                objectName: "deviceItem"
                label: qsTr("Device")
                value: model.device
            }

            DetailItem {
                objectName: "fileSystemTypeItem"
                label: qsTr("File system type")
                value: model.fileSystemType
            }

            DetailItem {
                objectName: "blockSizeItem"
                label: qsTr("Block size")
                value: model.blockSize
            }

            DetailItem {
                objectName: "bytesAvailableItem"
                label: qsTr("Available size")
                value: StorageInfoUiStrings.megabytes(model.bytesAvailable)
            }

            DetailItem {
                objectName: "bytesFreeItem"
                label: qsTr("Free size")
                value: StorageInfoUiStrings.megabytes(model.bytesFree)
            }

            DetailItem {
                objectName: "bytesTotalItem"
                label: qsTr("Total size")
                value: StorageInfoUiStrings.megabytes(model.bytesTotal)
            }

            DetailItem {
                objectName: "isReadOnlyItem"
                label: qsTr("Read only")
                value: UiStrings.yesNo(model.isReadOnly)
            }

            DetailItem {
                objectName: "isReadyItem"
                label: qsTr("Ready")
                value: UiStrings.yesNo(model.isReady)
            }

            DetailItem {
                objectName: "isRootItem"
                label: qsTr("Is root")
                value: UiStrings.yesNo(model.isRoot)
            }
        }
    }
}
