import QtQuick 2.0
import Sailfish.Silica 1.0
import myModule 1.0

Page {
    id: page
    allowedOrientations: Orientation.All

    MyList {
        id: myList
        onValueChanged: label.text = list
    }
    Label {
        id: label
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 400
        text: "Initial text!"
    }
    TextInput {
        id: input
        anchors.top: label.bottom
        anchors.topMargin: 30
        anchors.verticalCenter: parent.verticalCenter
        text: "Input text!"
    }
    Button {
        id: button1
        text: "Add string"
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 25
        onClicked: {
            myList.add_string(input.text)
        }
    }
    Button {
        id: button2
        x: parent.width / 2
        text: "Remove string"
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: button1
        anchors.leftMargin: 75
        onClicked: {
            myList.remove_string()
        }
    }
}
