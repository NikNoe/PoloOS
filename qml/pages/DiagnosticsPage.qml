import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    id: diagPage

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 25
        spacing: 15

        // --- BUS HEALTH ROW ---
        RowLayout {
            spacing: 20
            BusStatusCard {
                title: "ENGINE BUS (500k)"; active: carCan.busEngineActive;
                fps: carCan.engineFps; errors: carCan.errorFrames
            }
            BusStatusCard {
                title: "COMFORT BUS (100k)"; active: carCan.busComfortActive;
                fps: carCan.comfortFps; errors: 0
            }
        }

        // --- ECU ONLINE STATUS ---
        Text { text: "NETWORK NODES"; color: "#888"; font.bold: true }
        RowLayout {
            spacing: 10
            EcuTag { name: "ECU"; online: carCan.ecuEngineOnline }
            EcuTag { name: "ABS"; online: carCan.ecuAbsOnline }
            EcuTag { name: "BCM"; online: carCan.ecuBodyOnline }
            EcuTag { name: "INSTR"; online: true }
        }

        // --- FAULT CODES (OBD) ---
        Rectangle {
            Layout.fillWidth: true; Layout.preferredHeight: 80
            color: "#1A1A1A"; radius: 8; border.color: "#333"
            RowLayout {
                anchors.fill: parent; anchors.margins: 15
                Column {
                    Text { text: "ACTIVE FAULT CODES"; color: "#E74C3C"; font.pixelSize: 10; font.bold: true }
                    Text { text: carCan.lastFaultCode === "" ? "NO DTC FOUND" : carCan.lastFaultCode; color: "white"; font.pixelSize: 22 }
                }
                Button {
                    text: "CLEAR CODES"; flat: true
                    onClicked: carCan.setLastFaultCode("")
                }
            }
        }

        // --- RAW VIEWER (LONG PRESS TO UNLOCK) ---
        Rectangle {
            id: rawViewer
            Layout.fillWidth: true; Layout.fillHeight: true
            color: "black"; radius: 5; border.color: "#222"
            clip: true

            Text {
                anchors.centerIn: parent
                text: "HOLD TO VIEW RAW TRAFFIC"
                color: "#444"
                visible: !rawContent.visible
            }

            Column {
                id: rawContent
                visible: false; anchors.fill: parent; anchors.margins: 10
                Text { text: "ID | DLC | DATA"; color: "#00FF00"; font.family: "Monospace" }
                Text { text: "0x280 | 8 | 01 22 00 1A FF 00 2B 11"; color: "#00FF00"; font.family: "Monospace" }
                Text { text: "0x320 | 8 | 00 00 00 00 00 00 00 00"; color: "#00FF00"; font.family: "Monospace" }
            }

            MouseArea {
                anchors.fill: parent
                onPressAndHold: rawContent.visible = true
                onReleased: rawContent.visible = false
            }
        }
    }
}
