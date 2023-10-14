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
import ru.omp.SystemInfo 1.0
import "../../components"
import "../../js/UiStrings.js" as UiStrings
import "../../js/BatteryInfoUiStrings.js" as BatteryInfoUiStrings

ColumnPage {
    objectName: "batteryInfoPage"
    bottomPadding: Theme.paddingLarge

    BatteryInfo { id: batteryInfo; objectName: "batteryInfo"; batteryIndex: batterySelector.currentIndex }

    ComboBox {
        id: batterySelector

        objectName: "batterySelector"
        label: qsTr("Battery")
        width: parent.width
        enabled: batteryInfo.batteryCount > 1

        menu: ContextMenu {
            objectName: "menu"

            Repeater {
                model: batteryInfo.batteryCount
                delegate: MenuItem { objectName: "item%1".arg(model.index); text: model.index + 1 }
            }
        }
    }

    InfoLabel {
        objectName: "notValidLabel"
        text: qsTr("Battery info is not available")
        visible: !batteryInfo.valid
    }

    Column {
        objectName: "validColumn"
        width: parent.width
        visible: batteryInfo.valid

        DetailItem {
            objectName: "levelItem"
            label: qsTr("Level")
            value: qsTr("%L1 %").arg(batteryInfo.level)
        }

        DetailItem {
            objectName: "levelStatusItem"
            label: qsTr("Level status")
            value: BatteryInfoUiStrings.levelStatus(batteryInfo.levelStatus)
        }

        DetailItem {
            objectName: "voltageItem"
            label: qsTr("Voltage")
            value: batteryInfo.voltage >= 0
                   ? qsTr("%L1 mV").arg(batteryInfo.voltage)
                   : qsTr("Unknown")
        }

        DetailItem {
            objectName: "healthItem"
            label: qsTr("Health")
            value: BatteryInfoUiStrings.health(batteryInfo.health)
        }

        DetailItem {
            objectName: "maximumCapacityItem"
            label: qsTr("Maximum capacity")
            value: batteryInfo.maximumCapacity >= 0
                   ? qsTr("%L1 mAh").arg(batteryInfo.maximumCapacity)
                   : qsTr("Unknown")
        }

        DetailItem {
            objectName: "remainingCapacityItem"
            label: qsTr("Remaining capacity")
            value: batteryInfo.remainingCapacity >= 0
                   ? qsTr("%L1 mAh").arg(batteryInfo.remainingCapacity)
                   : qsTr("Unknown")
        }

        DetailItem {
            objectName: "cycleCountItem"
            label: qsTr("Cycle count")
            value: batteryInfo.cycleCount >= 0
                   ? batteryInfo.cycleCount
                   : qsTr("Unknown")
        }

        DetailItem {
            objectName: "temperatureItem"
            label: qsTr("Temperature")
            value: isNaN(batteryInfo.temperature)
                   ? qsTr("Unknown")
                   : qsTr("%L1 °C").arg(batteryInfo.temperature)
        }

        DetailItem {
            objectName: "chargingStateItem"
            label: qsTr("Charging state")
            value: BatteryInfoUiStrings.chargingState(batteryInfo.chargingState)
        }

        DetailItem {
            objectName: "chargerTypeItem"
            label: qsTr("Charger type")
            value: BatteryInfoUiStrings.chargerType(batteryInfo.chargerType)
        }

        DetailItem {
            objectName: "currentFlowItem"
            label: qsTr("Current flow")
            value: qsTr("%L1 mA").arg(batteryInfo.currentFlow)
        }

        DetailItem {
            objectName: "remainingChargingTimeItem"
            label: qsTr("Remaining charging time")
            value: batteryInfo.remainingChargingTime >= 0
                   ? qsTr("%L1 sec").arg(batteryInfo.remainingChargingTime)
                   : qsTr("Unknown")
        }
    }
}
