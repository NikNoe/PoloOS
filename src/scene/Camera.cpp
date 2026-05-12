/**
 * @file Camera.cpp
 * @brief Implementation of the car-tracking 3D camera controller.
 */

#include "Camera.h"

CarCamera::CarCamera() {
    m_cam.up         = { 0.f, 1.f, 0.f };
    m_cam.fovy       = 50.f;
    m_cam.projection = CAMERA_PERSPECTIVE;
}

void CarCamera::update(const PoloCar& car, float dt)
{
    if (IsKeyPressed(KEY_C))
        m_mode = (AppCamMode)((m_mode + 1) % 3);

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        m_lastMouse = GetMousePosition();
        m_dragging  = true;
    }
    if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON))
        m_dragging = false;

    if (m_dragging) {
        Vector2 mouse = GetMousePosition();
        m_angle += (mouse.x - m_lastMouse.x) * 0.4f;
        m_pitch -= (mouse.y - m_lastMouse.y) * 0.4f;
        m_pitch  = Clamp(m_pitch, 5.f, 80.f);
        m_lastMouse = mouse;
    }

    m_dist -= GetMouseWheelMove() * 1.5f;
    m_dist  = Clamp(m_dist, 4.f, 50.f);

    if (IsKeyDown(KEY_Q)) m_angle -= 60.f * dt;
    if (IsKeyDown(KEY_E)) m_angle += 60.f * dt;

    float rad = car.heading * DEG2RAD;
    float s = std::sin(rad), c = std::cos(rad);

    switch (m_mode) {
    case CAM_FOLLOW:
        m_cam.position = { car.x - s * 12.f, 5.5f, car.z - c * 12.f };
        m_cam.target   = { car.x + s * 4.f,  0.8f, car.z + c * 4.f  };
        break;
    case CAM_ORBIT: {
        float oRad = m_angle * DEG2RAD;
        float pRad = m_pitch * DEG2RAD;
        m_cam.position = {
            car.x + std::cos(pRad) * std::sin(oRad) * m_dist,
            std::sin(pRad) * m_dist,
            car.z + std::cos(pRad) * std::cos(oRad) * m_dist
        };
        m_cam.target = { car.x, 1.f, car.z };
        break;
    }
    case CAM_HOOD:
        m_cam.position = { car.x + s * 1.8f,  1.4f, car.z + c * 1.8f  };
        m_cam.target   = { car.x + s * 10.f,  1.2f, car.z + c * 10.f  };
        break;
    }
}
