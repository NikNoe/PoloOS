import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects // Module moderne pour Qt 6.7+

Item {
    id: root
    width: 44; height: 44

    // Propriétés
    property url iconSource: ""
    property color activeColor: "#FFFFFF"
    property bool isActive: false
    property bool isBlinking: false

    // 1. L'image source (sert de masque de base)
    Image {
        id: iconInternal
        source: root.iconSource
        anchors.fill: parent
        anchors.margins: 4
        fillMode: Image.PreserveAspectFit
        sourceSize.width: width
        sourceSize.height: height
        visible: false // Cachée car MultiEffect l'utilise en source
        antialiasing: true
    }

    // 2. L'effet combiné (Remplace ColorOverlay ET Glow)
    MultiEffect {
        id: effect
        anchors.fill: iconInternal
        source: iconInternal

        // --- Gestion de la Couleur ---
        colorization: 1.0 // Applique la coloration à 100%
        colorizationColor: root.isActive ? root.activeColor : "#1a1a1a"

        // --- Gestion de la Lueur (Glow) ---
        shadowEnabled: root.isActive
        shadowColor: root.activeColor
        shadowBlur: 0.8
        shadowHorizontalOffset: 0
        shadowVerticalOffset: 0

        // Effet brillant quand l'icône est active
        brightness: root.isActive ? 0.2 : 0.0

        // Transition fluide de la couleur
        Behavior on colorizationColor { ColorAnimation { duration: 200 } }
    }

    // 3. Animation de clignotement (Blinker)
    SequentialAnimation {
        id: blinkAnim
        running: root.isActive && root.isBlinking
        loops: Animation.Infinite

        NumberAnimation {
            target: effect // On anime l'effet pour plus de fluidité
            property: "opacity"
            from: 1.0; to: 0.1
            duration: 400
            easing.type: Easing.InOutQuad
        }
        NumberAnimation {
            target: effect
            property: "opacity"
            from: 0.1; to: 1.0
            duration: 400
            easing.type: Easing.InOutQuad
        }
    }

    // Réinitialisation propre
    onIsActiveChanged: if (!isActive) effect.opacity = 1.0;
    onIsBlinkingChanged: if (!isBlinking) effect.opacity = 1.0;
}
