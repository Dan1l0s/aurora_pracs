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
import QtMultimedia 5.5
import "../../components"
import "../../js/NetworkUiStrings.js" as NetworkServiceUI
import ru.omp.SystemInfo 1.0

ListViewPage {
    id: wlanInfoPage
    objectName: "wlanInfoPage"
    model: networkServiceModel
    delegate: itemDelegate

    CDBTechnologyModel { id: networkServiceModel; objectName: "networkServiceModel"; name: "wifi" }

    PullDownMenu {
        objectName: "pullDownMenu"
        quickSelect: true

        MenuItem {
            objectName: "updateItem"
            text: qsTr("Update")
            onClicked: networkServiceModel.requestScan()
        }
    }

    ViewPlaceholder {
        objectName: "placeholder"
        enabled: !networkServiceModel.powered || !networkServiceModel.available
        text: networkServiceModel.powered
              ? qsTr("The WLAN is not available")
              : qsTr("The WLAN is not powered")
        hintText: networkServiceModel.powered ? "" : qsTr("Turn the WLAN on")
    }

    Component {
        id: itemDelegate

        NetworkServiceItem {
            objectName: "wlanItem%1".arg(index)
            title: modelData.name
            networkService: modelData
        }
    }
}
