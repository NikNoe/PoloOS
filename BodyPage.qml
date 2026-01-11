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
                    value: canHandler.isLocked ? "LOCKED" : "UNLOCKED"
                    iconColor: canHandler.isLocked ? "#888" : "orange"
                }

                VitalsItem {
                    label: "Driver Door"
                    value: canHandler.doorFL ? "OPEN" : "CLOSED"
                    iconColor: canHandler.doorFL ? "red" : (window.carInverted ? "black" : "white")
                }

                VitalsItem {
                    label: "Trunk/Boot"
                    value: canHandler.trunk ? "OPEN" : "CLOSED"
                    iconColor: canHandler.trunk ? "red" : "#555"
                }
            }

            // --- COMFORT & SYSTEM SECTION ---
            Text { text: "COMFORT & VISIBILITY"; font.bold: true; color: "#888"; font.pixelSize: 14 }

            Flow {
                Layout.fillWidth: true
                spacing: 20

                VitalsItem {
                    label: "A/C State"
                    value: canHandler.acActive ? "COOLING" : "OFF"
                    iconColor: canHandler.acActive ? "#00AAFF" : (window.carInverted ? "#aaa" : "#333")
                }

                VitalsItem {
                    label: "Windows"
                    value: canHandler.windowPos
                    unit: "% Open"
                }

                VitalsItem {
                    label: "Wipers"
                    value: ["OFF", "INT", "LOW", "HIGH"][canHandler.wiperLevel] || "OFF"
                    iconColor: canHandler.wiperLevel > 0 ? (window.carInverted ? "#007aff" : "cyan") : (window.carInverted ? "#444" : "#222")
                }

                VitalsItem {
                    label: "Defrost"
                    value: canHandler.windshieldHeater ? "ON" : "OFF"
                    iconColor: canHandler.windshieldHeater ? "orange" : (window.carInverted ? "#aaa" : "#222")
                }

                VitalsItem {
                    label: "Int. Lights"
                    value: canHandler.interiorLight ? "ON" : "OFF"
                    iconColor: canHandler.interiorLight ? "#FFD700" : "#555"
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

