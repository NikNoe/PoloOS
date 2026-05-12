#pragma once
#include "../network/DetectedObject.h"
#include "raylib.h"
#include "raymath.h"

// ─── TrafficAgent.h ───────────────────────────────────────────────────────────
// Représente un objet détecté par YOLO dans la scène 3D.
// Interpolation smooth entre les mises à jour UDP.
// ─────────────────────────────────────────────────────────────────────────────

class TrafficAgent {
public:
    TrafficAgent() = default;
    explicit TrafficAgent(const DetectedObject& det);

    void update(const DetectedObject& det, float dt);
    void draw() const;

    float x()          const { return m_x; }
    float z()          const { return m_z; }
    float heading()    const { return m_heading; }
    float confidence() const { return m_confidence; }
    float ttl()        const { return m_ttl; }
    ObjectClass cls()  const { return m_cls; }
    bool  isAlive()    const { return m_ttl > 0.f; }
    static void loadSharedModels();
    static void unloadSharedModels();
    int trackId() const { return m_trackId; }

private:
    float       m_x          = 0.f;
    float       m_z          = 0.f;
    float       m_heading    = 0.f;
    float       m_confidence = 0.f;
    float       m_ttl        = 1.5f;
    float       m_scale      = 1.f;
    ObjectClass m_cls        = ObjectClass::UNKNOWN;
    std::string m_className;
    int m_trackId = -1;

    // Couleur selon classe
    Color classColor() const;
    float classHeight() const;
    float classRadius() const;

    // Label affiché au-dessus
    void drawLabel(Vector3 pos) const;

    // Meshes statiques partagés — chargés une seule fois
    static Model s_carModel;
    static Model s_personModel;
    static Model s_boxModel;
    static bool  s_modelsLoaded;
};