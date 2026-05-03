#pragma once
#include "raylib.h"

// ─── RoadMap.h ────────────────────────────────────────────────────────────────
// Route 3D infinie centrée sur la voiture.
// ─────────────────────────────────────────────────────────────────────────────

class RoadMap {
public:
    RoadMap();
    void draw(float carX, float carZ);

private:
    void drawRoad      (float cx, float cz);
    void drawMarkings  (float cx, float cz);
    void drawGrid      (float cx, float cz);
    void drawSkybox    ();
    void drawBuildings (float cx, float cz);

    Color m_roadColor    = {  35,  35,  40, 255 };
    Color m_lineColor    = { 240, 220,  50, 255 };  // jaune centre
    Color m_sideColor    = { 220, 220, 220, 255 };  // blanc bord
    Color m_grassColor   = {  45,  90,  35, 255 };
    Color m_skyColor     = {  15,  20,  35, 255 };   // nuit

    float m_roadWidth    = 7.0f;   // mètres
    float m_roadLength   = 200.f;  // longueur visible de chaque côté
};