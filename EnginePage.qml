import QtQuick
import QtQuick.Controls

Item {
    id: enginePageRoot

    // This ensures the sub-page background is identical to the sidebar
    Rectangle {
        anchors.fill: parent
        color: window.carInverted ? "#F5F5F7" : "#111111"
    }

    SwipeView {
        id: engineSwipe
        anchors.fill: parent
        currentIndex: indicator.currentIndex

        // Your 3 sub-pages
        Loader { source: "EngineLive.qml" }
        Loader { source: "EngineConsumption.qml" }
        Loader { source: "EngineFlags.qml" }
    }

    // Tesla-style dot indicator at the bottom
    PageIndicator {
        id: indicator
        count: engineSwipe.count
        currentIndex: engineSwipe.currentIndex
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter

        delegate: Rectangle {
            implicitWidth: 8; implicitHeight: 8
            radius: 4
            color: window.carInverted ? "black" : "white"
            opacity: index === indicator.currentIndex ? 0.9 : 0.2

            Behavior on opacity { NumberAnimation { duration: 200 } }
        }
    }
}
