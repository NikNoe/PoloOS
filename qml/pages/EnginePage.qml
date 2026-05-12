import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: enginePage

    // Theme helper properties
    readonly property color mainTextColor: window.carInverted ? "#111111" : "#FFFFFF"
    readonly property color subTextColor: window.carInverted ? "#555555" : "#888888"
    readonly property color bgAccent: window.carInverted ? "#E0E0E0" : "#1A1A1A"

    // RED OVERLAY for Limp Mode or Overheating
    Rectangle {
        anchors.fill: parent
        color: "#AA0000"
        opacity: (carCan.limpMode || carCan.overheat) ? 0.4 : 0
        visible: opacity > 0
        z: 10

        Text {
            anchors.centerIn: parent
            text: carCan.overheat ? "ENGINE OVERHEAT" : "LIMP MODE ACTIVE"
            color: "white" // Keep white for contrast against red
            font.pixelSize: 40; font.bold: true
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        // --- TOP: PRIMARY DRIVING DATA ---
        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 0.4
            spacing: 20

            // RPM GAUGE (Left)
            Rectangle {
                Layout.preferredWidth: 160; Layout.preferredHeight: 160; radius: 80
                color: "transparent"; border.color: carCan.rpm > 5500 ? "red" : subTextColor; border.width: 4
                Column {
                    anchors.centerIn: parent
                    Text { text: carCan.rpm; color: mainTextColor; font.pixelSize: 36; font.bold: true; anchors.horizontalCenter: parent.horizontalCenter }
                    Text { text: "RPM"; color: subTextColor; font.pixelSize: 12; anchors.horizontalCenter: parent.horizontalCenter }
                }
            }

            // SPEED & GEAR (Center)
            ColumnLayout {
                Layout.alignment: Qt.AlignCenter
                spacing: 0
                Text {
                    text: carCan.speed
                    color: mainTextColor; font.pixelSize: 80; font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                }
                Text {
                    text: "km/h"; color: subTextColor; font.pixelSize: 18
                    Layout.alignment: Qt.AlignHCenter
                }
                Rectangle {
                    Layout.preferredWidth: 50; Layout.preferredHeight: 50; radius: 5
                    color: window.carInverted ? "#333" : "#444"
                    Layout.alignment: Qt.AlignHCenter; Layout.topMargin: 10
                    Text {
                        anchors.centerIn: parent
                        text: carCan.gear === 0 ? "R" : (carCan.gear === 11 ? "N" : carCan.gear)
                        color: "white"; font.pixelSize: 30; font.bold: true
                    }
                }
            }

            // ENGINE LOAD (Right)
            VitalsItem {
                label: "Engine Load"; value: carCan.engineLoad; unit: "%"
                Layout.alignment: Qt.AlignVCenter
            }
        }

        // --- MIDDLE: PEDALS & THROTTLE ---
        ColumnLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height * 0.3
            spacing: 10

            Text { text: "DRIVE-BY-WIRE INPUTS"; color: subTextColor; font.bold: true; font.pixelSize: 12 }

            // Accelerator
            RowLayout {
                Text { text: "Pedal"; color: mainTextColor; Layout.preferredWidth: 70 }
                ProgressBar {
                    value: carCan.pedalPos / 100
                    Layout.fillWidth: true
                }
                Text { text: carCan.pedalPos + "%"; color: mainTextColor; Layout.preferredWidth: 40 }
            }

            // Throttle
            RowLayout {
                Text { text: "Throttle"; color: mainTextColor; Layout.preferredWidth: 70 }
                ProgressBar {
                    value: carCan.throttlePos / 100
                    Layout.fillWidth: true
                    // Use a darker cyan for light mode to maintain visibility
                    palette.highlight: window.carInverted ? "#007A99" : "cyan"
                }
                Text { text: carCan.throttlePos + "%"; color: mainTextColor; Layout.preferredWidth: 40 }
            }
        }

        // --- BOTTOM: CONSUMPTION & FLAGS ---
        Rectangle {
                Layout.fillWidth: true; Layout.preferredHeight: parent.height * 0.3
                color: bgAccent; radius: 10
                RowLayout {
                    anchors.fill: parent; anchors.margins: 15

                    // Consumption Column
                    ColumnLayout {
                        Text { text: "FUEL"; color: subTextColor; font.bold: true; font.pixelSize: 10 }
                        Text { text: carCan.fuelInst.toFixed(1) + " L/h"; color: mainTextColor; font.pixelSize: 20 }
                    }

                    Rectangle { width: 1; Layout.fillHeight: true; color: subTextColor; opacity: 0.2 }

                    // NEW: ENGINE & IGNITION FLAGS
                    ColumnLayout {
                        spacing: 8
                        Row {
                            spacing: 10
                            Rectangle { width: 12; height: 12; radius: 6; color: carCan.ignitionOn ? "#FFCC00" : "#333" }
                            Text { text: "IGNITION"; color: mainTextColor; font.pixelSize: 12; font.bold: carCan.ignitionOn }
                        }
                        Row {
                            spacing: 10
                            Rectangle { width: 12; height: 12; radius: 6; color: carCan.engineRunning ? "#4CD964" : "#333" }
                            Text { text: "ENGINE RUNNING"; color: mainTextColor; font.pixelSize: 12; font.bold: carCan.engineRunning }
                        }
                    }

                    Rectangle { width: 1; Layout.fillHeight: true; color: subTextColor; opacity: 0.2 }

                    // Systems Column
                    ColumnLayout {
                        Row {
                            spacing: 10
                            Rectangle { width: 12; height: 12; radius: 6; color: carCan.idleState ? "#4CD964" : subTextColor }
                            Text { text: "IDLE"; color: mainTextColor; font.pixelSize: 12 }
                        }
                        Row {
                            spacing: 10
                            Rectangle { width: 12; height: 12; radius: 6; color: carCan.cruiseActive ? "#5AC8FA" : subTextColor }
                            Text { text: "CRUISE"; color: mainTextColor; font.pixelSize: 12 }
                        }
                    }
                }
            }
        }
}

