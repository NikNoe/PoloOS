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
}


