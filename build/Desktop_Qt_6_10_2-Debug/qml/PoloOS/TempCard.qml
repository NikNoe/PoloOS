// TempCard.qml
import QtQuick
import QtQuick.Layouts

Rectangle {
    property string label: ""
    property real value: 0
    property color accent: "blue"

    Layout.fillWidth: true; Layout.preferredHeight: 80
    color: window.carInverted ? "#EEE" : "#222"
    radius: 8

    Rectangle {
        width: 4; anchors.left: parent.left; anchors.top: parent.top
        anchors.bottom: parent.bottom; color: accent; radius: 2
    }

    Column {
        anchors.centerIn: parent
        Text { text: label; color: "#888"; font.pixelSize: 10; anchors.horizontalCenter: parent.horizontalCenter }
        Text { text: value.toFixed(0) + "°C"; color: window.carInverted ? "#111" : "white"; font.pixelSize: 22; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
    }
}
