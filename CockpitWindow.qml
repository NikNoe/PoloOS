import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 400
    height: 850
    visible: true
    title: "VW Polo 9N3 Manual Control"
    color: "#121212"

    ScrollView {
        anchors.fill: parent
        ColumnLayout {
            width: parent.width - 30
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 15

            Text { text: "9N3 COCKPIT SIMULATOR"; color: "#00ccff"; font.bold: true; Layout.topMargin: 10 }

            // --- TRANSMISSION (Gearbox) ---
            GroupBox {
                title: "GEARBOX"; Layout.fillWidth: true
                RowLayout {
                    spacing: 10
                    Repeater {
                        model: [1, 2, 3, 4, 5]
                        Button {
                            text: modelData
                            Layout.fillWidth: true
                            palette.button: carCan.gear === modelData ? "#00ccff" : "#333"
                            onClicked: carCan.gear = modelData
                        }
                    }
                }
            }

            // --- CENTER CONSOLE (Heating & Wipers) ---
            GroupBox {
                title: "CENTER CONSOLE"; Layout.fillWidth: true
                ColumnLayout {
                    width: parent.width

                    CheckBox {
                        text: "Windshield Heating (Defrost)"; checked: carCan.windshieldHeater
                        onClicked: carCan.windshieldHeater = checked; palette.text: "white"
                    }

                    CheckBox {
                        text: "Interior Cabin Light"; checked: carCan.interiorLight
                        onClicked: carCan.interiorLight = checked; palette.text: "white"
                    }

                    Text { text: "Wiper Mode: " + ["OFF", "INTERMITTENT", "LOW", "HIGH"][carCan.wiperLevel]; color: "white" }
                    RowLayout {
                        Repeater {
                            model: ["OFF", "INT", "LOW", "HIGH"]
                            Button {
                                text: modelData; Layout.fillWidth: true
                                palette.button: carCan.wiperLevel === index ? "#ffcc00" : "#333"
                                onClicked: carCan.wiperLevel = index
                            }
                        }
                    }
                }
            }

            // --- CHASSIS CONTROLS ---
            GroupBox {
                title: "CHASSIS"; Layout.fillWidth: true
                ColumnLayout {
                    width: parent.width
                    Button {
                        text: "HANDBRAKE (P)"; Layout.fillWidth: true
                        palette.button: carCan.handbrake ? "red" : "#333"
                        onClicked: carCan.handbrake = !carCan.handbrake
                    }
                }
            }

            // --- RE-USE PREVIOUS SLIDERS (RPM/STEER) ---
            GroupBox {
                title: "ENGINE & STEERING"; Layout.fillWidth: true
                ColumnLayout {
                    width: parent.width
                    Text { text: "RPM: " + carCan.rpm; color: "white" }
                    Slider { from: 0; to: 7000; value: carCan.rpm; onMoved: carCan.rpm = value; Layout.fillWidth: true }

                    Text { text: "Steering: " + carCan.steeringAngle.toFixed(0) + "°"; color: "white" }
                    Slider { from: -450; to: 450; value: carCan.steeringAngle; onMoved: carCan.steeringAngle = value; Layout.fillWidth: true }
                }
            }
        }
    }
}
