#include "CarRenderer.h"
#include <cmath>

// ─── CarRenderer.cpp ──────────────────────────────────────────────────────────

#ifndef DEG2RAD
#define DEG2RAD 0.0174532925f
#endif

CarRenderer::CarRenderer() {}

// ── Utilitaire : offset local → position monde ────────────────────────────────
Vector3 CarRenderer::localToWorld(Vector3 origin, float heading,
                                   float lx, float ly, float lz)
{
    float rad = heading * DEG2RAD;
    float s   = std::sin(rad);
    float c   = std::cos(rad);
    return {
        origin.x + c * lx + s * lz,
        origin.y + ly,
        origin.z - s * lx + c * lz
    };
}

// ── Point d'entrée principal ──────────────────────────────────────────────────
void CarRenderer::draw(const PoloCar& car)
{
    Vector3 origin = { car.x, 0.f, car.z };

    drawBody  (origin, car.heading);
    drawDoors (origin, car.heading, car);
    drawTrunk (origin, car.heading, car.trunkAngle);
    drawHood  (origin, car.heading, car.hoodAngle);
    drawLights(origin, car.heading, car);

    // ── 4 roues ───────────────────────────────────────────────────────────────
    // Positions locales approx Polo 9N3 (empattement 2.46m, voie 1.48m)
    //   FL, FR : avant (+1.23 en Z local)
    //   RL, RR : arrière (-1.23 en Z local)
    //   Gauche : -0.74 X, Droite : +0.74 X
    struct WheelDef { float lx; float lz; bool isFront; bool mirrorX; };
    WheelDef wheels[4] = {
        { -0.74f,  1.23f, true,  true  },  // FL
        {  0.74f,  1.23f, true,  false },  // FR
        { -0.74f, -1.23f, false, true  },  // RL
        {  0.74f, -1.23f, false, false },  // RR
    };

    for (auto& w : wheels) {
        Vector3 wpos = localToWorld(origin, car.heading, w.lx, 0.3f, w.lz);
        float steer  = w.isFront ? car.wheelAngle : 0.f;
        drawWheel(wpos, car.heading + steer, car.wheelRoll, w.mirrorX);
    }
}

// ── Carrosserie principale ─────────────────────────────────────────────────────
void CarRenderer::drawBody(Vector3 origin, float heading)
{
    // Bas de caisse
    Vector3 base = localToWorld(origin, heading, 0, 0.25f, 0);
    DrawModelEx(
        LoadModelFromMesh(GenMeshBox(1.72f, 0.5f, 4.2f)),
        base, {0,1,0}, heading, {1,1,1}, m_bodyColor
    );

    // Toit (profil hatchback)
    Vector3 roof = localToWorld(origin, heading, 0, 0.85f, -0.15f);
    DrawModelEx(
        LoadModelFromMesh(GenMeshBox(1.60f, 0.55f, 2.4f)),
        roof, {0,1,0}, heading, {1,1,1}, m_bodyColor
    );

    // Pare-brise avant (légèrement incliné — simplifié en boîte plate)
    Vector3 windshield = localToWorld(origin, heading, 0, 0.72f, 0.95f);
    DrawModelEx(
        LoadModelFromMesh(GenMeshBox(1.55f, 0.05f, 0.9f)),
        windshield, {0,1,0}, heading, {1,1,1}, m_glassColor
    );

    // Lunette arrière
    Vector3 rear = localToWorld(origin, heading, 0, 0.72f, -1.05f);
    DrawModelEx(
        LoadModelFromMesh(GenMeshBox(1.45f, 0.05f, 0.7f)),
        rear, {0,1,0}, heading, {1,1,1}, m_glassColor
    );

    // Vitres latérales gauche / droite
    for (int side = -1; side <= 1; side += 2) {
        Vector3 win = localToWorld(origin, heading, side * 0.86f, 0.85f, -0.1f);
        DrawModelEx(
            LoadModelFromMesh(GenMeshBox(0.05f, 0.42f, 1.9f)),
            win, {0,1,0}, heading, {1,1,1}, m_glassColor
        );
    }

    // Pare-chocs avant
    Vector3 bumpF = localToWorld(origin, heading, 0, 0.2f, 2.2f);
    DrawModelEx(
        LoadModelFromMesh(GenMeshBox(1.72f, 0.35f, 0.2f)),
        bumpF, {0,1,0}, heading, {1,1,1}, {50,50,50,255}
    );

    // Pare-chocs arrière
    Vector3 bumpR = localToWorld(origin, heading, 0, 0.2f, -2.2f);
    DrawModelEx(
        LoadModelFromMesh(GenMeshBox(1.72f, 0.35f, 0.2f)),
        bumpR, {0,1,0}, heading, {1,1,1}, {50,50,50,255}
    );
}

