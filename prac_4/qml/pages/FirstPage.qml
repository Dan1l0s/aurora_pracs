import QtQuick 2.0
import Sailfish.Silica 1.0
import myModule 1.0

Page {
    id: page
    allowedOrientations: Orientation.All

    MyCounter {
        id: myCounter
        onValueChanged: label.text = counter
    }
    Label {
        id: label
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 400
        text: myCounter.counter
    }
    Button {
        id: button1
        text: "Increment"
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 25
        onClicked: {
            myCounter.increment()
        }
    }
    Button {
        id: button2
        x: parent.width/2
        text: "Reset"
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: button1
        anchors.leftMargin: 75
        onClicked: {
            myCounter.reset()
        }
    }
}
