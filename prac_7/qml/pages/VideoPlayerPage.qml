import QtQuick 2.6
import Sailfish.Silica 1.0
import QtMultimedia 5.6

Page {
    allowedOrientations: Orientation.All
    // ToDo: pause playback when the page is not active
    onStatusChanged: if (status === PageStatus.Deactivating) player.pause

    SilicaFlickable {
        anchors.fill: parent

        Video {
            id: player
            width: parent.width
            height: parent.height
            autoPlay: true
            // ToDo: change progress slider value when position changed
            onPositionChanged: playbackSlider.value = position

            MouseArea {
                anchors.fill: parent
                // ToDo: play or pause on clicked
                onClicked: {
                    if (player.playbackState === MediaPlayer.PlayingState)
                        player.pause();
                    else
                        player.play();
                }
            }
        }
        PullDownMenu {
            id: videoSelectMenu
            quickSelect: true

            // ToDo: add item to call video picker
            MenuItem {
                text: qsTr("Select a video")
                onClicked: {
                    var videoPicker = pageStack.push('Sailfish.Pickers.VideoPickerPage', { allowedOrientations: Orientation.All });
                    videoPicker.selectedContentChanged.connect(function () {
                        player.source = videoPicker.selectedContent;
                        player.play();
                    });
                }
            }
        }
    }
    // ToDo: add silder to control playback
    Slider {
        id: positionSlider
        anchors {
            left: parent.left;
            right: parent.right
            bottom: parent.bottom
            bottomMargin: Theme.paddingLarge
        }
        minimumValue: 0
        maximumValue: player.duration || 1
        onReleased: player.seek(value)
    }
}
