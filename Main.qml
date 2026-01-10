import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick3D
import QtQuick3D.Helpers
import Polo.CAN 1.0

ApplicationWindow {
    id: window
    width: 1280; height: 720
    visible: true

    // --- 1. THEME LOGIC (This is why your sides didn't change before) ---
    property bool carInverted: false
    color: carInverted ? "#f5f5f7" : "black" // Main background

    CanHandler { id: carCan }
    CockpitWindow {id: cockpit }


    RowLayout {
        anchors.fill: parent
        spacing: 0

        // ==========================================
        // --- LEFT PANE ---
        // ==========================================
        Rectangle {
            Layout.preferredWidth: parent.width * 0.45
            Layout.fillHeight: true
            // BINDING: Changed from #050505 to a dynamic color
            color: window.carInverted ? "#eeeeee" : "#050505"

            Column {
                anchors.top: parent.top; anchors.margins: 20
                anchors.horizontalCenter: parent.horizontalCenter
                z: 10; spacing: 15

                Row {
                    spacing: 25
                    DashboardIcon { text: "◀"; activeColor: "#00FF00"; isActive: carCan.blinkerStatus === 1 }
                    DashboardIcon { text: "(P)"; activeColor: "red"; isActive: carCan.handbrake; label: "BRAKE" }
                    DashboardIcon { text: "☼"; activeColor: "#3366FF"; isActive: carCan.highBeam; label: "BEAM" }
                    DashboardIcon { text: "▶"; activeColor: "#00FF00"; isActive: carCan.blinkerStatus === 2 }
                }
            }

            View3D {
                id: carView
                anchors.fill: parent
                environment: SceneEnvironment {
                    // BINDING: Environment must match the theme
                    clearColor: window.carInverted ? "#eeeeee" : "#050505"
                    backgroundMode: SceneEnvironment.Color
                }

                Node {
                    id: carOrigin
                    eulerRotation: Qt.vector3d(15, yaw, 0)
                    property real yaw: 45

                    Polo {
                        id: poloModel
                        scale: Qt.vector3d(1.2, 1.2, 1.2)
                        bodyColor: window.carInverted ? "#ffffff" : "#0a0a0a"
                    }

                    NumberAnimation on yaw { from: 0; to: 360; duration: 20000; loops: Animation.Infinite; running: !mouseArea.pressed }
                }

                PerspectiveCamera { id: carCamera; z: 550 }
                DirectionalLight { brightness: window.carInverted ? 1.5 : 2.5; eulerRotation.x: -30 }
                OrbitCameraController { anchors.fill: parent; origin: carOrigin; camera: carCamera }
                MouseArea { id: mouseArea; anchors.fill: parent; propagateComposedEvents: true; onPressed: (m)=> m.accepted = false }

            }
        }

        // ==========================================
        // --- RIGHT PANE: Full Vehicle Vitals ---
        // ==========================================
        Rectangle {
            id: rightPane
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: window.carInverted ? "#ffffff" : "#0f0f0f"
            radius: 15
            clip: true

            Flickable {
                anchors.fill: parent
                contentHeight: contentContainer.height // Linked to the container below
                boundsBehavior: Flickable.StopAtBounds
                ScrollBar.vertical: ScrollBar { policy: ScrollBar.AsNeeded }

                Column {
                    id: contentContainer
                    width: parent.width
                    padding: 30
                    spacing: 25

                    Text {
                        text: "VEHICLE STATUS"
                        color: window.carInverted ? "#999" : "#444"
                        font.pixelSize: 12; font.bold: true
                    }

                    // The Grid now has a defined width, allowing Column 2 to appear
                    GridLayout {
                        width: parent.width - 60 // Account for padding
                        columns: 2
                        rowSpacing: 35
                        columnSpacing: 20

                        // --- PERFORMANCE ---
                        VitalsItem { label: "Engine RPM"; value: carCan.rpm; unit: "rpm" }
                        VitalsItem { label: "Coolant"; value: carCan.temp; unit: "°C";
                                     iconColor: carCan.temp > 105 ? "red" : (window.carInverted ? "#005577" : "cyan") }

                        // --- GEAR & SAFETY ---
                        VitalsItem { label: "Current Gear"; value: carCan.gear; unit: "MT" }
                        VitalsItem { label: "Steering"; value: carCan.steeringAngle.toFixed(1); unit: "°" }

                        // --- DOORS/LOCKS ---
                        VitalsItem { label: "Status"; value: carCan.isLocked ? "LOCKED" : "UNLOCKED";
                                     iconColor: carCan.isLocked ? "#888" : "orange" }
                        VitalsItem { label: "Driver Door"; value: carCan.doorFL ? "OPEN" : "CLOSED";
                                     iconColor: carCan.doorFL ? "red" : (window.carInverted ? "black" : "white") }
                        VitalsItem { label: "Trunk/Boot"; value: carCan.trunk ? "OPEN" : "CLOSED";
                                        iconColor: carCan.trunk ? "red" : "#555" }



                        // --- COMFORT ---
                        VitalsItem { label: "A/C State"; value: carCan.acActive ? "COOLING" : "OFF";
                                     iconColor: carCan.acActive ? "#00AAFF" : (window.carInverted ? "#aaa" : "#333") }
                        VitalsItem { label: "Windows"; value: carCan.windowPos; unit: "% Open" }



                        VitalsItem {
                            label: "Wipers"
                            value: ["OFF", "INT", "LOW", "HIGH"][carCan.wiperLevel]
                            iconColor: carCan.wiperLevel > 0 ? (window.carInverted ? "#007aff" : "cyan") : (window.carInverted ? "#444" : "#222")
                        }
                        VitalsItem {
                            label: "Defrost"
                            value: carCan.windshieldHeater ? "ON" : "OFF"
                            iconColor: carCan.windshieldHeater ? "orange" : (window.carInverted ? "#aaa" : "#222")

                        VitalsItem { label: "Int. Lights"; value: carCan.interiorLight ? "ON" : "OFF" }

                        }
                    }
                }
            }
        }


    }

    // --- FOOTER: Climate & Navigation ---
    footer: Rectangle {
        id: bottomBar
        height: 80
        // BINDING: Swaps between Tesla Black and Tesla Light Gray
        color: window.carInverted ? "#f0f0f0" : "black"

        // Optional: Subtle border for light mode
        border.color: window.carInverted ? "#dddddd" : "transparent"
        border.width: 1

        // Smooth fade effect when switching
        Behavior on color { ColorAnimation { duration: 300 } }

        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 40
            anchors.rightMargin: 40

            // Temperature Control
            Button {
                id: tempBtn
                flat: true
                contentItem: Text {
                    text: "❄️ 21.0°"
                    font.pixelSize: 18
                    font.bold: true
                    // BINDING: Text turns black when bar is light
                    color: window.carInverted ? "black" : "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            Item { Layout.fillWidth: true } // Spacer

            // Navigation & Media Group
            Row {
                spacing: 30
                Button {
                    text: "MEDIA"
                    flat: true
                    contentItem: Text {
                        text: parent.text; font.bold: true;
                        color: window.carInverted ? "black" : "white"
                    }
                }
                Button {
                    text: "MAPS"
                    flat: true
                    contentItem: Text {
                        text: parent.text; font.bold: true;
                        color: window.carInverted ? "black" : "white"
                    }
                }
            }

            Item { Layout.fillWidth: true } // Spacer

            // Settings
            Button {
                text: "SETTINGS"
                flat: true
                contentItem: Text {
                    text: parent.text;
                    color: window.carInverted ? "black" : "white"
                }
            }
        }
    }

    // --- BUTTON OVERLAY (Bottom Right) ---
    Rectangle {
        anchors.right: parent.right; anchors.bottom: parent.bottom; anchors.margins: 25
        width: 160; height: 50; radius: 25
        color: window.carInverted ? "#f0f0f0" : "#1a1a1a"
        border.color: "#333"; z: 100

        Row {
            anchors.centerIn: parent; spacing: 10
            Text { text: window.carInverted ? "LIGHT" : "DARK"; color: window.carInverted ? "black" : "white"; font.bold: true }
            Rectangle { width: 34; height: 18; radius: 9; color: window.carInverted ? "#007aff" : "#444"
                Rectangle { width: 14; height: 14; radius: 7; color: "white"
                    x: window.carInverted ? 18 : 2; anchors.verticalCenter: parent.verticalCenter
                    Behavior on x { NumberAnimation { duration: 200 } }
                }
            }
        }
        MouseArea { anchors.fill: parent; onClicked: window.carInverted = !window.carInverted }
    }


}

