// BusStatusCard.qml
import QtQuick
import QtQuick.Layouts

Rectangle {
    property string title: ""
    property bool active: false
    property int fps: 0
    property int errors: 0

    Layout.fillWidth: true; Layout.preferredHeight: 100
    color: "#222"; radius: 10; border.color: active ? "#2ECC71" : "#E74C3C"

    ColumnLayout {
        anchors.centerIn: parent
        Text { text: title; color: "#888"; font.pixelSize: 10; Layout.alignment: Qt.AlignHCenter }
        Text {
            text: active ? "CONNECTED" : "OFFLINE"
            color: active ? "#2ECC71" : "#E74C3C"; font.bold: true
            Layout.alignment: Qt.AlignHCenter
        }
        Text { text: fps + " fps | " + errors + " errors"; color: "white"; font.pixelSize: 12; Layout.alignment: Qt.AlignHCenter }
    }
}
