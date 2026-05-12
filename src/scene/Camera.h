#pragma once

/**
 * @file Camera.h
 * @brief 3D camera controller with Follow, Orbit and Hood modes.
 */

#include "raylib.h"
#include "raymath.h"
#include "../car/PoloCar.h"
#include <cmath>

/**
 * @brief Application camera modes.
 */
enum AppCamMode {
    CAM_FOLLOW, ///< Fixed offset behind the car.
    CAM_ORBIT,  ///< Free orbital camera centred on the car.
    CAM_HOOD    ///< First-person bonnet / hood view.
};

/**
 * @brief Manages the Raylib 3D camera, tracking the player's car.
 *
 * Cycles through three modes with the C key. In Orbit mode the camera can be
 * rotated by right-click dragging and zoomed with the scroll wheel.
 */
class CarCamera {
public:
    /** @brief Initialises the camera with a perspective projection. */
    CarCamera();

    /**
     * @brief Updates the camera position and target for the current frame.
     *
     * Handles mode switching (C key), orbit mouse drag (right button),
     * scroll-wheel zoom and keyboard rotation (Q/E keys).
     *
     * @param car Current car state (position and heading).
     * @param dt  Time step since the last frame (seconds).
     */
    void update(const PoloCar& car, float dt);

    /**
     * @brief Returns the underlying Raylib Camera3D for BeginMode3D().
     * @return Mutable reference to the internal camera.
     */
    Camera3D& get() { return m_cam; }

    /**
     * @brief Returns the currently active camera mode.
     * @return One of CAM_FOLLOW, CAM_ORBIT or CAM_HOOD.
     */
    AppCamMode mode() const { return m_mode; }

private:
    Camera3D   m_cam       = {};             ///< Raylib camera handle.
    AppCamMode m_mode      = CAM_HOOD;       ///< Active camera mode.
    float      m_angle     = 0.f;            ///< Orbit yaw angle (degrees).
    float      m_pitch     = 20.f;           ///< Orbit pitch angle (degrees).
    float      m_dist      = 18.f;           ///< Orbit distance from target (metres).
    Vector2    m_lastMouse = { 0.f, 0.f };   ///< Mouse position at drag start.
    bool       m_dragging  = false;          ///< True while right mouse button is held.
};
