import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: bodyPageRoot

    Rectangle {
        anchors.fill: parent
        color: window.carInverted ? "#F5F5F7" : "#111111"
    }

    ScrollView {
        anchors.fill: parent
        contentWidth: parent.width
        clip: true

        ColumnLayout {
            width: parent.width - 80
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 40
            spacing: 30

            // --- DOORS & LOCKS SECTION ---
            Text { text: "DOORS & LOCKS"; font.bold: true; color: "#888"; font.pixelSize: 14 }

            Flow {
                Layout.fillWidth: true
                spacing: 20


                VitalsItem {
                    label: "Status"
                    value: carCan.isLocked ? "LOCKED" : "UNLOCKED"
                    iconColor: carCan.isLocked ? "#888" : "orange"
                }

                // Belts
                VitalsItem {
                    label: "Driver Belt"
                    value: carCan.beltDriver ? "BUCKLED" : "UNBUCKLED"
                    // Icon turns Red when unbuckled for safety alert
                    iconColor: carCan.beltDriver ? "#4CD964" : "#FF3B30"
                }

                VitalsItem {
                    label: "Pass. Belt"
                    value: carCan.beltPassenger ? "BUCKLED" : "UNBUCKLED"
                    iconColor: carCan.beltPassenger ? "#4CD964" : "#FF3B30"
                }


                // FRONT DOORS
                VitalsItem {
                    label: "Driver Door (FL)"
                    value: carCan.doorFL ? "OPEN" : "CLOSED"
                    iconColor: carCan.doorFL ? "red" : (window.carInverted ? "black" : "white")
                }

                VitalsItem {
                    label: "Pass. Door (FR)"
                    value: carCan.doorFR ? "OPEN" : "CLOSED"
                    iconColor: carCan.doorFR ? "red" : (window.carInverted ? "black" : "white")
                }

                // REAR DOORS
                VitalsItem {
                    label: "Rear Left"
                    value: carCan.doorRL ? "OPEN" : "CLOSED"
                    iconColor: carCan.doorRL ? "red" : (window.carInverted ? "black" : "white")
                }

                VitalsItem {
                    label: "Rear Right"
                    value: carCan.doorRR ? "OPEN" : "CLOSED"
                    iconColor: carCan.doorRR ? "red" : (window.carInverted ? "black" : "white")
                }

                VitalsItem {
                    label: "Trunk/Boot"
                    value: carCan.trunk ? "OPEN" : "CLOSED"
                    iconColor: carCan.trunk ? "red" : "#555"
                }
            }

            // --- COMFORT & SYSTEM SECTION ---
            Text { text: "COMFORT & VISIBILITY"; font.bold: true; color: "#888"; font.pixelSize: 14 }

            Flow {
                Layout.fillWidth: true
                spacing: 20

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
        }
    }

    Connections {
        target: carCan
        function onDataChanged() {
            // This forces the UI to re-evaluate all bindings linked to carCan
            console.log("BodyPage received global update from Simulator");
        }
    }
}

