import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    PageHeader { id: header }
    id: page
    allowedOrientations: Orientation.All

    Label {
        id: label
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 200
        text: "Initial text"
    }
    Button {
        id: button1
        text: "Button"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: label.bottom
        anchors.topMargin: 100
        onPressed: {
            label.text = "Pressed!"
        }
        onReleased: {
            label.text = "Released!"
        }
    }

    Label {
        id: label2
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: button1.bottom
        anchors.topMargin: 200
        text: "Initial text"
    }
    Button {
        id: button2
        text: "Calculate!"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: label2.bottom
        anchors.topMargin: 100
        onClicked: {
            var dialog = pageStack.push(Qt.resolvedUrl("DialogPage.qml"));

             dialog.accepted.connect(function()
             {
                var num1 = parseInt(dialog.number1);
                var num2 = parseInt(dialog.number2);
                if (isNaN(num1) || isNaN(num2))
                    label2.text = "Last answer: undefined!";
                else
                    label2.text = "Last answer: " + (num1 + num2);
             });

        }
    }
}
