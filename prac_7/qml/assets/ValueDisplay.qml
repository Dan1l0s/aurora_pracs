import QtQuick 2.6
import Sailfish.Silica 1.0

Item {
    property alias label: textField.label
    property var value
    property bool valid: value
    property alias notValidText: textField.placeholderText

    height: textField.height

    TextField {
        id: textField
        text: valid ? "%1".arg(value) : ""
        color: Theme.highlightColor
        placeholderColor: color
        readOnly: true
        width: parent.width
    }
}
