import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: energyPage

    readonly property color mainText: window.carInverted ? "#111" : "#FFF"
    readonly property color cardBg: window.carInverted ? "#F5F5F5" : "#1A1A1A"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        // --- TOP: RANGE & FUEL ---
        RowLayout {
            spacing: 20
            Layout.fillWidth: true

            // Inside EnergyPage.qml
            Rectangle {
                Layout.fillWidth: true; Layout.preferredHeight: 100
                // Changes to Orange if range < 100km, Red if < 50km
                color: carCan.rangePossible < 50 ? "#C0392B" : (carCan.rangePossible < 100 ? "#D35400" : "#27AE60")
                radius: 12

                Behavior on color { ColorAnimation { duration: 500 } }

                Column {
                    anchors.centerIn: parent
                    Text { text: "ESTIMATED RANGE"; color: "white"; font.pixelSize: 12; font.bold: true }
                    Text { text: carCan.rangePossible.toFixed(0) + " km"; color: "white"; font.pixelSize: 32; font.bold: true }
                }
            }

            Rectangle {
                Layout.fillWidth: true; Layout.preferredHeight: 100
                color: cardBg; radius: 12; border.color: "#333"
                Column {
                    anchors.centerIn: parent
                    Text { text: "TO FILL UP"; color: "#888"; font.pixelSize: 12 }
                    Text { text: carCan.fuelToFill + " L"; color: mainText; font.pixelSize: 32; font.bold: true }
                }
            }
        }

        // --- MIDDLE: TEMPERATURES (Cards with Gradients) ---
        Text { text: "THERMAL MANAGEMENT"; color: "#888"; font.bold: true }
        GridLayout {
            columns: 3; Layout.fillWidth: true; rowSpacing: 10; columnSpacing: 10

            // Coolant Card
            TempCard {
                label: "Coolant"; value: carCan.tempCoolant;
                accent: carCan.tempCoolant > 105 ? "#E74C3C" : (carCan.tempCoolant > 75 ? "#2ECC71" : "#3498DB")
            }
            TempCard { label: "Oil"; value: carCan.tempOil; accent: "#F39C12" }
            TempCard { label: "Ambient"; value: carCan.tempAmbient; accent: "#95A5A6" }
            TempCard { label: "Intake"; value: carCan.tempIntake; accent: "#3498DB" }
            TempCard { label: "Fuel"; value: carCan.tempFuel; accent: "#D35400" }
        }

        // --- BOTTOM: ELECTRICAL ---
        Rectangle {
            Layout.fillWidth: true; Layout.preferredHeight: 120
            color: cardBg; radius: 12

            RowLayout {
                anchors.fill: parent; anchors.margins: 20

                // Battery Icon & Voltage
                RowLayout {
                    spacing: 15
                    Image {
                        source: "icons/battery.svg" // Replace with your icon
                        width: 40; height: 40
                        visible: true
                    }
                    Column {
                        Text { text: carCan.batteryVoltage.toFixed(1) + " V"; color: mainText; font.pixelSize: 28; font.bold: true }
                        Text {
                            text: carCan.altCharging ? "CHARGING" : "DISCHARGING"
                            color: carCan.altCharging ? "#2ECC71" : "#E74C3C"
                            font.bold: true; font.pixelSize: 10
                        }
                    }
                }

                // Simple Graph Placeholder
                Rectangle {
                    Layout.fillWidth: true; Layout.fillHeight: true
                    color: "#111"; radius: 5; opacity: 0.5
                    Text { anchors.centerIn: parent; text: "[ Consumption Graph ]"; color: "#444" }
                }
            }
        }
    }
}
