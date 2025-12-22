import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick3D
import QtQuick3D.Helpers // Required for OrbitCameraController

ApplicationWindow {
    id: window
    width: 1280
    height: 720
    visible: true
    color: "black"

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // --- LEFT PANE: 3D Polo Model ---
        Rectangle {
            Layout.preferredWidth: parent.width * 0.4
            Layout.fillHeight: true
            color: "#050505" // Dark background for the car

            View3D {
                id: carView
                anchors.fill: parent

                environment: SceneEnvironment {
                    clearColor: "#050505"
                    backgroundMode: SceneEnvironment.Color
                    antialiasingMode: SceneEnvironment.MSAA
                    antialiasingQuality: SceneEnvironment.High
                }

                // Node used as the pivot point for rotation
                Node {
                    id: carOrigin

                    // Your 3D Polo component
                    Polo {
                        id: poloModel
                        scale: Qt.vector3d(1.5, 1.5, 1.5)
                    }

                    PerspectiveCamera {
                        id: carCamera
                        z: 600 // Distance from the car
                    }
                }

                // Navigation Controller: Allows dragging to rotate and scrolling to zoom
                OrbitCameraController {
                    anchors.fill: parent
                    origin: carOrigin
                    camera: carCamera
                    mouseEnabled: true
                }

                DirectionalLight {
                    eulerRotation.x: -30
                    eulerRotation.y: 45
                    brightness: 2.0
                }

                DirectionalLight {
                    eulerRotation.x: 30
                    eulerRotation.y: -135
                    brightness: 1.0
                }
            }
        }

        // --- RIGHT PANE: Maps & Media (Unchanged) ---
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#111" // Slightly lighter gray
            radius: 15

            Text {
                text: "Navigation / Map View"
                color: "gray"
                anchors.centerIn: parent
            }
        }
    }

    // --- BOTTOM BAR: Controls (Unchanged) ---
    footer: Rectangle {
        height: 90
        color: "black"
        RowLayout {
            anchors.fill: parent
            spacing: 50

            Button { text: "Temp 22.0°"; flat: true; font.pixelSize: 18 }
            Button { text: "Music"; flat: true }
            Button { text: "Phone"; flat: true }
            Button { text: "Settings"; flat: true }
        }
    }
}
