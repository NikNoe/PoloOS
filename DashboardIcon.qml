import QtQuick

Column {
    property string text: ""
    property color activeColor: "white"
    property bool isActive: false
    property string label: ""
    spacing: 2

    Text {
        text: parent.text
        font.pixelSize: 26; font.bold: true
        // If not active, it uses a dim color that looks good in both themes
        color: parent.isActive ? parent.activeColor : (window.carInverted ? "#d0d0d0" : "#1a1a1a")
        Behavior on color { ColorAnimation { duration: 250 } }
    }
    Text {
        text: parent.label
        font.pixelSize: 9; color: "#666"
        anchors.horizontalCenter: parent.horizontalCenter
        visible: parent.isActive
    }
}
