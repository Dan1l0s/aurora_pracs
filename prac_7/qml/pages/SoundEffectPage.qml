import QtQuick 2.6
import Sailfish.Silica 1.0
import QtMultimedia 5.6

Page {
    SoundEffect {
        id: soundEffect
        // ToDo: set source to gun.wav in soundeffects folder
        source: "file:///usr/share/%1/soundeffects/gun.wav".arg(Qt.application.name)
        // ToDo: set volume controlled by volumeSlider
        volume: volumeSlider.value
        // ToDo: set loops controlled by slider
        loops: loopsSlider.value
    }
    PageHeader { title: qsTr("Sound Effect") }
    MouseArea {
        id: touchHandler
        anchors.fill: parent
        // ToDo: play sound effect or stop playing on clicked
        onClicked: {
            if (soundEffect.playing)
                    soundEffect.stop();
            else
                    soundEffect.play();
        }
    }
    Column {
        anchors {
            left: parent.left
            right: parent.right
            verticalCenter: parent.verticalCenter
        }
        spacing: Theme.paddingLarge

        Slider {
            id: volumeSlider
            width: parent.width
            label: qsTr("Volume level")
            value: 0.5
            valueText: value
            minimumValue: 0
            maximumValue: 1
            stepSize: 0.1
        }
        // ToDo: add slider to control count of loops
        Slider {
            id: loopsSlider
            width: parent.width
            label: qsTr("Loops amount")
            value: 1
            valueText: value
            minimumValue: 1
            maximumValue: 5
            stepSize: 1
        }
        // ToDo: add slider to show progress
        Slider {
            id: progressSlider
            width: parent.width
            label: qsTr("Loops progress")
            value: soundEffect.loops - soundEffect.loopsRemaining
            minimumValue: 0
            maximumValue: loopsSlider.value
            enabled: false
        }
    }
}
