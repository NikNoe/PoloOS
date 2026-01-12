import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: enginePage

    // RED OVERLAY for Limp Mode or Overheating
    Rectangle {
        anchors.fill: parent
        color: "#AA0000"
        opacity: (carCan.limpMode || carCan.overheat) ? 0.3 : 0
        visible: opacity > 0
        z: 10

        Text {
            anchors.centerIn: parent
            text: carCan.overheat ? "ENGINE OVERHEAT" : "LIMP MODE ACTIVE"
            color: "white"; font.pixelSize: 40; font.bold: true
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        // --- TOP: GAUGES ---
        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 0.4
            spacing: 30

            // RPM GAUGE
            Rectangle {
                Layout.preferredWidth: 200; Layout.preferredHeight: 200
                radius: 100
                color: "transparent"; border.color: carCan.rpm > 5500 ? "red" : "#444"; border.width: 8

                Column {
                    anchors.centerIn: parent
                    Text {
                        text: carCan.rpm; color: "white"; font.pixelSize: 42; font.bold: true
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text { text: "RPM"; color: "#888"; anchors.horizontalCenter: parent.horizontalCenter }
                }
            }

            // ENGINE LOAD GAUGE
            VitalsItem {
                label: "Engine Load"
                value: carCan.engineLoad
                unit: "%"
                Layout.alignment: Qt.AlignVCenter
            }
        }

        // --- MIDDLE: PEDALS & THROTTLE ---
        ColumnLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 0.3
            spacing: 10

            Text { text: "DRIVE-BY-WIRE INPUTS"; color: "#888"; font.bold: true; font.pixelSize: 12 }

            // Accelerator
            RowLayout {
                Text { text: "Pedal"; color: "white"; Layout.preferredWidth: 70 }
                ProgressBar {
                    value: carCan.pedalPos / 100
                    Layout.fillWidth: true
                    background: Rectangle { color: "#222"; radius: 4 }
                }
                Text { text: carCan.pedalPos + "%"; color: "white"; Layout.preferredWidth: 40 }
            }

            // Throttle
            RowLayout {
                Text { text: "Throttle"; color: "white"; Layout.preferredWidth: 70 }
                ProgressBar {
                    value: carCan.throttlePos / 100
                    Layout.fillWidth: true
                    palette.highlight: "cyan"
                    background: Rectangle { color: "#222"; radius: 4 }
                }
                Text { text: carCan.throttlePos + "%"; color: "white"; Layout.preferredWidth: 40 }
            }
        }

        // --- BOTTOM: CONSUMPTION & FLAGS ---
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 0.3
            color: window.carInverted ? "#EEE" : "#111"
            radius: 10

            RowLayout {
                anchors.fill: parent
                anchors.margins: 15

                // Fuel Stats
                ColumnLayout {
                    Text { text: "FUEL ECONOMY"; color: "#888"; font.bold: true; font.pixelSize: 10 }
                    Text { text: carCan.fuelInst.toFixed(1) + " L/100km"; color: "white"; font.pixelSize: 20 }
                    Text { text: "AVG: " + carCan.fuelAvg.toFixed(1); color: "#666" }
                }

                // Separator (The fix for your "Divider" issue)
                Rectangle { width: 1; Layout.fillHeight: true; color: "#333" }

                // Torque Info
                ColumnLayout {
                    VitalsItem { label: "Actual Torque"; value: carCan.torqueActual; unit: "Nm" }
                    VitalsItem { label: "Req. Torque"; value: carCan.torqueRequest; unit: "Nm" }
                }

                // Flags
                ColumnLayout {
                    Layout.alignment: Qt.AlignRight
                    Row {
                        spacing: 10
                        Rectangle { width: 12; height: 12; radius: 6; color: carCan.idleState ? "green" : "#333" }
                        Text { text: "IDLE"; color: "white"; font.pixelSize: 12 }
                    }
                    Row {
                        spacing: 10
                        Rectangle { width: 12; height: 12; radius: 6; color: carCan.cruiseActive ? "cyan" : "#333" }
                        Text { text: "CRUISE"; color: "white"; font.pixelSize: 12 }
                    }
                }
            }
        }
    }
}
