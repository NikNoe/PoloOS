import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick3D
import QtQuick3D.Helpers
import QtQuick.Shapes
import Qt5Compat.GraphicalEffects
import "."


ApplicationWindow {
    id: window
    width: 1280; height: 720
    visible: true

    // --- 1. THEME LOGIC (This is why your sides didn't change before) ---
    property bool carInverted: false
    color: carInverted ? "#f5f5f7" : "black" // Main background

    CockpitWindow {id: cockpit }

    Connections {
        target: carCan
        function anyDoorOpenChanged() {
            console.log("SIMULATOR MESSAGE: blinker is now " + carCan.DoorOpen)
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // ==========================================
        // --- LEFT PANE ---
        // ==========================================
        // ==========================================
        // --- LEFT PANE ---
        // ==========================================
        Rectangle {
            id: leftPane
            Layout.preferredWidth: parent.width * 0.45
            Layout.fillHeight: true
            color: window.carInverted ? "#eeeeee" : "#050505"

            // --- INDICATEURS (UI LAYER) ---
            Column {
                    anchors.top: parent.top; anchors.topMargin: 30
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 30 // Espace vertical entre les lignes
                    z: 10

                    // --- 1ère LIGNE : CONDUITE ---
                    Row {
                        spacing: 25
                        DashboardIcon {
                            iconSource: "qrc:/icons/iconsDashboard/mynaui--fat-arrow-left-solid.svg"
                            isActive: carCan.blinkerStatus === 1; isBlinking: true

                        }
                        DashboardIcon {
                            iconSource: "qrc:/icons/iconsDashboard/mdi--low-beam-2.svg"
                            isActive: carCan.lowBeam
                        }
                        DashboardIcon {
                            iconSource: "qrc:/icons/iconsDashboard/mdi--high-beam-2.svg"
                            isActive: carCan.highBeam
                        }
                        DashboardIcon {
                            iconSource: "qrc:/icons/iconsDashboard/mynaui--fat-arrow-right-solid.svg"
                            isActive: carCan.blinkerStatus === 2; isBlinking: true


                        }
                    }

                    // --- 2ème LIGNE : SÉCURITÉ ---
                    Row {
                        spacing: 25
                        DashboardIcon {
                            iconSource: "qrc:/icons/iconsDashboard/ph--seatbelt-bold.svg"
                            isActive: carCan.rpm > 900 && !carCan.beltDriver; isBlinking: true
                        }
                        DashboardIcon {
                            iconSource: "qrc:/icons/iconsDashboard/mdi--car-brake-parking.svg"
                            isActive: carCan.handbrake
                        }
                        DashboardIcon {
                            iconSource: "qrc:/icons/iconsDashboard/mingcute--car-door-line.svg"
                            isActive: carCan.anyDoorOpen
                        }
                    }

                    // --- 3ème LIGNE : TECHNIQUE (ABS, Huile, Batterie) ---
                    Row {
                        spacing: 25
                        DashboardIcon {
                            iconSource: "qrc:/icons/iconsDashboard/mdi--car-brake-abs-2.svg"
                            isActive: carCan.absActive
                        }
                        /*
                        DashboardIcon {
                            iconSource: "qrc:/icons/iconsDashboard/fa-solid--oil-can-2.svg"
                            isActive: carCan.oilWarning
                        }
                        */
                        DashboardIcon {
                            iconSource: "qrc:/icons/iconsDashboard/fa-solid--car-battery-2.svg"
                            isActive: carCan.batteryWarning
                        }
                    }
                }

            // --- VUE 3D DE LA VOITURE ---
            View3D {
                id: carView
                anchors.fill: parent
                z: 1 // Derrière les icônes

                environment: SceneEnvironment {
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

                    Model {
                        id: roadPlane
                        source: "#Rectangle"
                        position: Qt.vector3d(0, -1, 0)
                        scale: Qt.vector3d(20, 100, 1)
                        eulerRotation.x: -90
                        materials: [
                            PrincipledMaterial {
                                baseColor: window.carInverted ? "#cccccc" : "#111111"
                                roughness: 0.8
                                lighting: PrincipledMaterial.FragmentLighting
                            }
                        ]
                    }
                }

                PerspectiveCamera {
                    id: carCamera
                    position: Qt.vector3d(0, 150, 600)
                    onPositionChanged: {
                        let distance = Math.sqrt(x*x + y*y + z*z);
                        if (distance < 750) z = 750;
                        if (distance > 800) z = 800;
                        if (y < 20) y = 20;
                    }
                }

                DirectionalLight {
                    id: cameraLight
                    eulerRotation: carCamera.eulerRotation
                    brightness: window.carInverted ? 1.0 : 2.0
                    castsShadow: true
                    shadowFactor: 15
                }

                OrbitCameraController {
                    anchors.fill: parent
                    origin: carOrigin
                    camera: carCamera
                }

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    propagateComposedEvents: true
                    onPressed: (m)=> m.accepted = false
                }
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
                    // Le Flickable regarde la hauteur du rectangle bleu/conteneur ci-dessous
                    contentHeight: contentContainer.height
                    boundsBehavior: Flickable.StopAtBounds
                    ScrollBar.vertical: ScrollBar { policy: ScrollBar.AsNeeded }

                    // --- C'EST ICI QU'IL MANQUAIT L'ID ---
                    Column {
                        id: contentContainer
                        width: parent.width
                        spacing: 30
                        anchors.top: parent.top
                        anchors.margins: 20

                        Text {
                            text: "POLO TDI // TECNODJUM"
                            color: window.carInverted ? "#222" : "#00f2ff" // Bleu Néon
                            font.pixelSize: 22
                            font.letterSpacing: 2
                            font.bold: true
                            anchors.horizontalCenter: parent.horizontalCenter
                        }

                        Row {
                            spacing: 50
                            anchors.horizontalCenter: parent.horizontalCenter

                            // --- COMPTEUR VITESSE ---
                            ModernGauge {
                                id: speedGauge
                                value: carCan.speed
                                maxValue: 240
                                unit: "km/h"
                                glowColor: "#0a84ff"
                                numbers: [0, 40, 80, 120, 160, 200, 240]
                            }

                            // --- COMPTEUR RPM ---
                            ModernGauge {
                                id: rpmGauge
                                value: carCan.rpm
                                maxValue: 8000
                                unit: "x1000 RPM"
                                glowColor: "#ff007b" // Rose/Magenta Néon
                                numbers: [0, 2, 4, 6, 8]
                                isRpm: true
                            }
                        }

                        // --- BARRE DE STATUT & INFOS BASES ---

                        Item {
                            id: statusArea
                            width: parent.width
                            height: 150
                            anchors.horizontalCenter: parent.horizontalCenter

                            ColumnLayout {
                                anchors.fill: parent
                                spacing: 15

                                // --- PARTIE SUPÉRIEURE : RANGE ET GEAR ---
                                RowLayout {
                                    Layout.alignment: Qt.AlignHCenter
                                    spacing: 30

                                    // Bloc Autonomie
                                    Rectangle {
                                        Layout.preferredWidth: 200
                                        Layout.preferredHeight: 80
                                        radius: 12

                                        // Couleur de fond : Priorité aux alertes, sinon bascule Jour/Nuit
                                        color: {
                                            if (carCan.rangePossible < 50) return "#C0392B"; // Rouge Alerte
                                            if (carCan.rangePossible < 100) return "#D35400"; // Orange Alerte
                                            return window.carInverted ? "#E0E0E0" : "#1a1a1a"; // Jour: Gris clair / Nuit: Noir
                                        }

                                        border.color: window.carInverted ? "#BDBDBD" : "#333"
                                        border.width: 1

                                        Behavior on color { ColorAnimation { duration: 500 } }

                                        Column {
                                            anchors.centerIn: parent
                                            spacing: 2
                                            Text {
                                                text: "ESTIMATED RANGE"
                                                color: window.carInverted ? "#666666" : "#888888"
                                                font.pixelSize: 10
                                                font.bold: true
                                                anchors.horizontalCenter: parent.horizontalCenter
                                            }
                                            Text {
                                                text: carCan.rangePossible.toFixed(0) + " km"
                                                color: (carCan.rangePossible < 100) ? "white" : (window.carInverted ? "black" : "white")
                                                font.pixelSize: 28
                                                font.bold: true
                                                anchors.horizontalCenter: parent.horizontalCenter
                                            }
                                        }
                                    }

                                    // Bloc Rapport Engagé
                                    Rectangle {
                                        Layout.preferredWidth: 65
                                        Layout.preferredHeight: 65
                                        radius: 10
                                        // En mode jour, on peut passer sur un bleu plus profond pour la lisibilité
                                        color: window.carInverted ? "#0097A7" : "#00f2ff"

                                        Text {
                                            anchors.centerIn: parent
                                            text: carCan.gear === 0 ? "R" : (carCan.gear === 11 ? "N" : carCan.gear)
                                            color: "black"
                                            font.pixelSize: 36
                                            font.bold: true
                                        }
                                    }

                                    // Bloc Température
                                    Rectangle {
                                        Layout.preferredWidth: 200
                                        Layout.preferredHeight: 80
                                        radius: 12
                                        color: window.carInverted ? "#E0E0E0" : "#1a1a1a"
                                        border.color: window.carInverted ? "#BDBDBD" : "#333"

                                        Column {
                                            anchors.centerIn: parent
                                            Text {
                                                text: "OUTSIDE TEMP"
                                                color: window.carInverted ? "#666666" : "#888888"
                                                font.pixelSize: 10; font.bold: true
                                                anchors.horizontalCenter: parent.horizontalCenter
                                            }
                                            Text {
                                                text: weatherService.tempValue + "°C"
                                                font.pixelSize: 28
                                                font.bold: true
                                                anchors.horizontalCenter: parent.horizontalCenter
                                                color: window.carInverted ? "black" : "white"
                                            }
                                        }
                                    }
                                }

                                // --- PARTIE INFÉRIEURE : VERROUILLAGE ---
                                RowLayout {
                                    Layout.alignment: Qt.AlignHCenter
                                    spacing: 20

                                    Item {
                                        id: iconContainer
                                        Layout.preferredWidth: 40
                                        Layout.preferredHeight: 40

                                        Image {
                                            id: lockIcon
                                            anchors.fill: parent
                                            source: carCan.isLocked ? "qrc:/icons/iconsDashboard/vaadin--lock.svg" : "qrc:/icons/iconsDashboard/vaadin--unlock.svg"
                                            fillMode: Image.PreserveAspectFit
                                            // On cache l'original pour ne voir que la version colorée
                                            visible: false
                                        }

                                        // L'effet de couleur qui remplace MultiEffect pour plus de compatibilité
                                        ColorOverlay {
                                            anchors.fill: lockIcon
                                            source: lockIcon
                                            color: {
                                                if (!carCan.isLocked) return "#ff4444";
                                                return window.carInverted ? "#007A7C" : "#00f2ff";
                                            }

                                            // Animation de pulsation si déverrouillé
                                            SequentialAnimation on opacity {
                                                running: !carCan.isLocked
                                                loops: Animation.Infinite
                                                NumberAnimation { from: 1.0; to: 0.4; duration: 800; easing.type: Easing.InOutQuad }
                                                NumberAnimation { from: 0.4; to: 1.0; duration: 800; easing.type: Easing.InOutQuad }
                                            }

                                            // État stable si verrouillé
                                            opacity: carCan.isLocked ? 0.8 : 1.0

                                            Behavior on color { ColorAnimation { duration: 400 } }
                                        }

                                        scale: carCan.isLocked ? 1.0 : 1.2
                                        Behavior on scale { NumberAnimation { duration: 250; easing.type: Easing.OutBack } }
                                    }

                                    Text {
                                        text: carCan.isLocked ? "VEHICLE SECURED" : "VEHICLE UNLOCKED"
                                        color: carCan.isLocked ? (window.carInverted ? "#007A7C" : "#00f2ff") : "#ff4444"
                                        font.pixelSize: 12
                                        font.bold: true
                                        font.letterSpacing: 1
                                        Behavior on color { ColorAnimation { duration: 400 } }
                                    }
                                }
                            }
                        }
                        }
                    }

                    component ModernGauge : Item {
                        property real value: 0
                        property real maxValue: 100
                        property string unit: ""
                        property color glowColor: "cyan"
                        property var numbers: []
                        property bool isRpm: false

                        width: 280; height: 280

                        // Anneau de fond sombre
                        Shape {
                            anchors.fill: parent
                            antialiasing: true
                            ShapePath {
                                fillColor: "transparent"
                                strokeColor: "#1a1a1a"
                                strokeWidth: 12
                                capStyle: ShapePath.RoundCap
                                PathAngleArc {
                                    centerX: 140; centerY: 140
                                    radiusX: 110; radiusY: 110
                                    startAngle: 140
                                    sweepAngle: 260
                                }
                            }
                        }

                        // Anneau de progression néon
                        Shape {
                            anchors.fill: parent
                            antialiasing: true
                            ShapePath {
                                fillColor: "transparent"
                                strokeColor: glowColor
                                strokeWidth: 12
                                capStyle: ShapePath.RoundCap
                                PathAngleArc {
                                    centerX: 140; centerY: 140
                                    radiusX: 110; radiusY: 110
                                    startAngle: 140
                                    sweepAngle: (value / maxValue) * 260
                                }
                            }
                        }

                        // Chiffres sur le bord
                        Repeater {
                            model: numbers
                            delegate: Text {
                                readonly property real angle: (modelData / maxValue) * 260 + 140
                                readonly property real rad: angle * Math.PI / 180
                                x: 140 + 135 * Math.cos(rad) - width/2
                                y: 140 + 135 * Math.sin(rad) - height/2
                                text: modelData
                                color: (value >= modelData) ? glowColor : "#444"
                                font.pixelSize: 14
                                font.bold: true
                                Behavior on color { ColorAnimation { duration: 200 } }
                            }
                        }

                        // Affichage digital central
                        Column {
                            anchors.centerIn: parent
                            spacing: -5
                            Text {
                                text: isRpm ? (value/1000).toFixed(1) : Math.floor(value)
                                font.pixelSize: 56
                                font.bold: true
                                color: "white"
                                // Effet d'ombre portée pour le "glow"
                                style: Text.Outline; styleColor: glowColor
                            }
                            Text {
                                text: unit
                                font.pixelSize: 14
                                color: "#888"
                                anchors.horizontalCenter: parent.horizontalCenter
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
                                    { name: "Engine", file: "EnginePage.qml" },
                                    { name: "Chassis", file: "ChassisPage.qml" },
                                    { name: "Energy", file: "EnergyPage.qml" },
                                   { name: "Body", file: "BodyPage.qml" },
                                   { name: "Diagnostics", file: "DiagnosticsPage.qml" },
                                   { name: "Settings", file: "SettingsPage.qml" },
                                    { name: "About", file: "AboutPage.qml" }
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

                        property string currentItemName: "Engine"
                        initialItem: "EnginePage.qml"

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


            // --- GROUP 1: Settings ---
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
                    font.pixelSize: 22
                    color: window.carInverted ? "black" : "white"
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
                        font.pixelSize: 22
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
                        font.pixelSize: 22
                        color: window.carInverted ? "black" : "white"
                    }
                }
            }

            Item { Layout.fillWidth: true } // SPACER (Pushes next group to right)

            // --- GROUP 3: Time & Climate ---
            Row {
                spacing: 15
                Layout.alignment: Qt.AlignVCenter

                Text {
                    id: timeDisplay
                    text: Qt.formatDateTime(new Date(), "hh:mm")
                    font.pixelSize: 30 // Slightly smaller to match UI balance
                    font.weight: Font.DemiBold
                    color: window.carInverted ? "#000000" : "#FFFFFF"

                    Timer {
                        interval: 1000
                        running: true
                        repeat: true
                        onTriggered: timeDisplay.text = Qt.formatDateTime(new Date(), "hh:mm")
                    }
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

