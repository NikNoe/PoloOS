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

}
