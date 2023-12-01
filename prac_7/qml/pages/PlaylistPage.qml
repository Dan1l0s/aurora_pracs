import QtQuick 2.6
import Sailfish.Silica 1.0
import QtMultimedia 5.6


Page {
    property var metaBySource: new Object

    Audio {
        id: audioPlayer
        autoLoad: false
        playlist: playlist
    }
    Playlist { id: playlist }
    SilicaListView {
        id: playlistView
        anchors { fill: parent; bottomMargin: buttonsRow.height }
        header: PageHeader { title: qsTr("Playlist") }
        model: playlist
        delegate: ListItem {
            menu: ContextMenu {
                MenuItem {
                    text: qsTr("Remove")
                    onClicked: playlist.removeItem(model.index)
                }
            }
            onClicked: {
                playlist.currentIndex = model.index;
                audioPlayer.play();
            }

            Label {
                text: metaBySource[source].title
                font.bold: model.index === playlist.currentIndex
                anchors {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    right: parent.right
                    margins: Theme.horizontalPageMargin
                }
                color: highlighted ? Theme.highlightColor : Theme.primaryColor
            }
        }

        PullDownMenu {
            quickSelect: true

            MenuItem {
                text: qsTr("Select music")
                onClicked: {
                    var musicPicker = pageStack.push("Sailfish.Pickers.MultiMusicPickerDialog");
                    musicPicker.accepted.connect(function () {
                        playlist.clear();
                        metaBySource = new Object;
                        for (var iSelectedItem = 0; iSelectedItem < musicPicker.selectedContent.count; ++iSelectedItem) {
                            var selectedItem = musicPicker.selectedContent.get(iSelectedItem);
                            metaBySource[selectedItem.url] = {
                                title: selectedItem.title,
                                fileName: selectedItem.fileName,
                                filePath: selectedItem.filePath,
                                mimeType: selectedItem.mimeType
                            }
                            playlist.addItem(selectedItem.url);
                        }
                        audioPlayer.play();
                    });
                    musicPicker.rejected.connect(function () {
                        playlist.clear()
                    });
                }
            }
        }
    }
    Slider {
        id: playInfo
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 300
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

    Row {
        id: buttonsRow
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: playInfo.bottom
            topMargin: Theme.paddingMedium
            //            bottom: parent.bottom
//            bottomMargin: Theme.paddingLarge
        }
        spacing: Theme.paddingLarge

        IconButton {
            icon.source: "image://theme/icon-m-shuffle"
            onClicked: playlist.shuffle()
        }
        IconButton {
            icon.source: "image://theme/icon-m-previous"
            onClicked: playlist.previous()
        }
        IconButton {
            icon.source: "image://theme/icon-m-next"
            onClicked: playlist.next()
        }
    }
}
