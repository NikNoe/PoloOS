import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt5Compat.GraphicalEffects // Pour les effets de couleur SVG

Item {
    id: bodyPageRoot

    // Thème dynamique
    readonly property color mainBg: window.carInverted ? "#F5F5F7" : "#111111"
    readonly property color carOutline: window.carInverted ? "#D1D1D6" : "#2C2C2E"
    readonly property color accentColor: "#00f2ff"
    readonly property color subTextColor: "#888888"

    Rectangle { anchors.fill: parent; color: mainBg }

    ScrollView {
        anchors.fill: parent
        contentWidth: parent.width
        clip: true

        ColumnLayout {
            width: parent.width - 80
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 40
            spacing: 40

            // --- COMFORT & SYSTEM SECTION ---
            Text { text: "COMFORT & VISIBILITY"; font.bold: true; color: "#888"; font.pixelSize: 14 ; Layout.alignment: Qt.AlignHCenter }

            Flow {
                Layout.fillWidth: true
                spacing: 20
                Layout.alignment: Qt.AlignHCenter

                VitalsItem {
                    label: "A/C State"
                    value: carCan.acActive ? "COOLING" : "OFF"
                    iconColor: carCan.acActive ? "#00AAFF" : (window.carInverted ? "#aaa" : "#333")
                }

                VitalsItem {
                    label: "Windows"
                    value: carCan.windowPos
                    unit: "% Open"
                }

                VitalsItem {
                    label: "Wipers"
                    value: ["OFF", "INT", "LOW", "HIGH"][carCan.wiperLevel] || "OFF"
                    iconColor: carCan.wiperLevel > 0 ? (window.carInverted ? "#007aff" : "cyan") : (window.carInverted ? "#444" : "#222")
                }

                VitalsItem {
                    label: "Defrost"
                    value: carCan.windshieldHeater ? "ON" : "OFF"
                    iconColor: carCan.windshieldHeater ? "orange" : (window.carInverted ? "#aaa" : "#222")
                }

                VitalsItem {
                    label: "Int. Lights"
                    value: carCan.interiorLight ? "ON" : "OFF"
                    iconColor: carCan.interiorLight ? "#FFD700" : "#555"
                }
            }

            // ==========================================
            // --- SECTION 1 : VUE INTERACTIVE ---
            // ==========================================
            Item {
                id: carVisualContainer
                Layout.fillWidth: true
                Layout.preferredHeight: 400
                Layout.alignment: Qt.AlignHCenter

                // Lueur intérieure si la lumière de courtoisie est ON
                Rectangle {
                    id: interiorGlow
                    width: 120; height: 220
                    anchors.centerIn: parent
                    radius: 30
                    color: "#FFD700"
                    opacity: carCan.interiorLight ? 0.15 : 0
                    Behavior on opacity { NumberAnimation { duration: 500 } }
                }

                // --- CORPS DE LA VOITURE (Silhouette Polo) ---
                Rectangle {
                    id: carShell
                    width: 160; height: 340
                    anchors.centerIn: parent
                    color: "transparent"
                    border.color: carOutline
                    border.width: 2
                    radius: 45

                    // --- PORTES (Animations de rotation) ---
                    DoorGraphic { // Avant Gauche
                        anchors.left: parent.left; y: 80; side: "L"
                        isOpen: carCan.doorFL
                    }
                    DoorGraphic { // Avant Droite
                        anchors.right: parent.right; y: 80; side: "R"
                        isOpen: carCan.doorFR
                    }
                    DoorGraphic { // Arrière Gauche
                        anchors.left: parent.left; y: 180; side: "L"
                        isOpen: carCan.doorRL
                    }
                    DoorGraphic { // Arrière Droite
                        anchors.right: parent.right; y: 180; side: "R"
                        isOpen: carCan.doorRR
                    }

                    // --- COFFRE (Trunk) ---
                    Rectangle {
                        width: 80; height: 4
                        anchors.bottom: parent.bottom; anchors.horizontalCenter: parent.horizontalCenter
                        color: carCan.trunk ? "red" : carOutline
                        antialiasing: true
                        y: carCan.trunk ? 15 : 0 // Animation de recul
                        Behavior on y { NumberAnimation { duration: 300 } }
                    }

                    // --- INTÉRIEUR : SIÈGES ET CEINTURES ---
                    GridLayout {
                        anchors.centerIn: parent
                        anchors.verticalCenterOffset: -20
                        columns: 2; rowSpacing: 40; columnSpacing: 20

                        SeatModule { isBuckled: carCan.beltDriver; label: "D" }
                        SeatModule { isBuckled: carCan.beltPassenger; label: "P" }
                    }
                    Item {
                        id: iconContainer
                        width: 40; height: 40
                        anchors.bottom: parent.top; anchors.bottomMargin: 15
                        anchors.horizontalCenter: parent.horizontalCenter

                        Image {
                            id: lockIcon
                            anchors.fill: parent
                            source: carCan.isLocked ? "qrc:/icons/iconsDashboard/vaadin--lock.svg" : "qrc:/icons/iconsDashboard/vaadin--unlock.svg"
                            fillMode: Image.PreserveAspectFit
                            visible: false
                        }

                        ColorOverlay {
                            anchors.fill: lockIcon
                            source: lockIcon
                            color: !carCan.isLocked ? "#ff4444" : (window.carInverted ? "#007A7C" : "#00f2ff")

                            SequentialAnimation on opacity {
                                running: !carCan.isLocked
                                loops: Animation.Infinite
                                NumberAnimation { from: 1.0; to: 0.4; duration: 800; easing.type: Easing.InOutQuad }
                                NumberAnimation { from: 0.4; to: 1.0; duration: 800; easing.type: Easing.InOutQuad }
                            }
                            opacity: carCan.isLocked ? 0.8 : 1.0
                            Behavior on color { ColorAnimation { duration: 400 } }
                        }

                        scale: carCan.isLocked ? 1.0 : 1.2
                        Behavior on scale { NumberAnimation { duration: 250; easing.type: Easing.OutBack } }
                    }

                    // --- VISUALISATION DES VITRES (Gauches et Droites) ---
                    // Vitres Gauches
                    Rectangle {
                        x: -10; y: 90; width: 4; height: 160
                        color: carOutline; opacity: 0.3; radius: 2
                        Rectangle {
                            width: parent.width; height: parent.height * (carCan.windowPos / 100)
                            color: accentColor; radius: 2; anchors.bottom: parent.bottom
                            Behavior on height { NumberAnimation { duration: 500 } }
                        }
                    }
                    // Vitres Droites
                    Rectangle {
                        x: parent.width + 6; y: 90; width: 4; height: 160
                        color: carOutline; opacity: 0.3; radius: 2
                        Rectangle {
                            width: parent.width; height: parent.height * (carCan.windowPos / 100)
                            color: accentColor; radius: 2; anchors.bottom: parent.bottom
                            Behavior on height { NumberAnimation { duration: 500 } }
                        }
                    }
                    // --- PHARES AVANT (HAUTS ET BAS) ---
                    LightIcon {
                        id: headLights
                        x: carShell.x + carShell.width / 2 - width / 2; y: carShell.y - 30 // Positionné devant
                        isHeadlights: true; isFront: true
                        lowBeamActive: carCan.lowBeam; highBeamActive: carCan.highBeam
                        fogLightsActive: carCan.fogLightsFront // Assumant que tu as une variable pour les anti-brouillards avant
                        isLowBeamSupported: true // Polo 9N3 a les feux de croisement
                    }

                    // --- PHARES ARRIÈRE (Feux de position et Antibrouillard) ---
                    LightIcon {
                        x: carShell.x + carShell.width / 2 - width / 2; y: carShell.y + carShell.height + 10 // Positionné derrière
                        isHeadlights: false; isFront: false
                        lowBeamActive: carCan.tailLights // Feux de position arrière
                        fogLightsActive: carCan.fogLightsRear // Antibrouillard arrière
                        isLowBeamSupported: true // Feux de position
                    }
                }


            }



        }
    }


// ==========================================
// --- COMPOSANTS INTERNES ---
// ==========================================

// Composant pour les portes animées
component DoorGraphic : Rectangle {
    property bool isOpen: false
    property string side: "L"
    width: 2; height: 80
    color: isOpen ? "red" : carOutline
    transformOrigin: side === "L" ? Item.TopLeft : Item.TopRight
    rotation: isOpen ? (side === "L" ? 45 : -45) : 0
    Behavior on rotation { NumberAnimation { duration: 400; easing.type: Easing.OutBack } }
}

// Composant pour les sièges/ceintures
component SeatModule : Item {
    property bool isBuckled: false
    property string label: ""
    width: 40; height: 50

    // Forme du siège
    Rectangle {
        anchors.fill: parent
        color: window.carInverted ? "#E5E5EA" : "#1C1C1E"
        radius: 8
        border.color: isBuckled ? "#4CD964" : "#FF3B30"
        border.width: 1.5

        // Icône de ceinture
        Image {
            anchors.centerIn: parent
            source: "qrc:/icons/iconsDashboard/ph--seatbelt-bold.svg"
            width: 20; height: 20
            opacity: isBuckled ? 1.0 : 0.4

            layer.enabled: true
            layer.effect: ColorOverlay {
                color: isBuckled ? "#4CD964" : "#FF3B30"
            }
        }
    }
}

    // Nouveau composant pour les icônes de phares avec effet de lumière
    component LightIcon : Item {
        property bool isFront: true // Est-ce les phares avant ou arrière?
        property bool isHeadlights: true // Est-ce les feux principaux (croisement/route) ou juste arrière?
        property bool lowBeamActive: false // Feux de croisement ou de position
        property bool highBeamActive: false // Feux de route
        property bool fogLightsActive: false // Anti-brouillards
        property bool isLowBeamSupported: false // La Polo a-t-elle des feux de croisement/position

        width: 100; height: 30

        // Effet de halo de lumière (quand les feux sont actifs)
        Rectangle {
            id: lightHalo
            width: parent.width; height: 20
            anchors.horizontalCenter: parent.horizontalCenter
            color: lowBeamActive ? "#FFD700" : (highBeamActive ? "#FFFFFF" : (fogLightsActive ? "#FFA500" : "transparent"))
            opacity: (lowBeamActive || highBeamActive || fogLightsActive) ? 0.3 : 0
            radius: 10
            visible: opacity > 0 // Optimisation

            layer.enabled: true
            layer.effect: GaussianBlur { radius: 15 } // Effet de flou pour le halo

            Behavior on opacity { NumberAnimation { duration: 300 } }
        }

        // Icône des feux de croisement/position (positionnée sur le côté gauche/avant)
        Image {
            id: lowBeamIcon
            visible: isLowBeamSupported
            source: isFront ? "qrc:/icons/iconsDashboard/light-low-beam.svg" : "qrc:/icons/iconsDashboard/light-tail.svg"
            width: 24; height: 24
            anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
            opacity: lowBeamActive ? 1.0 : 0.3

            layer.enabled: true
            layer.effect: ColorOverlay {
                color: lowBeamActive ? "#FFD700" : (window.carInverted ? "#444" : "#888") // Jaune chaud actif
            }
        }

        // Icône des feux de route (si phares avant)
        Image {
            id: highBeamIcon
            visible: isHeadlights && highBeamActive // Seulement si c'est l'avant et que les feux de route sont actifs
            source: "qrc:/icons/iconsDashboard/light-high-beam.svg"
            width: 24; height: 24
            anchors.centerIn: parent
            opacity: highBeamActive ? 1.0 : 0.3

            layer.enabled: true
            layer.effect: ColorOverlay {
                color: highBeamActive ? "#00f2ff" : (window.carInverted ? "#444" : "#888") // Bleu froid actif
            }
        }

        // Icône des anti-brouillards
        Image {
            id: fogLightIcon
            source: isFront ? "qrc:/icons/iconsDashboard/light-fog-front.svg" : "qrc:/icons/iconsDashboard/light-fog-rear.svg"
            width: 24; height: 24
            anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
            opacity: fogLightsActive ? 1.0 : 0.3

            layer.enabled: true
            layer.effect: ColorOverlay {
                color: fogLightsActive ? "#FFA500" : (window.carInverted ? "#444" : "#888") // Orange actif
            }
        }
    }
}
