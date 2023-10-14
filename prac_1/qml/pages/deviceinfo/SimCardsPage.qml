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

ColumnPage {
    objectName: "simCardsPage"
    bottomPadding: Theme.paddingLarge

    SimCardsIface { id: simCardsIface; objectName: "simCardsIface"; simCardIndex: simCardSelector.currentIndex }

    ComboBox {
        id: simCardSelector

        objectName: "simCardSelector"
        label: qsTr("SIM card")
        width: parent.width
        enabled: simCardsIface.simCardsCount > 1

        menu: ContextMenu {
            objectName: "menu"

            Repeater {
                model: simCardsIface.simCardsCount
                delegate: MenuItem { objectName: "item%1".arg(model.index); text: model.index + 1 }
            }
        }
    }

    InfoLabel {
        objectName: "notValidLabel"
        text: qsTr("SIM cards info is not available")
        visible: !simCardsIface.available
    }

    Column {
        objectName: "validColumn"
        width: parent.width
        visible: simCardsIface.available

        DetailItem {
            objectName: "simCardNameItem"
            label: qsTr("SIM card name")
            value: simCardsIface.simCardName
        }

        DetailItem {
            objectName: "operatorNameItem"
            label: qsTr("Operator name")
            value: simCardsIface.operatorName
        }

        DetailItem {
            objectName: "simCardEnabledItem"
            label: qsTr("SIM card enabled")
            value: UiStrings.yesNo(simCardsIface.simCardEnabled)
        }

        DetailItem {
            objectName: "preferredVoiceCallItem"
            label: qsTr("Preferred voice call")
            value: UiStrings.yesNo(simCardsIface.preferredVoiceCall)
        }

        DetailItem {
            objectName: "preferredDataTransferItem"
            label: qsTr("Preferred data transfer")
            value: UiStrings.yesNo(simCardsIface.preferredDataTransfer)
        }
    }
}
