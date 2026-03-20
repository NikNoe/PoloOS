// Dans ton ApplicationWindow (Main.qml),
// remplace l'ancienne ligne :
//
//   CockpitWindow { id: cockpit }
//
// par ce bloc complet :

    // ─── SIMULATEUR ──────────────────────────────────────────────────────────
    CockpitWindow {
        id: cockpit
        busDetected: carCan.busEngineActive
    }

    // ─── TOAST de notification ───────────────────────────────────────────────
    Rectangle {
        id: busToast
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 14
        width: busToastText.implicitWidth + 40
        height: 40
        radius: 20
        color: "#1D9E75"
        opacity: 0
        z: 100

        Text {
            id: busToastText
            anchors.centerIn: parent
            text: ""
            color: "white"
            font.pixelSize: 13
            font.bold: true
        }

        SequentialAnimation {
            id: toastAnim
            NumberAnimation { target: busToast; property: "opacity"; to: 1.0; duration: 250 }
            PauseAnimation  { duration: 3000 }
            NumberAnimation { target: busToast; property: "opacity"; to: 0.0; duration: 400 }
        }
    }

    // ─── Helpers ─────────────────────────────────────────────────────────────
    function showToast(msg, hexColor) {
        busToastText.text = msg
        busToast.color = hexColor
        toastAnim.restart()
    }

    function fpsLine() {
        var parts = []
        if (carCan.busEngineActive)  parts.push("Engine "  + carCan.engineFps  + " fps")
        if (carCan.busComfortActive) parts.push("Comfort " + carCan.comfortFps + " fps")
        return parts.length > 0 ? "  •  " + parts.join("  |  ") : ""
    }

    // ─── Réactions aux changements d'état ────────────────────────────────────
    Connections {
        target: carCan

        function onBusEngineActiveChanged() {
            if (carCan.busEngineActive)
                showToast("✓ Engine CAN détecté" + fpsLine() + " — simulateur fermé", "#1D9E75")
            else
                showToast("⚠ Engine CAN perdu — simulateur réactivé", "#BA7517")
        }

        function onBusComfortActiveChanged() {
            if (carCan.busComfortActive)
                showToast("✓ Comfort CAN actif" + fpsLine(), "#378ADD")
            else
                showToast("⚠ Comfort CAN perdu", "#BA7517")
        }

        function onDiagChanged() {
            if (toastAnim.running) return
            if (!carCan.busEngineActive && !carCan.busComfortActive) return
            showToast("CAN" + fpsLine(), "#185FA5")
        }
    }
