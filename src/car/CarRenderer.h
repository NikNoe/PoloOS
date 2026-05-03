#pragma once
#include "PoloCar.h"
#include "raylib.h"
#include "raymath.h"

// ─── CarRenderer.h ────────────────────────────────────────────────────────────
// Rendu 3D de la Polo en primitives Raylib.
// Conçu pour être remplacé par un vrai mesh .glb sans toucher PoloCar.
// ─────────────────────────────────────────────────────────────────────────────

class CarRenderer {
public:
    CarRenderer();

    void draw(const PoloCar& car);

private:
    // Couleurs
    Color m_bodyColor     = { 30,  60, 180, 255 };  // Bleu Polo
    Color m_glassColor    = { 140, 200, 220, 160 };  // Bleu transparent
    Color m_wheelColor    = { 30,   30,  30, 255 };  // Noir pneu
    Color m_rimColor      = { 180, 180, 190, 255 };  // Argent jante
    Color m_lightOnLow    = { 255, 240, 180, 255 };  // Jaune chaud feux codes
    Color m_lightOnHigh   = { 255, 255, 255, 255 };  // Blanc feux route
    Color m_lightOff      = { 60,   60,  60, 255 };  // Gris éteint
    Color m_blinkerOn     = { 255, 160,   0, 255 };  // Orange cligno
    Color m_blinkerOff    = { 80,   50,   0, 255 };  // Orange sombre éteint
    Color m_brakeLight    = { 220,  20,  20, 255 };  // Rouge stop

    // Helpers de dessin
    void drawBody      (Vector3 origin, float heading);
    void drawDoors     (Vector3 origin, float heading, const PoloCar& car);
    void drawTrunk     (Vector3 origin, float heading, float angle);
    void drawHood      (Vector3 origin, float heading, float angle);
    void drawWheel     (Vector3 pos, float steer, float roll, bool mirrorX);
    void drawLights    (Vector3 origin, float heading, const PoloCar& car);
    void drawWireframe (Vector3 origin, float heading);

    // Utilitaire : appliquer rotation heading à un offset local
    Vector3 localToWorld(Vector3 origin, float heading,
                         float lx, float ly, float lz);
};