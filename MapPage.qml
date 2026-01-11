import QtQuick
import QtPositioning
import QtLocation

Item {
    id: mapPage
    anchors.fill: parent

    Plugin {
        id: mapPlugin
        name: "osm"

        // 2. Disable the default provider repository to stop the "API Required" message
        PluginParameter {
            name: "osm.mapping.providersrepository.disabled"
            value: true
        }

        // This is the "Secret Sauce" for Qt 6:
        // We tell the OSM plugin to fetch tiles from Maptiler instead of OpenStreetMap.
        PluginParameter {
            name: "osm.mapping.custom.host"
                        // Note the %z/%x/%y format for Qt 6
            value: "https://api.maptiler.com/maps/darkmatter/%z/%x/%y.png?key=4yhr2bUQrOxesEe95COD"
        }



        // Required by OSM servers to identify the app
        PluginParameter { name: "osm.useragent"; value: "PoloOS_HMI" }
    }

    Map {
        id: mainMap
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(48.8566, 2.3522)
        zoomLevel: 12

        // Note: 'tilt' and 'bearing' are limited in the standard OSM plugin compared to Mapbox
        // but it is the most reliable "Free" way to get a map appearing.
    }

    // 3. THIS IS CRITICAL: Tell the map to use the Custom Host we defined above
    // Instead of direct assignment, we wait for the Map to load its plugins
            Component.onCompleted: {
                for (var i = 0; i < supportedMapTypes.length; i++) {
                    // The CustomMap type is created automatically when osm.mapping.custom.host is set
                    if (supportedMapTypes[i].style === MapType.CustomMap) {
                        mainMap.activeMapType = supportedMapTypes[i];
                        break;
                    }
                }
            }

    // --- ZOOM BUTTONS ---
    Column {
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.margins: 20
        spacing: 15

        Rectangle {
            width: 50; height: 50; radius: 25
            color: window.carInverted ? "#FFFFFF" : "#222222"
            opacity: 0.9
            Text { text: "+"; anchors.centerIn: parent; color: window.carInverted ? "black" : "white"; font.pixelSize: 24 }
            MouseArea { anchors.fill: parent; onClicked: mainMap.zoomLevel += 1 }
        }

        Rectangle {
            width: 50; height: 50; radius: 25
            color: window.carInverted ? "#FFFFFF" : "#222222"
            opacity: 0.9
            Text { text: "-"; anchors.centerIn: parent; color: window.carInverted ? "black" : "white"; font.pixelSize: 24 }
            MouseArea { anchors.fill: parent; onClicked: mainMap.zoomLevel -= 1 }
        }
    }
}
