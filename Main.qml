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

    // The C++ Logic Bridge
    CanHandler {
        id: carCan
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // ==========================================
        // --- LEFT PANE: 3D Polo Model & Safety ---
        // ==========================================
        Rectangle {
            Layout.preferredWidth: parent.width * 0.45
            Layout.fillHeight: true
            color: "#050505"

            // --- 1. Top Dashboard Bar (Safety) ---
            Column {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 20
                spacing: 15
                z: 10

                Row {
                    spacing: 25
                    anchors.horizontalCenter: parent.horizontalCenter

                    DashboardIcon { text: "◀"; activeColor: "#00FF00"; isActive: carCan.blinkerStatus === 1 }
                    DashboardIcon { text: "(P)"; activeColor: "red"; isActive: carCan.handbrake; label: "BRAKE" }
                    DashboardIcon { text: "☼"; activeColor: "#3366FF"; isActive: carCan.highBeam; label: "BEAM" }
                    DashboardIcon { text: "▶"; activeColor: "#00FF00"; isActive: carCan.blinkerStatus === 2 }
                }

                // Tesla-style Fuel Line
                Row {
                    spacing: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text { text: "⛽"; color: "white"; font.pixelSize: 14 }
                    Rectangle {
                        width: 150; height: 6; color: "#333"; radius: 3
                        Rectangle {
                            width: (carCan.fuel / 100) * parent.width
                            height: parent.height; radius: 3
                            color: carCan.fuel < 15 ? "red" : "#00FF00"
                        }
                    }
                    Text { text: carCan.fuel + "%"; color: "white"; font.pixelSize: 12; font.bold: true }
                }
            }

            // --- 2. 3D Car View ---
            View3D {
                id: carView
                anchors.fill: parent

                environment: SceneEnvironment {
                    clearColor: "#050505"
                    backgroundMode: SceneEnvironment.Color
                    antialiasingMode: SceneEnvironment.MSAA
                    antialiasingQuality: SceneEnvironment.High
                }

                // --- 1. The Pivot Node ---
                Node {
                    id: carOrigin

                    // Independent properties (Not linked to carCan)
                    property real pitch: -15
                    property real yaw: 45
                    property real roll: 0

                    eulerRotation: Qt.vector3d(pitch, yaw, roll)

                    // The Car Mesh
                    Polo { // Using your Polo component name
                        id: poloModel
                        scale: Qt.vector3d(1.2, 1.2, 1.2)
                    }

                    // --- 2. Independent Showroom Animation ---
                    NumberAnimation on yaw {
                        from: 0
                        to: 360
                        duration: 20000 // 20 seconds for a slow, smooth spin
                        loops: Animation.Infinite
                        running: !mouseArea.pressed // Stops spinning when you touch it
                    }
                }

                // --- 3. Camera Definition (Required) ---
                PerspectiveCamera {
                    id: carCamera
                    z: 550
                    clipNear: 1
                    clipFar: 5000
                }

                // --- 4. Lights ---
                DirectionalLight {
                    eulerRotation.x: -30
                    eulerRotation.y: 45
                    brightness: 2.0
                }

                // --- 5. Controls ---
                OrbitCameraController {
                    anchors.fill: parent
                    origin: carOrigin
                    camera: carCamera
                    mouseEnabled: true
                }

                // Transparent overlay to detect when the user is interacting
                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    propagateComposedEvents: true
                    onPressed: (mouse) => mouse.accepted = false // Let events pass to OrbitController
                }
            }

            // --- 3. Brake/STOP Overlay ---
            Rectangle {
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 110
                anchors.horizontalCenter: parent.horizontalCenter
                width: 160; height: 34
                color: "#AA0000"
                radius: 17
                visible: carCan.brakeActive
                Text { text: "STOP"; color: "white"; anchors.centerIn: parent; font.bold: true }
            }
        }

        // ==========================================
        // --- RIGHT PANE: Full Vehicle Vitals ---
        // ==========================================
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#0f0f0f"
            radius: 15

            Flickable {
                anchors.fill: parent
                contentHeight: vitalsColumn.height + 60
                clip: true
                ScrollBar.vertical: ScrollBar { }

                ColumnLayout {
                    id: vitalsColumn
                    width: parent.width - 60
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 30
                    spacing: 25

                    Text { text: "VEHICLE STATUS"; color: "#444"; font.pixelSize: 12; font.bold: true }

                    GridLayout {
                        columns: 2
                        rowSpacing: 30
                        columnSpacing: 40
                        Layout.fillWidth: true

                        // --- SECTION: PERFORMANCE ---
                        VitalsItem { label: "Engine RPM"; value: carCan.rpm; unit: "rpm" }
                        VitalsItem { label: "Coolant"; value: carCan.temp; unit: "°C"; iconColor: carCan.temp > 105 ? "red" : "cyan" }
                        VitalsItem { label: "Steering"; value: carCan.steeringAngle.toFixed(1); unit: "°" }
                        VitalsItem { label: "Fuel Vol"; value: carCan.fuelLiters.toFixed(1); unit: "L" }

                        // --- SECTION: DOORS/LOCKS ---
                        VitalsItem { label: "Status"; value: carCan.isLocked ? "LOCKED" : "UNLOCKED"; iconColor: carCan.isLocked ? "#888" : "orange" }
                        VitalsItem { label: "Driver Door"; value: carCan.doorFL ? "OPEN" : "CLOSED"; iconColor: carCan.doorFL ? "red" : "#555" }
                        VitalsItem { label: "Trunk/Boot"; value: carCan.trunk ? "OPEN" : "CLOSED"; iconColor: carCan.trunk ? "red" : "#555" }

                        // --- SECTION: COMFORT ---
                        VitalsItem { label: "A/C State"; value: carCan.acActive ? "COOLING" : "OFF"; iconColor: carCan.acActive ? "#00AAFF" : "#333" }
                        VitalsItem { label: "Windows"; value: carCan.windowPos; unit: "% Open" }
                        VitalsItem { label: "Int. Lights"; value: carCan.interiorLight ? "ON" : "OFF" }
                    }
                }
            }
        }
    }

    // --- FOOTER: Climate & Navigation ---
    footer: Rectangle {
        height: 80
        color: "black"
        RowLayout {
            anchors.fill: parent
            Button { text: "❄️ 21.0°"; flat: true; font.pixelSize: 18; Layout.alignment: Qt.AlignVCenter }
            Item { Layout.fillWidth: true } // Spacer
            Button { text: "MEDIA"; flat: true; font.bold: true }
            Button { text: "MAPS"; flat: true; font.bold: true }
            Item { Layout.fillWidth: true } // Spacer
            Button { text: "SETTINGS"; flat: true }
        }
    }

    // --- REUSABLE COMPONENTS ---

    component VitalsItem : Column {
        property string label: ""
        property string value: ""
        property string unit: ""
        property color iconColor: "white"
        spacing: 4
        Text { text: label; color: "#666"; font.pixelSize: 13; font.capitalization: Font.AllUppercase }
        Row {
            spacing: 4
            Text { text: value; color: iconColor; font.pixelSize: 22; font.bold: true }
            Text { text: unit; color: "#444"; font.pixelSize: 12; anchors.bottom: parent.bottom; anchors.bottomMargin: 4 }
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
            font.pixelSize: 26; font.bold: true
            color: parent.isActive ? parent.activeColor : "#1a1a1a"
            Behavior on color { ColorAnimation { duration: 250 } }
        }
        Text {
            text: parent.label
            font.pixelSize: 9; color: "#444"
            anchors.horizontalCenter: parent.horizontalCenter
            visible: parent.isActive
        }
    }
}
