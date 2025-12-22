import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: window
    visible: true
    width: 1280
    height: 720
    title: "PoloOS - Tesla Style"
    color: "#050505" // Tesla Deep Black

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // --- LEFT PANE: Car Visualization ---
        Rectangle {
            Layout.preferredWidth: parent.width * 0.35
            Layout.fillHeight: true
            color: "transparent"

            ColumnLayout {
                anchors.centerIn: parent
                spacing: 20

                Text {
                    text: "Polo IV"
                    color: "white"
                    font.pixelSize: 28; font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                }

                // Placeholder for Car Image
                Rectangle {
                    width: 250; height: 400
                    color: "#1a1a1a"
                    radius: 20
                    Text { text: "Car Top View\n(Insert Polo Image)"; color: "gray"; anchors.centerIn: parent }
                }
            }
        }

        // --- RIGHT PANE: Maps & Media ---
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#111" // Slightly lighter gray
            radius: 15

            Text {
                text: "Navigation / Map View"
                color: "gray"
                anchors.centerIn: parent
            }
        }
    }

    // --- BOTTOM BAR: Controls ---
    footer: Rectangle {
        height: 90
        color: "black"
        RowLayout {
            anchors.fill: parent
            spacing: 50

            Button { text: "Temp 22.0°"; flat: true; font.pixelSize: 18 }
            Button { text: "Music"; flat: true }
            Button { text: "Phone"; flat: true }
            Button { text: "Settings"; flat: true }
        }
    }
}
