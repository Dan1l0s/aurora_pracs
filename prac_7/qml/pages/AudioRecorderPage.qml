import QtQuick 2.6
import Sailfish.Silica 1.0
import QtMultimedia 5.6
import Multimedia 1.0
import "../assets"

Page {
    property string filePath: StandardPaths.documents + "/" + Qt.application.name + ".wav"

    AudioRecorder {
        id: audioRecorder
        outputLocation: filePath
        onStateChanged: {
            if (state === AudioRecorder.StoppedState) {
                audioPlayer.source = "";
                audioPlayer.source = filePath;
            }
        }
    }
    Audio {
        id: audioPlayer
        source: filePath
        autoLoad: true
    }
    Column {
        anchors.fill: parent
        spacing: Theme.paddingLarge

        PageHeader { title: qsTr("Audio recorder") }
        ValueDisplay {
            id: recordInfo
            label: qsTr("Recorded duration")
            value: qsTr("%1 s").arg((audioRecorder.duration || audioPlayer.duration) / 1000)
            width: parent.width
        }
        Slider {
            id: playInfo
            label: qsTr("Player position")
            width: parent.width
            minimumValue: 0
            maximumValue: audioPlayer.duration || 1
            value: audioPlayer.position
            valueText: qsTr("%1 s").arg(value / 1000)
            enabled: false
            down: true
            handleVisible: false
        }
    }
    Row {
        id: buttonsRow
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: Theme.paddingLarge
        }
        spacing: Theme.paddingLarge

        IconButton {
            id: recordStartButton
            icon.source: "image://theme/icon-m-call-recording-on"
            onClicked: audioRecorder.record()
        }
        IconButton {
            id: recordPauseButton
            icon.source: "image://theme/icon-m-pause"
            visible: false
            onClicked: audioRecorder.pause()
        }
        IconButton {
            id: recordStopButton
            icon.source: "image://theme/icon-m-call-recording-off"
            visible: false
            onClicked: audioRecorder.stop()
        }
        IconButton {
            id: playStartButton
            icon.source: "image://theme/icon-m-play"
            onClicked: audioPlayer.play()
        }
        IconButton {
            id: playPauseButton
            icon.source: "image://theme/icon-m-pause"
            visible: false
            onClicked: audioPlayer.pause()
        }
        IconButton {
            id: playStopButton
            icon.source: "image://theme/icon-m-clear"
            visible: false
            onClicked: audioPlayer.stop()
        }

        states: [
            State {
                when: audioRecorder.state === AudioRecorder.RecordingState

                PropertyChanges { target: recordStartButton; visible: false }
                PropertyChanges { target: recordPauseButton; visible: true }
                PropertyChanges { target: recordStopButton; visible: true }
                PropertyChanges { target: playStartButton; visible: false }
            },
            State {
                when: audioRecorder.state === AudioRecorder.PausedState

                PropertyChanges { target: recordStopButton; visible: true }
                PropertyChanges { target: playStartButton; visible: false }
            },
            State {
                when: audioPlayer.playbackState === Audio.PlayingState

                PropertyChanges { target: recordStartButton; visible: false }
                PropertyChanges { target: playStartButton; visible: false }
                PropertyChanges { target: playPauseButton; visible: true }
                PropertyChanges { target: playStopButton; visible: true }
                PropertyChanges { target: playInfo; down: false }
            },
            State {
                when: audioPlayer.playbackState === Audio.PausedState

                PropertyChanges { target: recordStartButton; visible: false }
                PropertyChanges { target: playStopButton; visible: true }
                PropertyChanges { target: playInfo; down: false }
            }
        ]
    }
}
