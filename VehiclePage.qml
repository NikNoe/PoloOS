import QtQuick

Item {
    Column {
        anchors.centerIn: parent
        Text {
            text: "Vehicle Status"
            color: window.carInverted ? "black" : "white"
            font.pixelSize: 24
        }
        Text {
            text: "Polo 9N3 - 1.9 TDI"
            color: "gray"
        }
    }
}
