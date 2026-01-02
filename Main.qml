import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick3D
import QtQuick3D.Helpers
import Polo.CAN 1.0


ApplicationWindow {
    id: window
    width: 1280
    height: 720
    visible: true
    color: "black"

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // --- LEFT PANE: 3D Polo Model ---
        Rectangle {
            Layout.preferredWidth: parent.width * 0.4
            Layout.fillHeight: true
            color: "#050505"


        // --- 1. NEW: Top Dashboard Bar ---
            Column {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 20
                spacing: 15
                z: 10 // Ensures this stays on top of the 3D car

                // Row for Safety Icons (Blinkers, Handbrake, Doors)
                Row {
                    spacing: 25
                    anchors.horizontalCenter: parent.horizontalCenter

                    // Left Blinker
                    DashboardIcon {
                        text: "◀"
                        activeColor: "#00FF00"
                        isActive: carCan.blinkerStatus === 1
                    }

                    // Handbrake (P)
                    DashboardIcon {
                        text: "(P)"
                        activeColor: "red"
                        isActive: carCan.handbrake
                    }

                    // Door State Icon
                    DashboardIcon {
                        text: "🚗" // You can replace with an SVG icon later
                        activeColor: "orange"
                        isActive: carCan.doorOpen
                        label: carCan.doorOpen ? "DOOR OPEN" : ""
                    }

                    // Right Blinker
                    DashboardIcon {
                        text: "▶"
                        activeColor: "#00FF00"
                        isActive: carCan.blinkerStatus === 2
                    }
                }

                // Fuel Level Progress Bar (Tesla Style)
                Row {
                    spacing: 10
                    anchors.horizontalCenter: parent.horizontalCenter

                    Text { text: "⛽"; color: "white"; font.pixelSize: 14 }

                    Rectangle {
                        width: 150
                        height: 6
                        color: "#333"
                        radius: 3

                        Rectangle {
                            width: (carCan.fuel / 100) * parent.width
                            height: parent.height
                            color: carCan.fuel < 15 ? "red" : "#00FF00"
                            radius: 3
                        }
                    }

                    Text {
                        text: carCan.fuel + "%"
                        color: "white"
                        font.pixelSize: 12
                        font.bold: true
                    }
                }
            }


            Item {
                anchors.fill: parent

                // --- BRAKE / STOP LIGHT INDICATOR ---
                Rectangle {
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 100
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: 200; height: 40
                    color: carCan.brakeActive ? "#FF0000" : "#110000"
                    border.color: carCan.brakeActive ? "#FF5555" : "#330000"
                    radius: 5
                    opacity: carCan.brakeActive ? 1.0 : 0.2

                    Text {
                        text: "BRAKE ACTIVE"
                        color: "white"
                        anchors.centerIn: parent
                        font.bold: true
                        visible: carCan.brakeActive
                    }
                }

                // --- COOL 9N3 STATUS ICONS (Right side of 3D car) ---
                Column {
                    anchors.right: parent.right
                    anchors.rightMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 20

                    // Seatbelt
                    DashboardIcon {
                        text: "ൠ" // Replace with seatbelt icon
                        activeColor: "red"
                        isActive: carCan.seatbelt
                        label: "SEATBELT"
                    }

                    // Washer Fluid (Classic VW warning)
                    DashboardIcon {
                        text: "Ⓦ"
                        activeColor: "yellow"
                        isActive: carCan.washerFluid
                        label: "WASHER LOW"
                    }
                }
            }

            View3D {
                id: carView
                anchors.fill: parent

                environment: SceneEnvironment {
                    clearColor: "#050505"
                    backgroundMode: SceneEnvironment.Color
                    antialiasingMode: SceneEnvironment.MSAA
                    antialiasingQuality: SceneEnvironment.High
                }

                // Node used as the pivot point for rotation
                Node {
                    id: carOrigin
                    // TESLA INITIAL POSITION: Slight tilt and front-side angle
                    eulerRotation: Qt.vector3d(-15, 45, 0)

                    Polo {
                        id: poloModel
                        // Scale adjusted so the car fits nicely in the left pane
                        scale: Qt.vector3d(1.2, 1.2, 1.2)
                    }

                    PerspectiveCamera {
                        id: carCamera
                        z: 550 // Distance from car
                        clipNear: 1
                        clipFar: 5000
                    }
                }

                // Navigation Controller: Allows dragging to rotate and scrolling to zoom
                OrbitCameraController {
                    anchors.fill: parent
                    origin: carOrigin
                    camera: carCamera
                    mouseEnabled: true

                    // Makes the rotation feel more natural
                    xSpeed: 0.15
                    ySpeed: 0.15
                }

                // Double tap the 3D area to reset the view to "Tesla Position"
                TapHandler {
                    onDoubleTapped: {
                        resetAnimation.start()
                    }
                }

                PropertyAnimation {
                    id: resetAnimation
                    target: carOrigin
                    property: "eulerRotation"
                    to: Qt.vector3d(-15, 45, 0)
                    duration: 1000
                    easing.type: Easing.InOutQuad
                }

                // Lights positioned to highlight the car's curves
                DirectionalLight {
                    eulerRotation.x: -30
                    eulerRotation.y: 45
                    brightness: 2.5
                }

                DirectionalLight {
                    eulerRotation.x: 30
                    eulerRotation.y: -135
                    brightness: 1.5
                }
            }
        }

        // --- RIGHT PANE: Car Vitals ---
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#111111"
            radius: 15

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 30
                spacing: 20

                Text {
                    text: "VEHICLE STATUS"
                    color: "#666"
                    font.pixelSize: 14
                    font.bold: true
                    Layout.alignment: Qt.AlignTop
                }

                // --- Data Grid ---
                GridLayout {
                    columns: 2
                    rowSpacing: 25
                    columnSpacing: 40
                    Layout.fillWidth: true

                    // Engine Speed
                    VitalsItem { label: "Engine RPM"; value: carCan.rpm; unit: "rpm" }

                    // Engine Temp
                    VitalsItem {
                        label: "Coolant Temp";
                        value: carCan.temp;
                        unit: "°C";
                        iconColor: carCan.temp > 100 ? "red" : "cyan"
                    }

                    // Fuel Level
                    VitalsItem { label: "Fuel Level"; value: carCan.fuel; unit: "%" }

                    // Consumption
                    VitalsItem { label: "Average"; value: carCan.consumption.toFixed(1); unit: "L/100km" }

                    // Door Status
                    VitalsItem { label: "Doors"; value: carCan.doorOpen ? "OPEN" : "CLOSED"; unit: "" }

                    // OBD Status
                    VitalsItem { label: "OBD Errors"; value: "0"; unit: "Active"; iconColor: "green" }
                }

                Item { Layout.fillHeight: true } // Spacer to push items to the top
            }
        }
    }

    // --- BOTTOM BAR: Controls (Unchanged) ---
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
    CanHandler {
            id: carCan
        }


        /*
        // Add this inside your Left Pane (over the 3D car)
        Text {
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 40
            text: carCan.rpm + " RPM"
            color: "white"
            font.pixelSize: 48
            font.family: "Orbitron" // Or any tech font
        }
        */

        component VitalsItem : Column {
            property string label: ""
            property string value: ""
            property string unit: ""
            property color iconColor: "white"

            spacing: 5
            Text { text: label; color: "#888"; font.pixelSize: 14 }
            Row {
                spacing: 5
                Text {
                    text: value;
                    color: iconColor;
                    font.pixelSize: 24;
                    font.bold: true
                }
                Text {
                    text: unit;
                    color: "#555";
                    font.pixelSize: 12;
                    anchors.bottom: parent.bottom;
                    anchors.bottomMargin: 4
                }
            }
        }

        component DashboardIcon : Column {
            property string text: ""
            property color activeColor: "white"
            property bool isActive: false
            property string label: ""

            spacing: 2
            Text {
                text: parent.text
                font.pixelSize: 24
                font.bold: true
                color: parent.isActive ? parent.activeColor : "#151515" // Dim when off
                Behavior on color { ColorAnimation { duration: 200 } }
            }
            Text {
                text: parent.label
                font.pixelSize: 8
                color: "white"
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
}


