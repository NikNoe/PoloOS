#include "HUD.h"
#include <cmath>
#include <cstring>
#include <cstdio>

// ─── HUD.cpp ──────────────────────────────────────────────────────────────────

void HUD::draw(const PoloCar& car, int sw, int sh)
{
    drawSpeedometer(car, sw, sh);
    drawCarState   (car, sw, sh);
    drawBlinkerBar (car, sw, sh);
    drawControls   (sw, sh);
}

// ── Compteur de vitesse ───────────────────────────────────────────────────────
void HUD::drawSpeedometer(const PoloCar& car, int sw, int sh)
{
    int cx = sw - 110;
    int cy = sh - 110;
    int r  = 80;

    // Fond
    DrawCircle(cx, cy, (float)r, { 0, 0, 0, 160 });
    DrawCircleLines(cx, cy, (float)r, { 0, 242, 255, 200 });

    // Arc de progression
    float maxSpd  = 160.f;
    float ratio   = std::abs(car.speed) / maxSpd;
    float startA  = 140.f;
    float sweepA  = 260.f * ratio;
    Color arcCol  = car.speed < 0 ? ORANGE : Color{ 0, 242, 255, 255 };
    DrawCircleSector({ (float)cx, (float)cy }, (float)r - 8,
                     startA, startA + sweepA, 40, arcCol);

    // Valeur numérique
    char buf[16];
    std::snprintf(buf, sizeof(buf), "%d", (int)std::abs(car.speed));
    int tw = MeasureText(buf, 32);
    DrawText(buf, cx - tw / 2, cy - 18, 32, WHITE);
    DrawText("km/h", cx - MeasureText("km/h", 14) / 2, cy + 18, 14, GRAY);
}

// ── État de la voiture (portes, phares…) ──────────────────────────────────────
void HUD::drawCarState(const PoloCar& car, int sw, int sh)
{
    int x = 20;
    int y = sh - 220;
    int lh = 24;

    DrawRectangle(x - 8, y - 8, 220, 200, { 0, 0, 0, 140 });
    DrawRectangleLines(x - 8, y - 8, 220, 200, { 0, 242, 255, 80 });

    auto row = [&](const char* label, bool state, Color onCol) {
        DrawText(label, x, y, 18, GRAY);
        DrawText(state ? "ON" : "off", x + 160, y, 18, state ? onCol : DARKGRAY);
        y += lh;
    };

    row("Low beam",   car.lowBeam,      YELLOW);
    row("High beam",  car.highBeam,      WHITE);
    row("L blinker",  car.leftBlinker,  ORANGE);
    row("R blinker",  car.rightBlinker, ORANGE);
    row("Door FL",    car.doorFL,       RED);
    row("Door FR",    car.doorFR,       RED);
    row("Trunk",      car.trunk,        RED);
    row("Hood",       car.hood,         RED);
}

// ── Clignotants en haut ────────────────────────────────────────────────────────
void HUD::drawBlinkerBar(const PoloCar& car, int sw, int sh)
{
    int cy = 30;
    int cx = sw / 2;

    // Flèche gauche
    bool leftOn  = (car.leftBlinker || car.hazard) && car.blinkerVisible;
    bool rightOn = (car.rightBlinker || car.hazard) && car.blinkerVisible;

    Color lCol = leftOn  ? ORANGE : { 60, 40, 0, 255 };
    Color rCol = rightOn ? ORANGE : { 60, 40, 0, 255 };

    // Flèche gauche ◄
    DrawTriangle({ (float)cx - 60, (float)cy },
                  { (float)cx - 30, (float)cy - 14 },
                  { (float)cx - 30, (float)cy + 14 }, lCol);

    // Flèche droite ►
    DrawTriangle({ (float)cx + 60, (float)cy },
                  { (float)cx + 30, (float)cy - 14 },
                  { (float)cx + 30, (float)cy + 14 }, rCol);
}

// ── Aide touches ──────────────────────────────────────────────────────────────
void HUD::drawControls(int sw, int sh)
{
    const char* lines[] = {
        "↑↓  Accelerate / Brake",
        "←→  Steer",
        "1   Door FL    2  Door FR",
        "3   Door RL    4  Door RR",
        "T   Trunk      O  Hood",
        "L   Low beam   H  High beam",
        "Z   L blinker  X  R blinker",
        "W   Hazard     C  Camera mode",
    };
    int n = sizeof(lines) / sizeof(lines[0]);

    DrawRectangle(sw - 310, 10, 300, n * 20 + 16, { 0, 0, 0, 130 });
    for (int i = 0; i < n; i++)
        DrawText(lines[i], sw - 304, 18 + i * 20, 14, { 180, 180, 180, 255 });
}