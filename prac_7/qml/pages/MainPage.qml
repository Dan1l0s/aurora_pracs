import QtQuick 2.6
import Sailfish.Silica 1.0

Page {
    SilicaListView {
        id: sensorsListView
        anchors.fill: parent
        header: PageHeader { title: qsTr("Prac7") }
        delegate: ListItem {
            onClicked: pageStack.push(Qt.resolvedUrl('./%1Page.qml'.arg(model.page)));

            Label {
                text: model.name
                anchors {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    right: parent.right
                    margins: Theme.horizontalPageMargin
                }
                color: highlighted ? Theme.highlightColor : Theme.primaryColor
            }
        }
        model:  ListModel {
            ListElement {
                name: qsTr("Sound Effect")
                page: "SoundEffect"
            }
            ListElement {
                name: qsTr("Video player")
                page: "VideoPlayer"
            }
            ListElement {
                name: qsTr("Playlist")
                page: "Playlist"
            }
            ListElement {
                name: qsTr("Audio Recorder")
                page: "AudioRecorder"
            }
        }
    }
}
