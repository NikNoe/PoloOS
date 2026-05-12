/**
 * @file RoadMap.cpp
 * @brief Implementation of the legacy infinite road scene.
 */

#include "RoadMap.h"
#include <cmath>

RoadMap::RoadMap() {}

void RoadMap::draw(float carX, float carZ)
{
    drawSkybox();
    drawRoad(carX, carZ);
    drawMarkings(carX, carZ);
    drawBuildings(carX, carZ);
}

void RoadMap::drawRoad(float cx, float cz)
{
    float L = m_roadLength;
    float W = m_roadWidth;

    // Wide grass ground plane
    DrawPlane({ cx, 0.f, cz }, { L * 2.f, L * 2.f }, m_grassColor);

    // Road carriageway
    DrawCube({ cx, 0.01f, cz }, W, 0.02f, L * 2.f, m_roadColor);

    // Raised sidewalk kerbs
    DrawCube({ cx - W * 0.5f - 0.5f, 0.05f, cz }, 0.8f, 0.1f, L * 2.f, {80, 80, 85, 255});
    DrawCube({ cx + W * 0.5f + 0.5f, 0.05f, cz }, 0.8f, 0.1f, L * 2.f, {80, 80, 85, 255});
}

void RoadMap::drawMarkings(float cx, float cz)
{
    float L = m_roadLength;

    // Dashed yellow centre line scrolling with the car
    float dashLen  = 3.0f;
    float dashGap  = 3.0f;
    float step     = dashLen + dashGap;
    float startZ   = std::floor((cz - L) / step) * step;

    for (float z = startZ; z < cz + L; z += step) {
        DrawCube({ cx, 0.02f, z }, 0.12f, 0.01f, dashLen, m_lineColor);
    }

    // Solid white edge lines
    DrawCube({ cx - m_roadWidth * 0.5f + 0.15f, 0.02f, cz },
              0.12f, 0.01f, L * 2.f, m_sideColor);
    DrawCube({ cx + m_roadWidth * 0.5f - 0.15f, 0.02f, cz },
              0.12f, 0.01f, L * 2.f, m_sideColor);
}

void RoadMap::drawBuildings(float cx, float cz)
{
    float spacing = 25.f;
    float W       = m_roadWidth;
    float startZ  = std::floor((cz - 150.f) / spacing) * spacing;

    for (float z = startZ; z < cz + 150.f; z += spacing) {
        // Left side
        float hL = 5.f + std::fmod(std::abs(z) * 0.3f, 8.f);
        DrawCube({ cx - W * 0.5f - 6.f, hL * 0.5f, z },
                  4.f, hL, 4.f, { 55, 55, 70, 255 });
        DrawCubeWires({ cx - W * 0.5f - 6.f, hL * 0.5f, z },
                       4.f, hL, 4.f, {80, 80, 100, 255});

        // Right side
        float hR = 4.f + std::fmod(std::abs(z + 12.f) * 0.4f, 10.f);
        DrawCube({ cx + W * 0.5f + 6.f, hR * 0.5f, z },
                  4.f, hR, 4.f, { 50, 60, 65, 255 });
        DrawCubeWires({ cx + W * 0.5f + 6.f, hR * 0.5f, z },
                       4.f, hR, 4.f, {80, 100, 100, 255});

        // Lit windows on the left building
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

void RoadMap::drawSkybox()
{
    // ClearBackground handles the sky; draw static star points here
    for (int i = 0; i < 80; i++) {
        float x = ((i * 137) % 200) - 100.f;
        float y = 20.f + (i * 73) % 40;
        float z = ((i * 211) % 200) - 100.f;
        DrawSphere({ x, y, z }, 0.08f, WHITE);
    }
}
