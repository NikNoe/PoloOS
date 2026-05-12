/**
 * @file DebugPanel.cpp
 * @brief Implementation of the debug overlay panel and speedometer.
 */

#include "DebugPanel.h"
#include "raymath.h"
#include <cstdio>
#include <cmath>

// Panel colour constants
static const Color BG       = {  15,  15,  25, 210 };
static const Color BORDER   = {   0, 200, 255,  80 };
static const Color ACCENT   = {   0, 200, 255, 255 };
static const Color BTN_ON   = {   0, 180,  80, 255 };
static const Color BTN_OFF  = {  60,  60,  70, 255 };
static const Color TEXT_COL = { 200, 200, 200, 255 };
static const Color HEAD_COL = {   0, 220, 255, 255 };
static const int   FONT     = 14;
static const int   LH       = 22;  // line height

DebugPanel::DebugPanel() {}

void DebugPanel::update(PoloCar& car, DayNightCycle& day)
{
    m_carRef = &car;
    m_dayRef = &day;

    // Toggle panel visibility
    if (IsKeyPressed(KEY_F1)) m_visible = !m_visible;
    if (!m_visible) return;

    Vector2 mouse = GetMousePosition();
    bool    click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    int px = (int)m_panelX;
    int pw = (int)m_panelW;

    // ── Quick time preset buttons ─────────────────────────────────────────────
    if (click) {
        if (CheckCollisionPointRec(mouse, { m_panelX+10, 90, 55, 20 }))
            day.setTimeOfDay(6.f);   // Dawn
        if (CheckCollisionPointRec(mouse, { m_panelX+70, 90, 55, 20 }))
            day.setTimeOfDay(12.f);  // Day
        if (CheckCollisionPointRec(mouse, { m_panelX+130, 90, 55, 20 }))
            day.setTimeOfDay(19.f);  // Dusk
        if (CheckCollisionPointRec(mouse, { m_panelX+190, 90, 55, 20 }))
            day.setTimeOfDay(0.f);   // Night

        // Headlights
        if (CheckCollisionPointRec(mouse, { m_panelX+10, 180, 110, 22 }))
            car.lowBeam = !car.lowBeam;
        if (CheckCollisionPointRec(mouse, { m_panelX+130, 180, 110, 22 }))
            car.highBeam = !car.highBeam;

        // Turn signals
        if (CheckCollisionPointRec(mouse, { m_panelX+10, 206, 110, 22 }))
            car.leftBlinker = !car.leftBlinker;
        if (CheckCollisionPointRec(mouse, { m_panelX+130, 206, 110, 22 }))
            car.rightBlinker = !car.rightBlinker;
        if (CheckCollisionPointRec(mouse, { m_panelX+10, 232, 240, 22 }))
            car.hazard = !car.hazard;

        // Doors
        if (CheckCollisionPointRec(mouse, { m_panelX+10, 290, 110, 22 }))
            car.doorFL = !car.doorFL;
        if (CheckCollisionPointRec(mouse, { m_panelX+130, 290, 110, 22 }))
            car.doorFR = !car.doorFR;
        if (CheckCollisionPointRec(mouse, { m_panelX+10, 316, 110, 22 }))
            car.doorRL = !car.doorRL;
        if (CheckCollisionPointRec(mouse, { m_panelX+130, 316, 110, 22 }))
            car.doorRR = !car.doorRR;
        if (CheckCollisionPointRec(mouse, { m_panelX+10, 342, 110, 22 }))
            car.trunk = !car.trunk;
        if (CheckCollisionPointRec(mouse, { m_panelX+130, 342, 110, 22 }))
            car.hood = !car.hood;
    }

    // ── Time-of-day slider ────────────────────────────────────────────────────
    Rectangle sliderArea = { m_panelX+10, 118, m_panelW-20, 16 };
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(mouse, sliderArea)) {
        float t = (mouse.x - sliderArea.x) / sliderArea.width;
        day.setTimeOfDay(Clamp(t * 24.f, 0.f, 24.f));
    }

    // ── Simulation speed override ─────────────────────────────────────────────
    if (IsKeyDown(KEY_N)) day.setTimeScale(600.f);
    else                  day.setTimeScale(60.f);
}

