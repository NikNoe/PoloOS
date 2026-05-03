import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    Rectangle {
        anchors.centerIn: parent
        width: 300; height: 100
        color: "#1a1a2e"
        radius: 8
        Text {
            anchors.centerIn: parent
            text: "🗺  Carte non disponible sur cette plateforme"
            color: "#8b949e"
            font.pixelSize: 14
        }
    }
}
