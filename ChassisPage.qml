import QtQuick
import QtQuick.Layouts

Item {
    id: chassisPage

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 40
        spacing: 20

        Text { text: "CHASSIS & DYNAMICS"; color: "#888"; font.bold: true }

        // --- BRAKE & STEERING STATUS ---
        RowLayout {
            spacing: 20
            VitalsItem {
                label: "Steering"; value: carCan.steeringAngle.toFixed(1); unit: "°"
                iconColor: Math.abs(carCan.steeringAngle) > 20 ? "cyan" : "#555"
            }
            VitalsItem {
                label: "Brake Pedal"; value: carCan.brakePressed ? "PRESSED" : "RELEASED"
                iconColor: carCan.brakePressed ? "red" : "#333"
            }
            VitalsItem {
                label: "Handbrake"; value: carCan.handbrake ? "ENGAGED" : "RELEASED"
                iconColor: carCan.handbrake ? "red" : "#333"
            }
        }

        // --- WHEEL SPEEDS (4-Corner View) ---
        GridLayout {
            columns: 2
            rowSpacing: 15; columnSpacing: 15

            VitalsItem { label: "Wheel FL"; value: carCan.wheelFL; unit: "km/h" }
            VitalsItem { label: "Wheel FR"; value: carCan.wheelFR; unit: "km/h" }
            VitalsItem { label: "Wheel RL"; value: carCan.wheelRL; unit: "km/h" }
            VitalsItem { label: "Wheel RR"; value: carCan.wheelRR; unit: "km/h" }
        }

        // --- SAFETY SYSTEMS ---
        RowLayout {
            spacing: 20
            VitalsItem {
                label: "ABS"; value: carCan.absActive ? "INTERVENING" : "READY"
                iconColor: carCan.absActive ? "yellow" : "#444"
            }
            VitalsItem {
                label: "ESP/ESC"; value: carCan.espActive ? "ACTIVE" : "READY"
                iconColor: carCan.espActive ? "yellow" : "#444"
            }
            VitalsItem {
                label: "Traction"; value: carCan.tractionActive ? "SLIP" : "OK"
                iconColor: carCan.tractionActive ? "orange" : "#444"
            }
        }
    }
}