void DebugPanel::draw(const PoloCar& car, const DayNightCycle& day, int sw, int sh)
{
    // Speedometer is always visible regardless of panel state
    drawSpeedometer(car, sw, sh);

    // Shortcut hint
    DrawText("F1 — Debug Panel", sw - 180, sh - 24, 13, { 120,120,120,180 });

    if (!m_visible) return;

    int px = (int)m_panelX;
    int py = (int)m_panelY;
    int pw = (int)m_panelW;

    // ── Panel background ──────────────────────────────────────────────────────
    DrawRectangle(px, py, pw, 400, BG);
    DrawRectangleLines(px, py, pw, 400, BORDER);

    // ── Header ───────────────────────────────────────────────────────────────
    DrawRectangle(px, py, pw, 26, { 0, 180, 230, 60 });
    DrawText("PoloOS — Debug Panel", px+8, py+6, FONT, HEAD_COL);
    DrawText("[F1]", px+pw-36, py+6, FONT, { 100,100,100,255 });

    // ── Day / night section ───────────────────────────────────────────────────
    int y = py + 36;
    DrawText("DAY / NIGHT", px+8, y, FONT, ACCENT);
    y += 18;

    // Current time display
    int   hh  = (int)day.timeOfDay();
    int   mm  = (int)((day.timeOfDay() - hh) * 60.f);
    float vis = day.visibility();
    char  buf[64];
    std::snprintf(buf, sizeof(buf), "%02d:%02d  vis:%.0f%%", hh, mm, vis*100.f);
    DrawText(buf, px+8, y, FONT, TEXT_COL);
    y += 18;

    // Quick-time preset buttons
    auto qbtn = [&](const char* label, float bx, float tod) {
        bool hover = CheckCollisionPointRec(GetMousePosition(), {bx, (float)y, 55, 20});
        DrawRectangle((int)bx, y, 55, 20, hover ? ACCENT : BTN_OFF);
        DrawText(label, (int)bx+4, y+3, 12, WHITE);
    };
    qbtn("Dawn", px+10,   6.f);
    qbtn("Day",  px+70,  12.f);
    qbtn("Dusk", px+130, 19.f);
    qbtn("Night",px+190,  0.f);
    y += 28;

    // Time-of-day progress slider
    float sliderW = pw - 20;
    float ratio   = day.timeOfDay() / 24.f;
    DrawRectangle(px+10, y, (int)sliderW, 16, { 40,40,60,255 });
    DrawRectangle(px+10, y, (int)(sliderW * ratio), 16, ACCENT);
    DrawText("0h",  px+10, y+18, 11, TEXT_COL);
    DrawText("12h", px+10+(int)(sliderW/2)-8, y+18, 11, TEXT_COL);
    DrawText("24h", px+10+(int)sliderW-18, y+18, 11, TEXT_COL);
    y += 38;

    // ── Lighting section ──────────────────────────────────────────────────────
    DrawText("LIGHTING", px+8, y, FONT, ACCENT);
    y += 18;

    auto toggleBtn = [&](const char* label, bool state, float bx, float by) {
        bool hover = CheckCollisionPointRec(GetMousePosition(), {bx, by, 110, 22});
        Color c = state ? BTN_ON : BTN_OFF;
        if (hover) c.a = 200;
        DrawRectangle((int)bx, (int)by, 110, 22, c);
        DrawRectangleLines((int)bx, (int)by, 110, 22, state ? BTN_ON : BORDER);
        DrawText(label, (int)bx+6, (int)by+4, 12, WHITE);
    };

    toggleBtn(car.lowBeam  ? "Low beam  ON" : "Low beam  --",  car.lowBeam,  px+10,  y);
    toggleBtn(car.highBeam ? "High beam ON" : "High beam --",  car.highBeam, px+130, y);
    y += 26;
    toggleBtn(car.leftBlinker  ? "Left sig. ON" : "Left sig. --", car.leftBlinker,  px+10,  y);
    toggleBtn(car.rightBlinker ? "Right sig ON" : "Right sig --", car.rightBlinker, px+130, y);
    y += 26;

    bool hover_haz = CheckCollisionPointRec(GetMousePosition(), {(float)px+10, (float)y, 240, 22});
    DrawRectangle(px+10, y, 240, 22, car.hazard ? Color{200,120,0,255} : BTN_OFF);
    DrawText(car.hazard ? "HAZARD LIGHTS  ON" : "HAZARD LIGHTS  --", px+18, y+4, 12, WHITE);
    y += 34;

    // ── Doors section ─────────────────────────────────────────────────────────
    DrawText("DOORS / BOOT", px+8, y, FONT, ACCENT);
    y += 18;

    toggleBtn(car.doorFL ? "Door FL  OPEN" : "Door FL  --", car.doorFL, px+10,  y);
    toggleBtn(car.doorFR ? "Door FR  OPEN" : "Door FR  --", car.doorFR, px+130, y);
    y += 26;
    toggleBtn(car.doorRL ? "Door RL  OPEN" : "Door RL  --", car.doorRL, px+10,  y);
    toggleBtn(car.doorRR ? "Door RR  OPEN" : "Door RR  --", car.doorRR, px+130, y);
    y += 26;
    toggleBtn(car.trunk ? "Boot  OPEN" : "Boot  --", car.trunk, px+10,  y);
    toggleBtn(car.hood  ? "Hood  OPEN" : "Hood  --", car.hood,  px+130, y);

    // ── Footer hint ───────────────────────────────────────────────────────────
    DrawText("N = speed up time", px+8, py+385, 11, {80,80,80,255});
}

void DebugPanel::drawSpeedometer(const PoloCar& car, int sw, int sh)
{
    int cx = sw - 90, cy = sh - 90, r = 70;
    DrawCircle(cx, cy, r, { 0, 0, 0, 160 });
    DrawCircleLines(cx, cy, r, ACCENT);

    float ratio = std::abs(car.speed) / 160.f;
    DrawCircleSector({ (float)cx, (float)cy }, r-8,
                     140.f, 140.f + 260.f*ratio, 40,
                     car.speed < 0 ? ORANGE : ACCENT);

    char buf[16];
    std::snprintf(buf, sizeof(buf), "%d", (int)std::abs(car.speed));
    int tw = MeasureText(buf, 28);
    DrawText(buf, cx - tw/2, cy-14, 28, WHITE);
    DrawText("km/h", cx - MeasureText("km/h",12)/2, cy+16, 12, { 150,150,150,255 });
}
