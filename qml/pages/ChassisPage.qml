import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt5Compat.GraphicalEffects

Item {
    id: chassisPage

    // Propriétés de style dynamiques (Mode Jour/Nuit)
    readonly property color mainTextColor: window.carInverted ? "#1a1a1a" : "#ffffff"
    readonly property color subTextColor: "#888888"
    readonly property color skeletonColor: window.carInverted ? "#D1D1D6" : "#333333"

    ScrollView {
        anchors.fill: parent
        contentWidth: parent.width
        clip: true

        ColumnLayout {
            width: parent.width - 80
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 40
            spacing: 15

            Text {
                text: "CHASSIS & DYNAMICS";
                color: subTextColor;
                font.bold: true;
                font.pixelSize: 16;
                font.letterSpacing: 2
                Layout.alignment: Qt.AlignHCenter
            }

            // ==========================================
            // --- SECTION 2: CONTRÔLES (Brakes/Steering) ---
            // ==========================================
            RowLayout {
                Layout.fillWidth: true; spacing: 20
                Layout.alignment: Qt.AlignHCenter
                VitalsItem {
                    label: "Steering"; value: carCan.steeringAngle.toFixed(1); unit: "°"
                    iconColor: Math.abs(carCan.steeringAngle) > 20 ? "#00f2ff" : subTextColor
                }
                VitalsItem {
                    label: "Brake Pedal"; value: carCan.brakePressed ? "PRESSED" : "RELEASED"
                    iconColor: carCan.brakePressed ? "#FF3B30" : "#333"
                }
                VitalsItem {
                    label: "Handbrake"; value: carCan.handbrake ? "ENGAGED" : "RELEASED"
                    iconColor: carCan.handbrake ? "#FF3B30" : "#333"
                }
            }

            // ==========================================
            // --- SECTION 1: VISUALISATION SQUELETTE ---
            // =========================================

            Item {
                Layout.fillWidth: true
                Layout.preferredHeight: 325
                Layout.alignment: Qt.AlignHCenter

                // Structure centrale du châssis (Squelette)
                Rectangle {
                    id: chassisFrame
                    width: 140; height: 300
                    anchors.centerIn: parent
                    color: "transparent"
                    border.color: skeletonColor
                    border.width: 2
                    radius: 30

                    // Axe longitudinal
                    Rectangle {
                        width: 2; height: parent.height - 60
                        anchors.centerIn: parent
                        color: skeletonColor; opacity: 0.5
                    }

                    // Axe avant (directionnel)
                    Rectangle {
                        width: parent.width + 40; height: 2
                        anchors.horizontalCenter: parent.horizontalCenter
                        y: 60; color: skeletonColor; opacity: 0.8
                    }

                    // Axe arrière
                    Rectangle {
                        width: parent.width + 40; height: 2
                        anchors.horizontalCenter: parent.horizontalCenter
                        y: parent.height - 60; color: skeletonColor; opacity: 0.8
                    }

                    // --- ROUE AVANT GAUCHE (FL) ---
                    WheelNode {
                        anchors.left: parent.left; anchors.leftMargin: -25; y: 20
                        wheelName: "FL"; speed: carCan.wheelFL
                        steering: carCan.steeringAngle; isFront: true
                    }

                    // --- ROUE AVANT DROITE (FR) ---
                    WheelNode {
                        anchors.right: parent.right; anchors.rightMargin: -25; y: 20
                        wheelName: "FR"; speed: carCan.wheelFR
                        steering: carCan.steeringAngle; isFront: true
                    }

                    // --- ROUE ARRIÈRE GAUCHE (RL) ---
                    WheelNode {
                        anchors.left: parent.left; anchors.leftMargin: -25; y: parent.height - 100
                        wheelName: "RL"; speed: carCan.wheelRL
                    }

                    // --- ROUE ARRIÈRE DROITE (RR) ---
                    WheelNode {
                        anchors.right: parent.right; anchors.rightMargin: -25; y: parent.height - 100
                        wheelName: "RR"; speed: carCan.wheelRR
                    }
                }
            }






            // ==========================================
            // --- SECTION 3: SYSTÈMES DE SÉCURITÉ ---
            // ==========================================
            Text {
                text: "SAFETY SYSTEMS"
                color: subTextColor
                font.bold: true
                font.pixelSize: 12
                font.letterSpacing: 1
                Layout.alignment: Qt.AlignHCenter
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 40
                Layout.alignment: Qt.AlignHCenter

                // 1. ICÔNE ABS
                SafetyIcon {
                    iconSource: "qrc:/icons/iconsDashboard/mdi--car-brake-abs-3.svg" // Remplace par ton chemin
                    label: "ABS"
                    isActive: carCan.absActive
                    activeColor: "#FFCC00" // Jaune Ambre
                }

                // 2. ICÔNE ESP/ESC
                SafetyIcon {
                    iconSource: "qrc:/icons/iconsDashboard/mdi--car-esp-2.svg"
                    label: "ESP"
                    isActive: carCan.espActive
                    activeColor: "#FFCC00"
                }

                // 3. ICÔNE TRACTION (TCS)
                SafetyIcon {
                    iconSource: "qrc:/icons/iconsDashboard/mdi--car-traction-control-2.svg"
                    label: "TRAC"
                    isActive: carCan.tractionActive
                    activeColor: "#FF9500" // Orange
                }
            }


            // --- MINI G-FORCE METER ---
            Item {
                Layout.fillWidth: true
                Layout.preferredHeight: 50
                Layout.topMargin: 20

                Text {
                    text: "G-Force simple"
                    color: subTextColor
                    font.bold: true
                    font.pixelSize: 12
                    font.letterSpacing: 1
                    Layout.alignment: Qt.AlignHCenter
                }

                Rectangle {
                    id: gBar
                    width: 200; height: 4
                    anchors.centerIn: parent
                    color: skeletonColor; opacity: 0.3
                    radius: 2

                    // La bille de force G
                    Rectangle {
                        id: gBall
                        width: 12; height: 12; radius: 6
                        color: Math.abs(xOffset) > 60 ? "#FF3B30" : "#00f2ff"
                        anchors.verticalCenter: parent.verticalCenter

                        // Calcul simplifié : angle de direction * vitesse / facteur
                        property real xOffset: (carCan.steeringAngle * carCan.speed) / 50

                        x: (parent.width / 2 - 6) + xOffset

                        Behavior on x { SpringAnimation { spring: 2; damping: 0.2 } }
                    }
                }

                Text {
                    anchors.top: gBar.bottom; anchors.topMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "LATERAL G-FORCE"
                    color: subTextColor; font.pixelSize: 9; font.bold: true
                }
            }
        }
    }

    // --- COMPOSANT INTERNE : ROUE ---
    component WheelNode : Item {
        id: wheelRoot
        property string wheelName: ""
        property real speed: 0
        property real steering: 0
        property bool isFront: false

        width: 50; height: 85

        // Logique de couleur selon la vitesse
        readonly property color wheelDynamicColor: {
            if (speed > 130) return "#FF3B30" // Rouge (Vitesse excessive)
            if (speed > 80) return "#FFCC00"  // Orange (Vitesse soutenue)
            if (speed > 5) return "#4CD964"   // Vert (En mouvement)
            return window.carInverted ? "#8E8E93" : "#444444" // Gris (Arrêt)
        }

        // Dessin du pneu
        Rectangle {
            anchors.fill: parent
            color: wheelDynamicColor
            radius: 8
            rotation: isFront ? steering : 0 // Applique l'angle si roue motrice
            antialiasing: true
            border.color: "black"; border.width: 1

            // Texture du pneu (Rainures)
            Column {
                anchors.centerIn: parent; spacing: 6
                Repeater { model: 5; Rectangle { width: 35; height: 1; color: "black"; opacity: 0.3 } }
            }

            Behavior on rotation { NumberAnimation { duration: 150; easing.type: Easing.OutQuad } }
            Behavior on color { ColorAnimation { duration: 400 } }
        }

        // Affichage Vitesse + Label à côté de la roue
        Column {
            anchors.left: wheelName.includes("R") ? parent.right : undefined
            anchors.right: wheelName.includes("L") ? parent.left : undefined
            anchors.leftMargin: 12; anchors.rightMargin: 12
            anchors.verticalCenter: parent.verticalCenter

            Text {
                text: speed.toFixed(0)
                font.pixelSize: 18; font.bold: true
                color: mainTextColor
                horizontalAlignment: wheelName.includes("L") ? Text.AlignRight : Text.AlignLeft
            }
            Text {
                text: "km/h"
                font.pixelSize: 10; color: subTextColor
                horizontalAlignment: wheelName.includes("L") ? Text.AlignRight : Text.AlignLeft
            }
        }
    }



    // --- COMPOSANT INTERNE : SafetyIcon ---
    component SafetyIcon : Column {
        property string iconSource: ""
        property string label: ""
        property bool isActive: false
        property bool isCritical: false
        property color activeColor: "#FFCC00"

        spacing: 8
        width: 60

        Item {
            width: 45; height: 45
            anchors.horizontalCenter: parent.horizontalCenter

            Image {
                id: svgImg
                source: iconSource
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                visible: false // Caché car on utilise l'effet de couleur
            }

            // Effet de couleur dynamique pour le SVG
            ColorOverlay {
                anchors.fill: svgImg
                source: svgImg

                // LOGIQUE DE COULEUR :
                // Si Actif : Couleur vive (Jaune/Orange)
                // Si Inactif : Gris sombre (Nuit) ou Gris clair (Jour)
                color: isActive ? activeColor : (window.carInverted ? "#D1D1D6" : "#333333")

                // Animation pour un passage fluide à l'état actif
                Behavior on color { ColorAnimation { duration: 300 } }

                // Animation de clignotement rapide si critique
                SequentialAnimation on opacity {
                    running: isCritical
                    loops: Animation.Infinite
                    NumberAnimation { from: 1.0; to: 0.2; duration: 150 }
                    NumberAnimation { from: 0.2; to: 1.0; duration: 150 }
                }
                // Reset de l'opacité si pas critique
                opacity: isCritical ? 1.0 : (isActive ? 1.0 : 0.5)
            }

            // Petit effet de lueur (Glow) quand le système intervient
            Rectangle {
                anchors.centerIn: parent
                width: 50; height: 50
                radius: 25
                color: activeColor
                opacity: isActive ? 0.15 : 0
                visible: isActive

                SequentialAnimation on opacity {
                    running: isActive
                    loops: Animation.Infinite
                    NumberAnimation { from: 0.05; to: 0.2; duration: 600 }
                    NumberAnimation { from: 0.2; to: 0.05; duration: 600 }
                }
            }
        }

        Text {
            text: label
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 10
            font.bold: true
            // Le texte s'allume aussi quand le système est actif
            color: isCritical ? "#FF3B30" : (isActive ? activeColor : subTextColor)
            Behavior on color { ColorAnimation { duration: 300 } }

        }
    }



}
