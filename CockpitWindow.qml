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

            GroupBox {
                title: "ENGINE PERFORMANCE"; Layout.fillWidth: true
                ColumnLayout {
                    width: parent.width

                    RowLayout {
                        Label { text: "Accelerator"; color: "white" }
                        Slider {
                            from: 0; to: 100; value: carCan.pedalPos
                            onMoved: {
                                carCan.setPedalPos(value)
                                // Simulate engine response: Throttle follows pedal with slight delay/offset
                                carCan.setThrottlePos(value * 0.95)
                                carCan.setRpm(800 + (value * 50))
                            }
                            Layout.fillWidth: true
                        }
                    }

                    RowLayout {
                        CheckBox { text: "Limp Mode"; checked: carCan.limpMode; onToggled: carCan.setLimpMode(checked) }
                        CheckBox { text: "Overheat"; checked: carCan.overheat; onToggled: carCan.setOverheat(checked) }
                        CheckBox { text: "Cruise"; checked: carCan.cruiseActive; onToggled: carCan.setCruiseActive(checked) }
                    }
                }
            }

            // --- CHASSIS & STEERING ---
            GroupBox {
                title: "CHASSIS & DYNAMICS";
                Layout.fillWidth: true;
                palette.windowText: "white"

                ColumnLayout {
                    width: parent.width
                    spacing: 15

                    // 1. Steering Control
                    ColumnLayout {
                        Layout.fillWidth: true
                        Text {
                            text: "Steering Angle: " + carCan.steeringAngle.toFixed(0) + "°"
                            color: "white"
                        }
                        Slider {
                            from: -450; to: 450;
                            value: carCan.steeringAngle
                            // Use the setter function for proper signal emission
                            onMoved: carCan.setSteeringAngle(value)
                            Layout.fillWidth: true
                        }
                    }

                    // 2. Wheel Speeds (FL, FR, RL, RR)
                    Text { text: "Wheel Speeds (km/h)"; color: "#888"; font.pixelSize: 12 }
                    GridLayout {
                        columns: 2; rowSpacing: 10; columnSpacing: 10; Layout.fillWidth: true

                        ColumnLayout {
                            Label { text: "Front Left"; color: "white"; font.pointSize: 8 }
                            Slider { from: 0; to: 250; value: carCan.wheelFL; onMoved: carCan.setWheelFL(value); Layout.fillWidth: true }
                        }
                        ColumnLayout {
                            Label { text: "Front Right"; color: "white"; font.pointSize: 8 }
                            Slider { from: 0; to: 250; value: carCan.wheelFR; onMoved: carCan.setWheelFR(value); Layout.fillWidth: true }
                        }
                        ColumnLayout {
                            Label { text: "Rear Left"; color: "white"; font.pointSize: 8 }
                            Slider { from: 0; to: 250; value: carCan.wheelRL; onMoved: carCan.setWheelRL(value); Layout.fillWidth: true }
                        }
                        ColumnLayout {
                            Label { text: "Rear Right"; color: "white"; font.pointSize: 8 }
                            Slider { from: 0; to: 250; value: carCan.wheelRR; onMoved: carCan.setWheelRR(value); Layout.fillWidth: true }
                        }
                    }

                    // 3. Safety Systems & Braking
                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 10

                        Button {
                            text: "ABS"; checkable: true; checked: carCan.absActive
                            onToggled: carCan.setAbsActive(checked)
                            Layout.fillWidth: true
                        }
                        Button {
                            text: "ESP"; checkable: true; checked: carCan.espActive
                            onToggled: carCan.setEspActive(checked)
                            Layout.fillWidth: true
                        }
                        Button {
                            text: "TCS"; checkable: true; checked: carCan.tractionActive
                            onToggled: carCan.setTractionActive(checked)
                            Layout.fillWidth: true
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Button {
                            text: "BRAKE PEDAL"
                            highlighted: carCan.brakePressed
                            onPressed: carCan.setBrakePressed(true)
                            onReleased: carCan.setBrakePressed(false)
                            Layout.fillWidth: true
                        }
                        Button {
                            text: carCan.handbrake ? "HANDBRAKE (ON)" : "HANDBRAKE (OFF)"
                            palette.button: carCan.handbrake ? "red" : "#444"
                            onClicked: carCan.setHandbrake(!carCan.handbrake)
                            Layout.fillWidth: true
                        }
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

            // --- SAFETY SECTION ---
            GroupBox {
                title: "SAFETY & PASSENGERS";
                Layout.fillWidth: true;
                palette.windowText: "white"

                RowLayout {
                    width: parent.width
                    Button {
                        text: "Driver Belt"
                        highlighted: carCan.beltDriver
                        onClicked: carCan.setBeltDriver(!carCan.beltDriver)
                        Layout.fillWidth: true
                    }
                    Button {
                        text: "Pass. Belt"
                        highlighted: carCan.beltPassenger
                        onClicked: carCan.setBeltPassenger(!carCan.beltPassenger)
                        Layout.fillWidth: true
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
                title: "DOORS & LOCKS";
                Layout.fillWidth: true;
                palette.windowText: "white"

                GridLayout {
                    columns: 2;
                    width: parent.width
                    rowSpacing: 10
                    columnSpacing: 10

                    // FRONT DOORS
                    Button {
                        text: carCan.doorFL ? "CLOSE FL" : "OPEN FL"
                        highlighted: carCan.doorFL
                        // CRITICAL: Use the setter function so C++ emits the signal!
                        onClicked: carCan.setDoorFL(!carCan.doorFL)
                        Layout.fillWidth: true
                    }
                    Button {
                        text: carCan.doorFR ? "CLOSE FR" : "OPEN FR"
                        highlighted: carCan.doorFR
                        onClicked: carCan.setDoorFR(!carCan.doorFR)
                        Layout.fillWidth: true
                    }

                    // REAR DOORS (New for your 4-door setup)
                    Button {
                        text: carCan.doorRL ? "CLOSE RL" : "OPEN RL"
                        highlighted: carCan.doorRL
                        onClicked: carCan.setDoorRL(!carCan.doorRL)
                        Layout.fillWidth: true
                    }
                    Button {
                        text: carCan.doorRR ? "CLOSE RR" : "OPEN RR"
                        highlighted: carCan.doorRR
                        onClicked: carCan.setDoorRR(!carCan.doorRR)
                        Layout.fillWidth: true
                    }

                    // TRUNK & LOCKS
                    Button {
                        text: carCan.trunk ? "CLOSE TRUNK" : "OPEN TRUNK"
                        highlighted: carCan.trunk
                        onClicked: carCan.setTrunk(!carCan.trunk)
                        Layout.fillWidth: true
                    }

                    Button {
                        text: carCan.isLocked ? "UNLOCK CAR" : "LOCK CAR"
                        palette.buttonText: carCan.isLocked ? "orange" : "white"
                        Layout.fillWidth: true
                        onClicked: carCan.setIsLocked(!carCan.isLocked)
                    }
                }
            }

            Item { height: 40 } // Bottom padding
        }
    }
}
