#pragma once
#include "raylib.h"
#include "raymath.h"
#include "../car/PoloCar.h"
#include <cmath>

enum AppCamMode { CAM_FOLLOW, CAM_ORBIT, CAM_HOOD };

class CarCamera {
public:
    CarCamera();
    void update(const PoloCar& car, float dt);
    Camera3D& get() { return m_cam; }
    AppCamMode mode() const { return m_mode; }

private:
    Camera3D   m_cam      = {};
    AppCamMode m_mode     = CAM_FOLLOW;
    float      m_angle    = 0.f;
    float      m_pitch    = 20.f;
    float      m_dist     = 18.f;
    Vector2    m_lastMouse = { 0.f, 0.f };
    bool       m_dragging  = false;
};