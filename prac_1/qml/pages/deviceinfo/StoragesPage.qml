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

import QtQuick 2.0
import Sailfish.Silica 1.0
import ru.omp.SystemInfo 1.0
import "../../components"
import "../../js/UiStrings.js" as UiStrings
import "../../js/StorageInfoUiStrings.js" as StorageInfoUiStrings

ColumnPage {
    objectName: "storagesPage"
    bottomPadding: Theme.paddingLarge

    StoragesIface { id: storagesIface; objectName: "storagesIface" }

    InfoLabel {
        objectName: "notValidLabel"
        text: qsTr("Storages info is not available")
        visible: !storagesIface.available
    }

    Column {
        objectName: "validColumn"
        width: parent.width
        visible: storagesIface.available

        Column {
            objectName: "intStorageColumn"
            width: parent.width

            SectionHeader {
                objectName: "intStorageItem"
                text: qsTr("Internal storage")
            }

            DetailItem {
                objectName: "intStorageDeviceLabelItem"
                label: qsTr("Device label")
                value: storagesIface.intStorageDeviceLabel
            }

            DetailItem {
                objectName: "intStorageFileSystemTypeItem"
                label: qsTr("File system type")
                value: storagesIface.intStorageFileSystemType
            }

            DetailItem {
                objectName: "intStorageBytesTotalItem"
                label: qsTr("Total size")
                value: StorageInfoUiStrings.megabytes(storagesIface.intStorageBytesTotal)
            }

            DetailItem {
                objectName: "intStorageBytesUsedItem"
                label: qsTr("Used size")
                value: StorageInfoUiStrings.megabytes(storagesIface.intStorageBytesUsed)
            }

            DetailItem {
                objectName: "intStorageBytesFreeItem"
                label: qsTr("Free size")
                value: StorageInfoUiStrings.megabytes(storagesIface.intStorageBytesFree)
            }
        }

        Column {
            objectName: "intUsrPartsColumn"
            width: parent.width

            SectionHeader {
                objectName: "intUsrPartsItem"
                text: qsTr("Internal user partition")
            }

            DetailItem {
                objectName: "intUsrPartsDeviceLabelItem"
                label: qsTr("Device label")
                value: storagesIface.intUsrPartsDeviceLabel
            }

            DetailItem {
                objectName: "intUsrPartsFileSystemTypeItem"
                label: qsTr("File system type")
                value: storagesIface.intUsrPartsFileSystemType
            }

            DetailItem {
                objectName: "intUsrPartsBytesTotalItem"
                label: qsTr("Total size")
                value: StorageInfoUiStrings.megabytes(storagesIface.intUsrPartsBytesTotal)
            }

            DetailItem {
                objectName: "intUsrPartsBytesUsedItem"
                label: qsTr("Used size")
                value: StorageInfoUiStrings.megabytes(storagesIface.intUsrPartsBytesUsed)
            }

            DetailItem {
                objectName: "intUsrPartsBytesFreeItem"
                label: qsTr("Free size")
                value: StorageInfoUiStrings.megabytes(storagesIface.intUsrPartsBytesFree)
            }
        }

        Column {
            objectName: "extStorageColumn"
            width: parent.width
            visible: storagesIface.extStorageMounted

            SectionHeader {
                objectName: "extStorageItem"
                text: qsTr("External storage")
            }

            DetailItem {
                objectName: "extStorageDeviceLabelItem"
                label: qsTr("Device label")
                value: storagesIface.extStorageDeviceLabel
            }

            DetailItem {
                objectName: "extStoragePartitionsCountItem"
                label: qsTr("Partitions count")
                value: storagesIface.extStoragePartitionsCount
            }

            DetailItem {
                objectName: "extStorageBytesTotalItem"
                label: qsTr("Total size")
                value: StorageInfoUiStrings.megabytes(storagesIface.extStorageBytesTotal)
            }

            DetailItem {
                objectName: "extStorageBytesUsedItem"
                label: qsTr("Used size")
                value: StorageInfoUiStrings.megabytes(storagesIface.extStorageBytesUsed)
            }

            DetailItem {
                objectName: "extStorageBytesFreeItem"
                label: qsTr("Free size")
                value: StorageInfoUiStrings.megabytes(storagesIface.extStorageBytesFree)
            }
        }
    }
}
