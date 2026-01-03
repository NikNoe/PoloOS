import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 400
    height: 600
    visible: true
    title: "Polo 9N3 Simulator Cockpit"
    color: "#222"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 30

        Text { text: "SIMULATOR CONTROLS"; color: "white"; font.bold: true }

        // --- STEERING WHEEL ---
        ColumnLayout {
            Text { text: "Steering Wheel: " + steerSlider.value.toFixed(0) + "°"; color: "white" }
            Slider {
                id: steerSlider
                from: -450; to: 450; value: 0
                Layout.fillWidth: true
                onMoved: carCan.steeringAngle = value
            }
        }

        // --- GAS PEDAL (RPM) ---
        ColumnLayout {
            Text { text: "Gas Pedal (RPM): " + rpmSlider.value.toFixed(0); color: "white" }
            Slider {
                id: rpmSlider
                from: 800; to: 7000; value: 800
                Layout.fillWidth: true
                onMoved: carCan.rpm = value
            }
        }

        // --- SWITCHES ---
        RowLayout {
            spacing: 20
            Button {
                text: "HANDBRAKE"
                palette.button: carCan.handbrake ? "red" : "#444"
                onClicked: carCan.handbrake = !carCan.handbrake
            }

            Button {
                text: "LEFT BLINKER"
                onClicked: carCan.blinkerStatus = (carCan.blinkerStatus === 1 ? 0 : 1)
            }
        }

        // --- DOOR TOGGLES ---
        GridLayout {
            columns: 2
            Button { text: "Front Left"; onClicked: carCan.doorFL = !carCan.doorFL }
            Button { text: "Front Right"; onClicked: carCan.doorFR = !carCan.doorFR }
        }

        Item { Layout.fillHeight: true } // Spacer
    }
}
