/*******************************************************************************
**
** Copyright (C) 2022 ru.auroraos
**
** This file is part of the Моё приложение для ОС Аврора project.
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

Item {
    width: 720;
    height: 1080;
    Rectangle {
        id: redRect;
        x: 100;
        y: 100;
        width: 200;
        height: 200;
        color: "#FF0000";
    }
    Rectangle {
        id: greenRect;
        x: 300;
        y: 200;
        width: 200;
        height: 200;
        color: "#00FF00";
    }
    Rectangle {
        id: blueRect;
        x: 400;
        y: 100;
        width: 200;
        height: 200;
        color: "#0000FF";
        Text {
            text: "Hello world!"
            color: "#FFFFFF";
            anchors {
                centerIn: parent;
            }
        }
    }
    MouseArea {
        anchors.fill: parent;
        onClicked: blackRectAnim.start();
    }

    Rectangle {
        id: blackRect;
        x: 300;
        y: 600;
        width: 200;
        height: 200;
        color: "#000000";
        rotation: 0;
    }
    ParallelAnimation {
        id: blackRectAnim;
        PropertyAnimation {target: blackRect; property:"width"; to:100; duration:2000}
        PropertyAnimation {target: blackRect; property:"height"; to:400; duration:2000}
        PropertyAnimation {target: blackRect; property:"rotation"; to:45; duration:2000}
    }
}

//ApplicationWindow {
//    objectName: "applicationWindow"
//    initialPage: Qt.resolvedUrl("pages/MainPage.qml")
//    cover: Qt.resolvedUrl("cover/DefaultCoverPage.qml")
//    allowedOrientations: defaultAllowedOrientations
//}
