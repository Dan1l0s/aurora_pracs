import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    property string number1
    property string number2
    DialogHeader {
        acceptText: qsTr("Sum 2 numbers!")
    }

    TextField {
        id: num1
        anchors.centerIn: parent
        width: parent.width
        placeholderText: qsTr("Input second number (digits only!)")
        label: qsTr("First number")
    }
    TextField {
        id: num2
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: num1.bottom
        anchors.topMargin: 100
        width: parent.width
        placeholderText: qsTr("Input second number (digits only!)")
        label: qsTr("Second number")
    }
    onDone:
        if (result == DialogResult.Accepted)
        {
            number1 = num1.text
            number2 = num2.text
        }

}
