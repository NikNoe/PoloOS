#include "TrafficAgent.h"
#include <cmath>
#include <cstdio>

// ─── TrafficAgent.cpp ─────────────────────────────────────────────────────────

#ifndef DEG2RAD
#define DEG2RAD 0.0174532925f
#endif

// En haut du fichier
Model TrafficAgent::s_carModel    = {};
Model TrafficAgent::s_personModel = {};
Model TrafficAgent::s_boxModel    = {};
bool  TrafficAgent::s_modelsLoaded = false;

void TrafficAgent::loadSharedModels() {
    if (s_modelsLoaded) return;
    s_carModel    = LoadModelFromMesh(GenMeshCube(1.8f, 1.4f, 3.8f));
    s_personModel = LoadModelFromMesh(GenMeshCylinder(0.25f, 1.6f, 8));
    s_boxModel    = LoadModelFromMesh(GenMeshCube(0.8f, 1.2f, 0.8f));
    s_modelsLoaded = true;
}

void TrafficAgent::unloadSharedModels() {
    UnloadModel(s_carModel);
    UnloadModel(s_personModel);
    UnloadModel(s_boxModel);
    s_modelsLoaded = false;
}

TrafficAgent::TrafficAgent(const DetectedObject& det) {
    m_x          = det.x;
    m_z          = det.z;
    m_heading    = det.heading;
    m_confidence = det.confidence;
    m_cls        = det.cls;
    m_className  = det.className;
    m_ttl        = det.ttl;
    m_trackId = det.trackId;
}

void TrafficAgent::update(const DetectedObject& det, float dt) {
    // Interpolation smooth
    m_trackId = det.trackId;
    m_x          = m_x * 0.4f + det.x * 0.6f;
    m_z          = m_z * 0.4f + det.z * 0.6f;
    m_heading    = det.heading;
    m_confidence = det.confidence;
    m_ttl        = det.ttl;
}

// ── Couleurs par classe ───────────────────────────────────────────────────────
Color TrafficAgent::classColor() const {
    switch (m_cls) {
        case ObjectClass::CAR:           return { 0,   180, 255, 220 };
        case ObjectClass::TRUCK:         return { 255, 140,  0,  220 };
        case ObjectClass::BUS:           return { 255, 200,  0,  220 };
        case ObjectClass::MOTORCYCLE:    return { 180,  0,  255, 220 };
        case ObjectClass::BICYCLE:       return { 0,   255, 180, 220 };
        case ObjectClass::PEDESTRIAN:    return { 255,  80,  80, 220 };
        case ObjectClass::TRAFFIC_LIGHT: return { 255, 255,   0, 220 };
        case ObjectClass::STOP_SIGN:     return { 220,  0,    0, 220 };
        default:                         return { 128, 128, 128, 180 };
    }
}

float TrafficAgent::classHeight() const {
    switch (m_cls) {
        case ObjectClass::PEDESTRIAN:    return 1.75f;
        case ObjectClass::BICYCLE:       return 1.2f;
        case ObjectClass::MOTORCYCLE:    return 1.2f;
        case ObjectClass::CAR:           return 1.5f;
        case ObjectClass::TRUCK:         return 3.5f;
        case ObjectClass::BUS:           return 3.0f;
        case ObjectClass::TRAFFIC_LIGHT: return 0.8f;
        case ObjectClass::STOP_SIGN:     return 0.6f;
        default:                         return 1.5f;
    }
}

float TrafficAgent::classRadius() const {
    switch (m_cls) {
        case ObjectClass::PEDESTRIAN:    return 0.3f;
        case ObjectClass::BICYCLE:       return 0.4f;
        case ObjectClass::MOTORCYCLE:    return 0.5f;
        case ObjectClass::CAR:           return 1.0f;
        case ObjectClass::TRUCK:         return 1.5f;
        case ObjectClass::BUS:           return 1.5f;
        case ObjectClass::TRAFFIC_LIGHT: return 0.2f;
        case ObjectClass::STOP_SIGN:     return 0.3f;
        default:                         return 0.8f;
    }
}

// ── Rendu 3D ──────────────────────────────────────────────────────────────────
void TrafficAgent::draw() const {
    if (!isAlive()) return;

    Vector3 pos    = { m_x, 0.f, m_z };
    Color   col    = classColor();
    float   h      = classHeight();
    float   r      = classRadius();

    // Fade selon TTL
    float fade = m_ttl / 1.5f;
    col.a = (unsigned char)(col.a * fade);

    // Corps principal
    if (m_cls == ObjectClass::PEDESTRIAN) {
        // Piéton — capsule simplifiée (cylindre + sphère)
        DrawModelEx(s_personModel, pos, {0,1,0}, 0.f, {1,1,1}, col);
        DrawSphere({ pos.x, h * 0.75f + r * 0.35f, pos.z },
                   r * 0.35f, col);
    } else if (m_cls == ObjectClass::TRAFFIC_LIGHT) {
        // Feu tricolore — poteau + boîtier
        DrawCylinder(pos, 0.05f, 0.05f, 2.5f, 6,
                     { 60, 60, 60, (unsigned char)(200 * fade) });
        DrawCube({ pos.x, 2.6f, pos.z }, 0.3f, 0.7f, 0.2f, col);
    } else if (m_cls == ObjectClass::STOP_SIGN) {
        // Panneau stop — poteau + panneau rouge
        DrawCylinder(pos, 0.04f, 0.04f, 2.0f, 6,
                     { 60, 60, 60, (unsigned char)(200 * fade) });
        DrawCube({ pos.x, 2.1f, pos.z }, 0.6f, 0.6f, 0.05f, col);
    } else {
        // Véhicule — boîte orientée
        float rad = m_heading * DEG2RAD;
        Vector3 center = { pos.x, h * 0.5f, pos.z };
        DrawModelEx(
            s_carModel,
            center,
            { 0.f, 1.f, 0.f },
            m_heading,
            { 1.f, 1.f, 1.f },
            col
        );

        // Indicateur direction (flèche)
        Vector3 arrow = {
            pos.x + std::sin(rad) * r * 2.f,
            0.1f,
            pos.z + std::cos(rad) * r * 2.f
        };
        DrawLine3D({ pos.x, 0.1f, pos.z }, arrow,
                   { 255, 255, 255, (unsigned char)(180 * fade) });
    }

    // Cercle au sol
    DrawCircle3D(pos, r * 1.2f, { 1, 0, 0 }, 90.f,
                 { col.r, col.g, col.b, (unsigned char)(120 * fade) });

    // Label
    drawLabel({ pos.x, h + 0.3f, pos.z });
}

void TrafficAgent::drawLabel(Vector3 pos) const {
    char buf[64];
    std::snprintf(buf, sizeof(buf), "%s %.0f%%",
                  m_className.c_str(), m_confidence * 100.f);

    // Billboard 2D via DrawText3D n'existe pas en Raylib de base
    // On utilise DrawLine3D comme indicateur vertical à la place
    Color col = classColor();
    float fade = m_ttl / 1.5f;
    DrawLine3D({ pos.x, 0.f, pos.z },
               { pos.x, pos.y, pos.z },
               { col.r, col.g, col.b, (unsigned char)(150 * fade) });
}