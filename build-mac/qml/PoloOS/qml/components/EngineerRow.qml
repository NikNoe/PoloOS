// EngineerRow.qml
import QtQuick
import QtQuick.Layouts

RowLayout {
    property string label: ""
    property string value: ""
    property bool isCode: false

    Text {
        text: label.padEnd(15, ' ')
        color: "#888"
        font.family: "Monospace"
        font.pixelSize: 14
        Layout.preferredWidth: 150
    }

    Text {
        text: isCode ? "[" + value + "]" : value
        color: isCode ? "#3498DB" : "white"
        font.family: "Monospace"
        font.pixelSize: 14
        font.bold: !isCode
    }
}
