import QtQuick
import QtQuick.Layouts

Rectangle {
    color: "#050505" // Deep black

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 40
        spacing: 15

        Text {
            text: "> SYSTEM_MANIFEST_DUMP"
            color: "#00FF00" // Terminal Green
            font.family: "Monospace"
            font.pixelSize: 18
            font.bold: true
        }

        Rectangle { Layout.fillWidth: true; height: 1; color: "#222" }

        // --- SECTION: VEHICLE DATA ---
        EngineerRow { label: "CAR MODEL"; value: "VOLKSWAGEN POLO (9N3)" }
        EngineerRow { label: "VIN"; value: carCan.vin }
        EngineerRow { label: "ECU_MILEAGE"; value: carCan.mileage.toLocaleString() + " KM" }

        Item { Layout.preferredHeight: 20 } // Spacer

        // --- SECTION: SOFTWARE STACK ---
        EngineerRow { label: "APP_VERSION"; value: "v1.2.0-STABLE" }
        EngineerRow { label: "CAN_MAP"; value: "POLO_PQ24_REV2" }
        EngineerRow { label: "GIT_COMMIT"; value: carCan.gitHash; isCode: true }
        EngineerRow { label: "BUILD_DATE"; value: carCan.buildDate }

        Item { Layout.preferredHeight: 20 } // Spacer

        // --- SECTION: HARDWARE ---
        EngineerRow { label: "HOST_HW"; value: "Raspberry Pi 4 Model B (4GB)" }
        EngineerRow { label: "CAN_CONTROLLER"; value: "MCP2515 @ 8MHz" }
        EngineerRow { label: "OS_KERNEL"; value: "Linux 6.1.21-v8+ aarch64" }

        Text {
            Layout.alignment: Qt.AlignBottom
            text: "LOGGED AS: ROOT_ADMIN | BUS_STATUS: OK"
            color: "#444"
            font.family: "Monospace"
            font.pixelSize: 10
        }
    }
}
