#include "RoadMap.h"
#include <cmath>

// ─── RoadMap.cpp ──────────────────────────────────────────────────────────────

RoadMap::RoadMap() {}

void RoadMap::draw(float carX, float carZ)
{
    drawSkybox();
    drawRoad(carX, carZ);
    drawMarkings(carX, carZ);
    drawBuildings(carX, carZ);
}

// ── Sol + route ────────────────────────────────────────────────────────────────
void RoadMap::drawRoad(float cx, float cz)
{
    float L = m_roadLength;
    float W = m_roadWidth;

    // Herbe large
    DrawPlane({ cx, 0.f, cz }, { L * 2.f, L * 2.f }, m_grassColor);

    // Chaussée
    DrawCube({ cx, 0.01f, cz }, W, 0.02f, L * 2.f, m_roadColor);

    // Trottoirs
    DrawCube({ cx - W * 0.5f - 0.5f, 0.05f, cz }, 0.8f, 0.1f, L * 2.f, {80, 80, 85, 255});
    DrawCube({ cx + W * 0.5f + 0.5f, 0.05f, cz }, 0.8f, 0.1f, L * 2.f, {80, 80, 85, 255});
}

// ── Marquages routiers ────────────────────────────────────────────────────────
void RoadMap::drawMarkings(float cx, float cz)
{
    float L = m_roadLength;

    // Ligne centrale jaune discontinue
    float dashLen  = 3.0f;
    float dashGap  = 3.0f;
    float step     = dashLen + dashGap;
    float startZ   = std::floor((cz - L) / step) * step;

    for (float z = startZ; z < cz + L; z += step) {
        DrawCube({ cx, 0.02f, z }, 0.12f, 0.01f, dashLen, m_lineColor);
    }

    // Lignes de bord blanches continues
    DrawCube({ cx - m_roadWidth * 0.5f + 0.15f, 0.02f, cz },
              0.12f, 0.01f, L * 2.f, m_sideColor);
    DrawCube({ cx + m_roadWidth * 0.5f - 0.15f, 0.02f, cz },
              0.12f, 0.01f, L * 2.f, m_sideColor);
}

// ── Bâtiments décoratifs répétés ──────────────────────────────────────────────
void RoadMap::drawBuildings(float cx, float cz)
{
    float spacing = 25.f;
    float W       = m_roadWidth;
    float startZ  = std::floor((cz - 150.f) / spacing) * spacing;

    for (float z = startZ; z < cz + 150.f; z += spacing) {
        // Côté gauche
        float hL = 5.f + std::fmod(std::abs(z) * 0.3f, 8.f);
        DrawCube({ cx - W * 0.5f - 6.f, hL * 0.5f, z },
                  4.f, hL, 4.f, { 55, 55, 70, 255 });
        DrawCubeWires({ cx - W * 0.5f - 6.f, hL * 0.5f, z },
                       4.f, hL, 4.f, {80, 80, 100, 255});

        // Côté droit
        float hR = 4.f + std::fmod(std::abs(z + 12.f) * 0.4f, 10.f);
        DrawCube({ cx + W * 0.5f + 6.f, hR * 0.5f, z },
                  4.f, hR, 4.f, { 50, 60, 65, 255 });
        DrawCubeWires({ cx + W * 0.5f + 6.f, hR * 0.5f, z },
                       4.f, hR, 4.f, {80, 100, 100, 255});

        // Fenêtres (petits cubes lumineux)
        for (int row = 0; row < (int)(hL / 1.8f); row++) {
            for (int col = -1; col <= 1; col++) {
                bool lit = ((int)(z + row + col) % 3) != 0;
                if (!lit) continue;
                DrawCube({ cx - W * 0.5f - 5.f + col * 1.2f,
                            1.0f + row * 1.8f, z + 0.5f },
                           0.5f, 0.6f, 0.05f,
                           { 255, 220, 120, 200 });
            }
        }
    }
}

// ── Skybox simple ─────────────────────────────────────────────────────────────
void RoadMap::drawSkybox()
{
    // Fond ciel nocturne (grand cube inversé)
    // Raylib efface le fond avec ClearBackground donc pas besoin de sphère,
    // on dessine juste quelques étoiles statiques
    for (int i = 0; i < 80; i++) {
        float x = ((i * 137) % 200) - 100.f;
        float y = 20.f + (i * 73) % 40;
        float z = ((i * 211) % 200) - 100.f;
        DrawSphere({ x, y, z }, 0.08f, WHITE);
    }
}