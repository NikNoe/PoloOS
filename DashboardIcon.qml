import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

Item {
    id: root
    width: 44; height: 44 // Taille légèrement augmentée pour lisibilité

    // Propriétés
    property url iconSource: ""
    property color activeColor: "#FFFFFF"
    property bool isActive: false
    property bool isBlinking: false

    // 1. L'image source (cachée, sert de masque)
    Image {
        id: iconInternal
        source: root.iconSource
        anchors.fill: parent
        anchors.margins: 4
        fillMode: Image.PreserveAspectFit
        sourceSize.width: width
        sourceSize.height: height
        visible: false // On ne l'affiche pas directement
        antialiasing: true
    }

    // 2. La couche de couleur (ColorOverlay)
    ColorOverlay {
        id: colorLayer
        anchors.fill: iconInternal
        source: iconInternal
        // Si inactif : gris très sombre. Si actif : la couleur choisie.
        color: root.isActive ? root.activeColor : "#1a1a1a"

        // Transition douce de la couleur
        Behavior on color { ColorAnimation { duration: 200 } }
    }

    // 3. L'effet de lueur (Glow)
    Glow {
        id: glowEffect
        anchors.fill: colorLayer
        radius: 8
        samples: 17
        color: root.activeColor
        source: colorLayer
        visible: root.isActive
    }

    // 4. Gestion de l'animation (Clignotement ou Allumage fixe)
    SequentialAnimation {
        id: blinkAnim
        running: root.isActive && root.isBlinking
        loops: Animation.Infinite

        NumberAnimation { target: root; property: "opacity"; from: 1.0; to: 0.2; duration: 400; easing.type: Easing.InOutQuad }
        NumberAnimation { target: root; property: "opacity"; from: 0.2; to: 1.0; duration: 400; easing.type: Easing.InOutQuad }
    }

    // Réinitialise l'opacité quand on arrête de clignoter ou quand c'est fixe
    onIsActiveChanged: {
        if (!isActive) root.opacity = 1.0;
    }
    onIsBlinkingChanged: {
        if (!isBlinking) root.opacity = 1.0;
    }
}
