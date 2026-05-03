import QtQuick
import QtPositioning
import QtLocation

Item {
    id: mapPage
    anchors.fill: parent

    Plugin {
        id: mapPlugin
        name: "osm"

        // On force l'adresse du serveur officiel d'OpenStreetMap
        // Qt 6 utilise le format %z/%x/%y
        PluginParameter {
            name: "osm.mapping.custom.host"
            value: "https://tile.openstreetmap.org/%z/%x/%y.png"
        }

        // Indispensable pour que le serveur OSM accepte ta connexion
        PluginParameter {
            name: "osm.useragent"
            value: "PoloOS_HMI"
        }


        // On désactive la recherche de serveurs par défaut qui échoue
        PluginParameter {
            name: "osm.mapping.providersrepository.disabled"
            value: true
        }
    }

    Map {
        id: mainMap
        anchors.fill: parent
        plugin: mapPlugin

        // Coordonnées fixes pour éviter les erreurs de positionnement au début
        center: QtPositioning.coordinate(48.8584, 2.2945) // Tour Eiffel
        zoomLevel: 13

        // Si le signal onSupportedMapTypesChanged ne marche pas,
        // on laisse la Map choisir son style par défaut.
    }

    // --- BOUTONS DE ZOOM (Simplifiés) ---
    Column {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 30
        spacing: 15
        z: 10

        Rectangle {
            width: 50; height: 50; radius: 25; color: "#222222"; opacity: 0.8
            Text { text: "+"; anchors.centerIn: parent; color: "white"; font.pixelSize: 22 }
            MouseArea { anchors.fill: parent; onClicked: mainMap.zoomLevel++ }
        }
        Rectangle {
            width: 50; height: 50; radius: 25; color: "#222222"; opacity: 0.8
            Text { text: "-"; anchors.centerIn: parent; color: "white"; font.pixelSize: 22 }
            MouseArea { anchors.fill: parent; onClicked: mainMap.zoomLevel-- }
        }
    }
}
