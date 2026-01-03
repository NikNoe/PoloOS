import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 450
    height: 900
    visible: true
    title: "9N3 Complete Simulator"
    color: "#0f0f0f"

    ScrollView {
        anchors.fill: parent
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn

        ColumnLayout {
            width: parent.width - 40
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20

            Text { text: "🕹️ 9N3 FULL TEST BENCH"; color: "#00FF00"; font.bold: true; font.pixelSize: 20; Layout.topMargin: 20 }

            // --- DRIVE & GEARS ---
            GroupBox {
                title: "POWERTRAIN"; Layout.fillWidth: true; palette.windowText: "white"
                ColumnLayout {
                    width: parent.width
                    Text { text: "RPM: " + carCan.rpm; color: "white" }
                    Slider { from: 0; to: 7000; value: carCan.rpm; onMoved: carCan.rpm = value; Layout.fillWidth: true }

                    Text { text: "Manual Gear: " + carCan.gear; color: "white" }
                    RowLayout {
                        Repeater {
                            model: [1, 2, 3, 4, 5]
                            Button {
                                text: modelData; Layout.fillWidth: true
                                palette.button: carCan.gear === modelData ? "#00AAFF" : "#333"
                                onClicked: carCan.gear = modelData
                            }
                        }
                    }
                }
            }

            // --- CHASSIS & STEERING ---
            GroupBox {
                title: "CHASSIS"; Layout.fillWidth: true; palette.windowText: "white"
                ColumnLayout {
                    width: parent.width
                    Text { text: "Steering Angle: " + carCan.steeringAngle.toFixed(0) + "°"; color: "white" }
                    Slider { from: -450; to: 450; value: carCan.steeringAngle; onMoved: carCan.steeringAngle = value; Layout.fillWidth: true }

                    Button {
                        text: "HANDBRAKE (P)"; Layout.fillWidth: true
                        palette.button: carCan.handbrake ? "red" : "#333"
                        onClicked: carCan.handbrake = !carCan.handbrake
                    }
                }
            }

            // --- LIGHTS & WIPERS ---
            GroupBox {
                title: "ENVIRONMENT CONTROLS"; Layout.fillWidth: true; palette.windowText: "white"
                ColumnLayout {
                    width: parent.width

                    RowLayout {
                        Button { text: "L Blinker"; onClicked: carCan.blinkerStatus = 1; Layout.fillWidth: true }
                        Button { text: "Off"; onClicked: carCan.blinkerStatus = 0; Layout.fillWidth: true }
                        Button { text: "R Blinker"; onClicked: carCan.blinkerStatus = 2; Layout.fillWidth: true }
                    }

                    Text { text: "Wiper Speed"; color: "white"; Layout.topMargin: 10 }
                    RowLayout {
                        Repeater {
                            model: ["OFF", "INT", "LOW", "HIGH"]
                            Button {
                                text: modelData; Layout.fillWidth: true
                                palette.button: carCan.wiperLevel === index ? "#FFCC00" : "#333"
                                onClicked: carCan.wiperLevel = index
                            }
                        }
                    }
                }
            }

            // --- COMFORT & INTERIOR ---
            GroupBox {
                title: "INTERIOR & COMFORT"; Layout.fillWidth: true; palette.windowText: "white"
                ColumnLayout {
                    width: parent.width
                    RowLayout {
                        CheckBox { text: "Windshield Heat"; checked: carCan.windshieldHeater;
                                   onClicked: carCan.windshieldHeater = checked; palette.text: "white" }
                        CheckBox { text: "Int. Light"; checked: carCan.interiorLight;
                                   onClicked: carCan.interiorLight = checked; palette.text: "white" }
                    }
                    CheckBox { text: "A/C System"; checked: carCan.acActive;
                               onClicked: carCan.acActive = checked; palette.text: "white" }

                    Text { text: "Windows: " + carCan.windowPos + "%"; color: "white" }
                    Slider { from: 0; to: 100; value: carCan.windowPos; onMoved: carCan.windowPos = value; Layout.fillWidth: true }
                }
            }

            // --- BODY ---
            GroupBox {
                title: "DOORS & LOCKS"; Layout.fillWidth: true; palette.windowText: "white"
                GridLayout {
                    columns: 2; width: parent.width
                    Button { text: "Front Left Door"; onClicked: carCan.doorFL = !carCan.doorFL; Layout.fillWidth: true }
                    Button { text: "Front Right Door"; onClicked: carCan.doorFR = !carCan.doorFR; Layout.fillWidth: true }
                    Button { text: carCan.isLocked ? "UNLOCK CAR" : "LOCK CAR"; Layout.columnSpan: 2; Layout.fillWidth: true;
                             onClicked: carCan.isLocked = !carCan.isLocked }
                }
            }

            Item { height: 40 } // Bottom padding
        }
    }
}
