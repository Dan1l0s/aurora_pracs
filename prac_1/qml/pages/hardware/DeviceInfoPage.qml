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
import "../../js/DeviceInfoUiStrings.js" as DeviceInfoUiStrings

ColumnPage {
    objectName: "deviceInfoPage"
    bottomPadding: Theme.paddingLarge

    DeviceInfo { id: deviceInfo; objectName: "deviceInfo" }

    DetailItem {
        objectName: "productNameItem"
        label: qsTr("Product name")
        value: deviceInfo.productName()
    }

    DetailItem {
        objectName: "modelItem"
        label: qsTr("Model")
        value: deviceInfo.model()
    }

    DetailItem {
        objectName: "boardNameItem"
        label: qsTr("Board name")
        value: deviceInfo.boardName()
    }

    DetailItem {
        objectName: "manufacturerItem"
        label: qsTr("Manufacturer")
        value: deviceInfo.manufacturer()
    }

    DetailItem {
        objectName: "operatingSystemNameItem"
        label: qsTr("Operating system")
        value: deviceInfo.operatingSystemName()
    }

    DetailItem {
        objectName: "osVersionItem"
        label: qsTr("OS version")
        value: deviceInfo.version(DeviceInfo.Os)
    }

    DetailItem {
        objectName: "firmwareVersionItem"
        label: qsTr("Firmware version")
        value: deviceInfo.version(DeviceInfo.Firmware)
    }

    DetailItem {
        objectName: "uniqueDeviceIdItem"
        label: qsTr("Unique device ID")
        value: deviceInfo.uniqueDeviceID()
    }

    Repeater {
        objectName: "imeiRepeater"
        model: deviceInfo.imeiCount()

        DetailItem {
            objectName: "imei%1Item".arg(model.index)
            label: qsTr("IMEI %1").arg(model.index + 1)
            value: deviceInfo.imei(model.index)
        }
    }

    DetailItem {
        objectName: "enabledLocksItem"
        label: qsTr("Enabled locks")
        value: DeviceInfoUiStrings.locks(deviceInfo.enabledLocks)
    }

    DetailItem {
        objectName: "activatedLocksItem"
        label: qsTr("Activated locks")
        value: DeviceInfoUiStrings.locks(deviceInfo.activatedLocks)
    }

    DetailItem {
        objectName: "thermalStateItem"
        label: qsTr("Thermal state")
        value: DeviceInfoUiStrings.thermalState(deviceInfo.thermalState)
    }

    DetailItem {
        objectName: "bluetoothFeatureItem"
        label: qsTr("Bluetooth available")
        value: UiStrings.yesNo(deviceInfo.hasFeature(DeviceInfo.BluetoothFeature))
    }

    DetailItem {
        objectName: "currentBluetoothPowerStateItem"
        label: qsTr("Bluetooth enabled")
        value: UiStrings.yesNo(deviceInfo.currentBluetoothPowerState)
    }

    DetailItem {
        objectName: "cameraFeatureItem"
        label: qsTr("Camera available")
        value: UiStrings.yesNo(deviceInfo.hasFeature(DeviceInfo.CameraFeature))
    }

    DetailItem {
        objectName: "fmRadioFeatureItem"
        label: qsTr("FM radio available")
        value: UiStrings.yesNo(deviceInfo.hasFeature(DeviceInfo.FmRadioFeature))
    }

    DetailItem {
        objectName: "fmTransmitterFeatureItem"
        label: qsTr("FM transmitter available")
        value: UiStrings.yesNo(deviceInfo.hasFeature(DeviceInfo.FmTransmitterFeature))
    }

    DetailItem {
        objectName: "infraredFeatureItem"
        label: qsTr("Infrared available")
        value: UiStrings.yesNo(deviceInfo.hasFeature(DeviceInfo.InfraredFeature))
    }

    DetailItem {
        objectName: "ledFeatureItem"
        label: qsTr("LED available")
        value: UiStrings.yesNo(deviceInfo.hasFeature(DeviceInfo.LedFeature))
    }

    DetailItem {
        objectName: "memoryCardFeatureItem"
        label: qsTr("Memory card slot available")
        value: UiStrings.yesNo(deviceInfo.hasFeature(DeviceInfo.MemoryCardFeature))
    }

    DetailItem {
        objectName: "usbFeatureItem"
        label: qsTr("USB available")
        value: UiStrings.yesNo(deviceInfo.hasFeature(DeviceInfo.UsbFeature))
    }

    DetailItem {
        objectName: "vibrationFeatureItem"
        label: qsTr("Vibration available")
        value: UiStrings.yesNo(deviceInfo.hasFeature(DeviceInfo.VibrationFeature))
    }

    DetailItem {
        objectName: "wlanFeatureItem"
        label: qsTr("WLAN available")
        value: UiStrings.yesNo(deviceInfo.hasFeature(DeviceInfo.WlanFeature))
    }

    DetailItem {
        objectName: "simFeatureItem"
        label: qsTr("SIM slot available")
        value: UiStrings.yesNo(deviceInfo.hasFeature(DeviceInfo.SimFeature))
    }

    DetailItem {
        objectName: "positioningFeatureItem"
        label: qsTr("Positioning available")
        value: UiStrings.yesNo(deviceInfo.hasFeature(DeviceInfo.PositioningFeature))
    }

    DetailItem {
        objectName: "videoOutFeatureItem"
        label: qsTr("Video output available")
        value: UiStrings.yesNo(deviceInfo.hasFeature(DeviceInfo.VideoOutFeature))
    }

    DetailItem {
        objectName: "hapticsFeatureItem"
        label: qsTr("Haptics available")
        value: UiStrings.yesNo(deviceInfo.hasFeature(DeviceInfo.HapticsFeature))
    }

    DetailItem {
        objectName: "nfcFeatureItem"
        label: qsTr("NFC available")
        value: UiStrings.yesNo(deviceInfo.hasFeature(DeviceInfo.NfcFeature))
    }
}
