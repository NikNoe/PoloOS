import QtQuick
import QtQuick.Layouts

Rectangle {
    id: root

    // Properties to make the tag dynamic
    property string name: "ECU"
    property bool online: false

    // Visual Settings
    Layout.preferredWidth: 80
    Layout.preferredHeight: 30
    radius: 4

    // Background color: Green if online, Dark/Red if offline
    color: online ? "#27AE60" : (window.carInverted ? "#DDD" : "#333")
    opacity: online ? 1.0 : 0.6

    // Smooth transition when ECU status changes
    Behavior on color { ColorAnimation { duration: 300 } }

    Row {
        anchors.centerIn: parent
        spacing: 6

        // Small "LED" circle
        Rectangle {
            width: 8; height: 8; radius: 4
            anchors.verticalCenter: parent.verticalCenter
            color: online ? "#2ECC71" : "#E74C3C"
        }

        Text {
            text: root.name
            color: online ? "white" : (window.carInverted ? "#555" : "#888")
            font.pixelSize: 11
            font.bold: true
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
