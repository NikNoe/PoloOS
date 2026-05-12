import QtQuick

Item {
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
