import QtQuick

Column {
    property string label: ""
    property string value: ""
    property string unit: ""
    property color iconColor: window.carInverted ? "black" : "white"
    spacing: 4

    Text {
        text: label
        color: window.carInverted ? "#888" : "#444"
        font.pixelSize: 11; font.capitalization: Font.AllUppercase
    }
    Row {
        spacing: 4
        Text {
            text: value
            color: iconColor
            font.pixelSize: 22; font.bold: true
        }
        Text {
            text: unit
            color: window.carInverted ? "#666" : "#333"
            font.pixelSize: 11
            anchors.bottom: parent.bottom; anchors.bottomMargin: 4
        }
    }
}
