import QtQuick 2.0
import Sailfish.Silica 1.0
import QtQuick.LocalStorage 2.0
import "../assets/Database.js" as JS
import "../assets"

Page {
    id: page
    allowedOrientations: Orientation.All

    SilicaFlickable {
        anchors.fill: parent
        Column {
            id: form
            width: parent.width
            anchors.top: parent.top

            Label {
                text: "Add note"
            }
            TextField {
                id: descInput
            }
            Row {
                spacing: 10
                Button {
                    id: saveButton
                    text: "Save"
                    onClicked: {
                        var tmp_rowid = form.insertrec()
                        if (tmp_rowid) {
                            form.setlistview(tmp_rowid)
                        } else {
                            statustext.text = "Failed to insert row"
                        }
                    }
                }
            }
            function insertrec() {
                var rowid = parseInt(JS.dbInsert(descInput.text), 10)
                return rowid;
            }

            function setlistview(tmp_rowid) {
                listView.model.append({"row_id": tmp_rowid, "test_description": descInput.text})
            }
            Label {
                id: statustext
                color: "red"
                font.bold: true
            }
        }
        Component {
            id: highlightBar
            Rectangle {
                width: listView.currentItem.width
                height: listView.currentItem.height
                color: "lightgreen"
            }
        }
        ListView {
            id: listView
            anchors.top: form.bottom
            anchors.bottom: parent.bottom
            anchors.margins: 10
            model: ListModel {
                id: listModel
                Component.onCompleted: {
                    JS.dbInit()
                    JS.dbReadAll()
                }
            }
            delegate: Label {
                height: 50
                text: test_description
                MouseArea {
                    anchors.fill: parent;
                    onClicked: {
                        JS.dbDelete(listModel.get(index).row_id)
                        listModel.remove(index);
                    }
                }
                Component.onCompleted: console.log(test_description)
            }

            header: Component {
                Label {
                    text: "Saved notes:"
                }
            }
        }
    }

}
