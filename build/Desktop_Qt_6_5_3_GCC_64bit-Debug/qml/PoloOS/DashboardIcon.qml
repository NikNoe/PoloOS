import QtQuick

Item {
    id: root
    width: 48; height: 48 // Taille recommandée pour la lisibilité

    property url iconSource: ""
    property bool isActive: false
    property bool isBlinking: false

    // LOGIQUE DE VISIBILITÉ :
    // 1. Si inactif : opacité 0 (invisible mais garde sa place dans le Row/Column)
    // 2. Si actif : opacité 1
    // 3. Si actif + clignotant : alterne entre 1 et 0 via le Timer
    opacity: isActive ? (isBlinking ? (blinkTimer.visibleState ? 1.0 : 0.0) : 1.0) : 0.0


    Image {
        id: iconImage
        source: root.iconSource
        anchors.fill: parent
        anchors.margins: 2
        fillMode: Image.PreserveAspectFit

        // Optimisation pour garder le vecteur net
        sourceSize.width: width
        sourceSize.height: height

        antialiasing: true
    }

    // Timer pour un clignotement "net" (Style industriel Polo 9N3)
    Timer {
        id: blinkTimer
        property bool visibleState: true
        interval: 400 // Rythme standard automobile
        running: root.isBlinking && root.isActive
        repeat: true
        onTriggered: visibleState = !visibleState
        onRunningChanged: if(!running) visibleState = true
    }
}
