#pragma once
#include "PoloCar.h"
#include "raylib.h"
#include "raymath.h"
#include <string>

// ─── CarRenderer.h ────────────────────────────────────────────────────────────
// Charge chaque partie animable séparément et applique les transformations.
// ─────────────────────────────────────────────────────────────────────────────

class CarRenderer {
public:
    CarRenderer();
    ~CarRenderer();
    void draw(const PoloCar& car);

private:
    // ── Modèles ───────────────────────────────────────────────────────────────
    Model m_body;
    Model m_doorLF, m_doorLR, m_doorRF, m_doorRR;
    Model m_trunk;
    Model m_wheelFL, m_wheelFR, m_wheelRL, m_wheelRR;
    Model m_headL, m_headR;
    Model m_tailL, m_tailR;
    Model m_blinkerFL, m_blinkerFR, m_blinkerRL, m_blinkerRR;

    // ── Helpers ───────────────────────────────────────────────────────────────
    Model   loadPart   (const std::string& name);
    void    unloadAll  ();

    void    drawBody   (const PoloCar& car);
    void    drawDoors  (const PoloCar& car);
    void    drawTrunk  (const PoloCar& car);
    void    drawWheels (const PoloCar& car);
    void    drawLights (const PoloCar& car);

    // Dessine un modèle avec position/rotation locales à la voiture
    void    drawPart   (Model& model, const PoloCar& car,
                        float lx, float ly, float lz,
                        float extraRotAxis_x, float extraRotAxis_y, float extraRotAxis_z,
                        float extraAngle,
                        Color tint = WHITE);

    // Pivot animé : rotation autour d'un point local
    void    drawPivot  (Model& model, const PoloCar& car,
                        float pivotLX, float pivotLY, float pivotLZ,
                        float rotAxisX, float rotAxisY, float rotAxisZ,
                        float angle,
                        Color tint = WHITE);

    Vector3 localToWorld(const PoloCar& car, float lx, float ly, float lz);
};