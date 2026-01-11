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
                    property real yaw: 0

                    Polo {
                        id: poloModel
                        scale: Qt.vector3d(1.2, 1.2, 1.2)
                        bodyColor: window.carInverted ? "white" : "#0000FF"
                    }

                    // Place this INSIDE your carOrigin Node so it stays linked to the car
                    Model {
                        id: roadPlane
                        source: "#Rectangle"

                        // Position: x=0 (centered), y=-1 (under tires), z=0
                        position: Qt.vector3d(0, -1, 0)

                        // Scale: Wide (20), Very Long (100)
                        scale: Qt.vector3d(20, 100, 1)

                        eulerRotation.x: -90 // Lay flat on the ground

                        materials: [
                            PrincipledMaterial {
                                id: roadMaterial
                                // THE COLOR TOGGLE:
                                // Dark Mode = Dark Asphalt (#111111)
                                // Light Mode = Light Concrete (#cccccc)
                                baseColor: window.carInverted ? "#cccccc" : "#111111"

                                roughness: 0.8
                                metalness: 0.0
                                lighting: PrincipledMaterial.Fragments // Ensures it reacts to your DirectionalLight
                            }
                        ]
                    }

                    //NumberAnimation on yaw { from: 0; to: 360; duration: 20000; loops: Animation.Infinite; running: !mouseArea.pressed }
                }




                PerspectiveCamera {
                    id: carCamera;
                    position: Qt.vector3d(0, 150, 600) // Default starting position

                    // --- MANUAL CONSTRAINTS ---
                    onPositionChanged: {
                        // 1. ZOOM LIMIT (Distance)
                        // We calculate the length of the vector to the center
                        let distance = Math.sqrt(x*x + y*y + z*z);
                        if (distance < 750) z = 750; // Too close
                        if (distance > 800) z = 800; // Too far

                        // 2. HEIGHT LIMIT (Angle/Pitch)
                        // Prevent camera from going below ground (y=0)
                        if (y < 20) y = 20;
                    }
                }

                DirectionalLight {
                    id: cameraLight
                    // Binds the light direction to the camera so the car is always well-lit
                    eulerRotation: carCamera.eulerRotation

                    // Adjusted brightness:
                    // Dark mode (carInverted: false) needs more light to see the deep blue.
                    // Light mode (carInverted: true) needs less to avoid "blinding" white.
                    brightness: window.carInverted ? 1.0 : 2.0

                    castsShadow: true
                    shadowFactor: 15 // Softens the shadow edge
                }

                OrbitCameraController { anchors.fill: parent; origin: carOrigin; camera: carCamera }


                MouseArea { id: mouseArea; anchors.fill: parent; propagateComposedEvents: true; onPressed: (m)=> m.accepted = false }

            }
        }

        // ==========================================
        // --- RIGHT PANE: Full Vehicle Vitals ---
        // ==========================================

        // --- welcome ---
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
            // submenu like tesla
            // --- 1. THE MAIN MENU CONTAINER ---
            Item {
                id: mainMenuContainer
                anchors.fill: parent
                visible: false
                z: 10 // Stays on top of the 3D Car

                Row {
                    anchors.fill: parent

                    // --- 2. THE LEFT SIDEBAR (The Submenu buttons) ---
                    Rectangle {
                        id: menuSidebar
                        width: parent.width * 0.25 // Occupies 25% of the width
                        height: parent.height
                        color: window.carInverted ? "#F5F5F7" : "#111111"

                        Column {
                            anchors.fill: parent
                            anchors.margins: 20
                            spacing: 10

                            Text {
                                text: "PoloOS"
                                color: window.carInverted ? "#666666" : "#888888"
                                font.pixelSize: 12; font.weight: Font.Bold
                                bottomPadding: 10
                            }

                            Repeater {
                                model: [
                                    { name: "Vehicle", file: "VehiclePage.qml" },
                                    { name: "Engine", file: "EnginePage.qml" },
                                    { name: "Chassis", file: "ChassisPage.qml" },
                                    { name: "Energy", file: "EnergyPage.qml" },
                                   { name: "Climate", file: "ClimatePage.qml" },
                                   { name: "Body", file: "BodyPage.qml" },
                                   { name: "Diagnostics", file: "DiagnosticsPage.qml" },
                                   { name: "Settings", file: "SettingsPage.qml" }
                                ]

                                Rectangle {
                                    width: parent.width; height: 50; radius: 10
                                    color: pageStack.currentItemName === modelData.name
                                           ? (window.carInverted ? "#E0E0E0" : "#222222") : "transparent"

                                    Text {
                                        anchors.centerIn: parent
                                        text: modelData.name.toUpperCase()
                                        color: window.carInverted ? "black" : "white"
                                        font.pixelSize: 14; font.weight: Font.DemiBold
                                    }

                                    MouseArea {
                                        anchors.fill: parent
                                        onClicked: {
                                            pageStack.replace(modelData.file)
                                            pageStack.currentItemName = modelData.name
                                        }
                                    }
                                }
                            }
                        }

                        // Visual separator line (Tesla style)
                        Rectangle {
                            anchors.right: parent.right
                            width: 1
                            height: parent.height
                            color: window.carInverted ? "#DDDDDD" : "#333333"
                        }
                    }

                    // --- 3. THE CONTENT AREA (The Page itself) ---
                    StackView {
                        id: pageStack
                        width: parent.width * 0.75 // Occupies the remaining 75%
                        height: parent.height
                        clip: true

                        property string currentItemName: "Vehicle"
                        initialItem: "VehiclePage.qml"

                        // --- REMOVE ALL ANIMATIONS ---
                            replaceEnter: Transition { }
                            replaceExit: Transition { }
                            pushEnter: Transition { }
                            pushExit: Transition { }
                            popEnter: Transition { }
                            popExit: Transition { }

                        // Background for the page area
                        background: Rectangle {
                            color: window.carInverted ? "#F5F5F7" : "#111111"
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

            // --- GROUP 1: Time & Climate ---
            Row {
                spacing: 15
                Layout.alignment: Qt.AlignVCenter

                Text {
                    id: timeDisplay
                    text: Qt.formatDateTime(new Date(), "hh:mm")
                    font.pixelSize: 22 // Slightly smaller to match UI balance
                    font.weight: Font.DemiBold
                    color: window.carInverted ? "#000000" : "#FFFFFF"

                    Timer {
                        interval: 1000
                        running: true
                        repeat: true
                        onTriggered: timeDisplay.text = Qt.formatDateTime(new Date(), "hh:mm")
                    }
                }

                Button {
                    id: tempBtn
                    flat: true
                    contentItem: Text {
                        // Displays the real-time temperature from the API
                        text: "🌡️ " + weatherService.tempValue
                        font.pixelSize: 22
                        font.bold: true
                        color: window.carInverted ? "black" : "white"
                    }
                }
            }

            Item { Layout.fillWidth: true } // SPACER (Pushes next group to center)

            // --- GROUP 2: Navigation & Media ---
            Row {
                spacing: 30
                Layout.alignment: Qt.AlignVCenter

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
                    onClicked: {
                            // Hide the settings menu if it's open
                            mainMenuContainer.visible = false
                            // Show the Map overlay
                            mapOverlay.visible = !mapOverlay.visible
                        }
                    contentItem: Text {
                        text: parent.text; font.bold: true;
                        color: window.carInverted ? "black" : "white"
                    }
                }
            }

            Item { Layout.fillWidth: true } // SPACER (Pushes next group to right)

            // --- GROUP 3: Settings ---
            Button {
                text: "MENU"
                flat: true
                Layout.alignment: Qt.AlignVCenter

                onClicked: {
                    // Toggle the entire Menu System (Sidebar + Pages)
                    mainMenuContainer.visible = !mainMenuContainer.visible
                }

                contentItem: Text {
                    text: parent.text
                    font.bold: true
                    color: window.carInverted ? "black" : "white"
                }
            }
        }
    }



    //--- item for weather ---

    Item {
        id: weatherService

        // Example: Paris (Replace with your city's coordinates)
        property real lat: 48.8566
        property real lon: 2.3522
        property string tempValue: "--"

        function fetchWeather() {
            var xhr = new XMLHttpRequest();
            // Open-Meteo URL (No Key Needed!)
            var url = "https://api.open-meteo.com/v1/forecast?latitude=" + lat + "&longitude=" + lon + "&current_weather=true";

            xhr.onreadystatechange = function() {
                if (xhr.readyState === XMLHttpRequest.DONE) {
                    if (xhr.status === 200) {
                        var response = JSON.parse(xhr.responseText);
                        // Open-Meteo returns 'current_weather' object
                        weatherService.tempValue = Math.round(response.current_weather.temperature) + "°";
                    } else {
                        console.log("Weather Error: " + xhr.status);
                    }
                }
            }
            xhr.open("GET", url);
            xhr.send();
        }

        // Refresh every 15 minutes
        Timer {
            interval: 900000
            running: true
            repeat: true
            triggeredOnStart: true
            onTriggered: weatherService.fetchWeather()
        }
    }

    //item for view MAP
    Loader {
        id: mapOverlay
        anchors.fill: parent
        visible: false
        source: "MapPage.qml"

        // Ensure the top bar and footer are still visible over the map
        z: 5
    }
}

