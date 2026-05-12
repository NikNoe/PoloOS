// EngineLive.qml
import QtQuick

Item {
    // No Rectangle background here!
    Column {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        Text {
            text: "LIVE TELEMETRY"
            font.pixelSize: 12
            font.weight: Font.Bold
            color: window.carInverted ? "#666666" : "#888888"
        }

        // Add your gauges or data here
        Text {
            text: "90°C OIL"
            font.pixelSize: 28
            color: window.carInverted ? "black" : "white"
        }
    }
}