// ── Portes animées ────────────────────────────────────────────────────────────
void CarRenderer::drawDoors(Vector3 origin, float heading, const PoloCar& car)
{
    struct DoorDef {
        float lx;   // offset latéral
        float lz;   // offset longitudinal (centre de la porte)
        float angle;// angle d'ouverture actuel
        int   side; // -1 gauche, +1 droite
    };

    DoorDef doors[4] = {
        { -0.86f,  0.8f,  car.doorFLAngle, -1 },  // FL
        {  0.86f,  0.8f,  car.doorFRAngle,  1 },  // FR
        { -0.86f, -0.6f,  car.doorRLAngle, -1 },  // RL
        {  0.86f, -0.6f,  car.doorRRAngle,  1 },  // RR
    };

    for (auto& d : doors) {
        // Pivot = extrémité avant de la porte
        float pivotZ = d.lz + d.side * 0.0f + 0.6f; // avant de la porte
        float openRad = d.angle * DEG2RAD * d.side;

        // Centre de la porte = pivot + offset selon angle d'ouverture
        float dx = std::sin(openRad) * 0.6f;
        float dz = -(std::cos(openRad) - 1.f) * 0.6f;

        Vector3 doorCenter = localToWorld(origin, heading,
            d.lx + dx * d.side,
            0.5f,
            d.lz + dz
        );

        DrawModelEx(
            LoadModelFromMesh(GenMeshBox(0.08f, 0.8f, 1.1f)),
            doorCenter,
            {0, 1, 0},
            heading + d.angle * d.side,
            {1, 1, 1},
            m_bodyColor
        );
    }
}

// ── Coffre animé ──────────────────────────────────────────────────────────────
void CarRenderer::drawTrunk(Vector3 origin, float heading, float angle)
{
    // Pivot en bas du coffre (arrière du toit)
    float rad    = angle * DEG2RAD;
    float cy     = 1.1f + std::sin(rad) * 0.35f;
    float cz     = -1.55f - std::cos(rad) * 0.35f + 0.35f;

    Vector3 trunkPos = localToWorld(origin, heading, 0, cy, cz);
    DrawModelEx(
        LoadModelFromMesh(GenMeshBox(1.55f, 0.06f, 0.75f)),
        trunkPos,
        {0, 1, 0},
        heading,
        {1, 1, 1},
        m_bodyColor
    );
}

// ── Capot animé ───────────────────────────────────────────────────────────────
void CarRenderer::drawHood(Vector3 origin, float heading, float angle)
{
    float rad = angle * DEG2RAD;
    float cy  = 0.52f + std::sin(rad) * 0.4f;
    float cz  = 1.4f  + std::cos(rad) * 0.4f - 0.4f;

    Vector3 hoodPos = localToWorld(origin, heading, 0, cy, cz);
    DrawModelEx(
        LoadModelFromMesh(GenMeshBox(1.65f, 0.06f, 0.85f)),
        hoodPos,
        {0, 1, 0},
        heading,
        {1, 1, 1},
        m_bodyColor
    );
}

