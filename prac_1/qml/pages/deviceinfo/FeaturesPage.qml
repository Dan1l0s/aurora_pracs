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
    objectName: "featuresPage"
    bottomPadding: Theme.paddingLarge

    FeaturesIface { id: featuresIface; objectName: "featuresIface" }

    InfoLabel {
        objectName: "notValidLabel"
        text: qsTr("Features are not available")
        visible: !featuresIface.available
    }

    Column {
        objectName: "validColumn"
        width: parent.width
        visible: featuresIface.available

        DetailItem {
            objectName: "osItem"
            label: qsTr("OS")
            value: qsTr("%1 %2").arg(featuresIface.osName).arg(featuresIface.osVersion)
        }

        DetailItem {
            objectName: "deviceItem"
            label: qsTr("Device")
            value: qsTr("%1 %2").arg(featuresIface.deviceName).arg(featuresIface.deviceModel)
        }

        DetailItem {
            objectName: "ramTotalSizeItem"
            label: qsTr("RAM total size")
            value: StorageInfoUiStrings.megabytes(featuresIface.ramTotalSize)
        }

        DetailItem {
            objectName: "ramUsedSizeItem"
            label: qsTr("RAM used size")
            value: StorageInfoUiStrings.megabytes(featuresIface.ramUsedSize)
        }

        DetailItem {
            objectName: "ramFreeSizeItem"
            label: qsTr("RAM free size")
            value: StorageInfoUiStrings.megabytes(featuresIface.ramFreeSize)
        }

        DetailItem {
            objectName: "cpuClockSpeedItem"
            label: qsTr("CPU clock speed")
            value: qsTr("%1 Hz").arg(featuresIface.cpuClockSpeed)
        }

        DetailItem {
            objectName: "cpuCoresNumberItem"
            label: qsTr("CPU cores number")
            value: featuresIface.cpuCoresNumber
        }

        DetailItem {
            objectName: "batteryChargeItem"
            label: qsTr("Battery charge")
            value: qsTr("%1%").arg(featuresIface.batteryCharge)
        }

        DetailItem {
            objectName: "screenResolutionItem"
            label: qsTr("Screen resolution")
            value: qsTr("%1x%2").arg(featuresIface.screenResolution.width).arg(featuresIface.screenResolution.height)
        }

        DetailItem {
            objectName: "backCameraResolutionItem"
            label: qsTr("Back camera res.")
            value: qsTr("%1 MP").arg(featuresIface.backCameraResolution)
        }

        DetailItem {
            objectName: "frontCameraResolutionItem"
            label: qsTr("Front camera res.")
            value: qsTr("%1 MP").arg(featuresIface.frontCameraResolution)
        }

        DetailItem {
            objectName: "hasBluetoothItem"
            label: qsTr("Has Bluetooth")
            value: UiStrings.yesNo(featuresIface.hasBluetooth)
        }

        DetailItem {
            objectName: "hasGnssItem"
            label: qsTr("Has GNSS")
            value: UiStrings.yesNo(featuresIface.hasGnss)
        }

        DetailItem {
            objectName: "hasWlanItem"
            label: qsTr("Has WLAN")
            value: UiStrings.yesNo(featuresIface.hasWlan)
        }

        DetailItem {
            objectName: "hasNfcItem"
            label: qsTr("Has NFC")
            value: UiStrings.yesNo(featuresIface.hasNfc)
        }
    }
}
