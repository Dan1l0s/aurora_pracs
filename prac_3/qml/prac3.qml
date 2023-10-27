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
import QtQuick.XmlListModel 2.0

ApplicationWindow {
    objectName: "applicationWindow"
    initialPage: Qt.resolvedUrl("pages/MainPage.qml")
    cover: Qt.resolvedUrl("cover/DefaultCoverPage.qml")
    allowedOrientations: defaultAllowedOrientations

    ListView {
        id: listView;
        y: 150;
        width: parent.width;
        height: parent.height / 3;
        model: ListModel {
            id: dataModel;
            ListElement {
                color: "red"
                text: "Red"
                textColor: "white"
            }
            ListElement {
                color: "green"
                text: "Green"
                textColor: "white"
            }
            ListElement {
                color: "blue"
                text: "Blue"
                textColor: "white"
            }
        }
        delegate: 
            Rectangle {
            width: parent.width;
            height: 100;
            color: model.color;
            Text {
                anchors.centerIn: parent;
                text: model.text;
                color: model.textColor;
            }
            MouseArea {
                anchors.fill: parent;
                onClicked: {
                    dataModel.remove(index);
                }
            }
        }
    }

    Button {
        id: addButton;
        width: parent.width - 20;
        anchors.left: parent.left;
        anchors.leftMargin: 10;
        anchors.top: listView.bottom;
        anchors.topMargin: 100;
        property int index: 3;
        Text {
            text: "Add a rectangle!";
            color: "black"
            anchors.centerIn: parent;
        }

        onClicked: {
            index++;
            var rect_color = ["red", "green", "blue"][Math.floor(Math.random() * 3)]
            dataModel.append({
                color: rect_color,
                text: rect_color + " rectangle #" + index,
                textColor: "white"
            })
        }
    }

    XmlListModel {
        id: xmlModel;
        source: "http://www.cbr.ru/scripts/XML_daily.asp";
        query: "/ValCurs/Valute"
        XmlRole { name: "name"; query: "Name/string()" }
        XmlRole { name: "value"; query: "Value/string()" }
        XmlRole { name: "code"; query: "CharCode/string()" }
    }

    ListView {
        id: listView2;
        anchors.top: addButton.bottom;
        anchors.topMargin: 10;
        width: parent.width;
        height: parent.height - 300 - addButton.height;
        model: xmlModel;
        delegate: Rectangle {
            width: parent.width;
            height: 50;
            color: "white";
            Text {
                anchors.centerIn: parent;
                text: model.name + " (" + model.code + "): " + model.value + " RUB";
            }
        }
    }
}