// ── Roue complète (pneu + jante) ──────────────────────────────────────────────
void CarRenderer::drawWheel(Vector3 pos, float steerHeading, float roll, bool mirrorX)
{
    // Pneu (cylindre)
    DrawModelEx(
        LoadModelFromMesh(GenMeshCylinder(0.295f, 0.19f, 16)),
        pos,
        {0, 0, 1},          // axe de rotation = Z
        steerHeading,
        {1, 1, 1},
        m_wheelColor
    );

    // Jante (cylindre plus fin, plus clair)
    Vector3 rimPos = pos;
    rimPos.y = pos.y;
    DrawModelEx(
        LoadModelFromMesh(GenMeshCylinder(0.22f, 0.21f, 8)),
        rimPos,
        {0, 0, 1},
        steerHeading,
        {1, 1, 1},
        m_rimColor
    );
}

// ── Phares et feux ────────────────────────────────────────────────────────────
void CarRenderer::drawLights(Vector3 origin, float heading, const PoloCar& car)
{
    // Phares avant gauche / droite
    for (int side = -1; side <= 1; side += 2) {
        Color col = car.highBeam  ? m_lightOnHigh
                  : car.lowBeam   ? m_lightOnLow
                  : m_lightOff;

        Vector3 lpos = localToWorld(origin, heading, side * 0.65f, 0.45f, 2.12f);
        DrawModelEx(
            LoadModelFromMesh(GenMeshBox(0.28f, 0.15f, 0.06f)),
            lpos, {0,1,0}, heading, {1,1,1}, col
        );

        // Halo phare allumé
        if (car.lowBeam || car.highBeam) {
            DrawSphere(lpos, 0.18f, ColorAlpha(col, 0.25f));
        }
    }

    // Feux arrière + stop
    bool isbraking = (car.speed > 1.f && car.handbrake);
    Color stopCol = isbraking ? m_brakeLight : Color{100, 10, 10, 255};

    for (int side = -1; side <= 1; side += 2) {
        Vector3 lpos = localToWorld(origin, heading, side * 0.65f, 0.45f, -2.12f);
        DrawModelEx(
            LoadModelFromMesh(GenMeshBox(0.32f, 0.15f, 0.06f)),
            lpos, {0,1,0}, heading, {1,1,1}, stopCol
        );
    }

    // Clignotants avant
    auto blinkerColor = [&](bool isLeft) -> Color {
        bool active = isLeft ? (car.leftBlinker || car.hazard)
                             : (car.rightBlinker || car.hazard);
        return (active && car.blinkerVisible) ? m_blinkerOn : m_blinkerOff;
    };

    Vector3 blFL = localToWorld(origin, heading, -0.72f, 0.4f,  2.1f);
    Vector3 blFR = localToWorld(origin, heading,  0.72f, 0.4f,  2.1f);
    Vector3 blRL = localToWorld(origin, heading, -0.72f, 0.4f, -2.1f);
    Vector3 blRR = localToWorld(origin, heading,  0.72f, 0.4f, -2.1f);

    DrawModelEx(LoadModelFromMesh(GenMeshBox(0.16f,0.12f,0.06f)),
        blFL, {0,1,0}, heading, {1,1,1}, blinkerColor(true));
    DrawModelEx(LoadModelFromMesh(GenMeshBox(0.16f,0.12f,0.06f)),
        blFR, {0,1,0}, heading, {1,1,1}, blinkerColor(false));
    DrawModelEx(LoadModelFromMesh(GenMeshBox(0.16f,0.12f,0.06f)),
        blRL, {0,1,0}, heading, {1,1,1}, blinkerColor(true));
    DrawModelEx(LoadModelFromMesh(GenMeshBox(0.16f,0.12f,0.06f)),
        blRR, {0,1,0}, heading, {1,1,1}, blinkerColor(false));
}