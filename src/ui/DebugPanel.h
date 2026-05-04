#pragma once
#include "raylib.h"
#include "../car/PoloCar.h"
#include "../world/DayNightCycle.h"

// ─── DebugPanel.h ─────────────────────────────────────────────────────────────
// Panneau debug overlay — togglable avec F1
// Remplace HUD, désactivable facilement pour la prod
// ─────────────────────────────────────────────────────────────────────────────

class DebugPanel {
public:
    DebugPanel();

    void update(PoloCar& car, DayNightCycle& day);
    void draw  (const PoloCar& car, const DayNightCycle& day, int sw, int sh);

    bool isVisible() const { return m_visible; }

private:
    bool  m_visible   = true;
    float m_panelX    = 20.f;
    float m_panelY    = 20.f;
    float m_panelW    = 260.f;

    // ── Sections ──────────────────────────────────────────────────────────────
    void drawHeader     (int& y);
    void drawTimeSection(const DayNightCycle& day, int& y);
    void drawCarSection (const PoloCar& car, int& y);
    void drawLightSection(const PoloCar& car, int& y);
    void drawDoorSection(const PoloCar& car, int& y);
    void drawSpeedometer(const PoloCar& car, int sw, int sh);

    // ── Widgets ───────────────────────────────────────────────────────────────
    bool button  (const char* label, int x, int y, int w, int h, Color col);
    void toggle  (const char* label, bool state, int x, int y);
    void slider  (const char* label, float val, float min, float max, int x, int y, int w);
    void infoRow (const char* label, const char* value, int x, int y);

    // État interne sliders
    bool m_draggingTime = false;

    DayNightCycle* m_dayRef = nullptr;
    PoloCar*       m_carRef = nullptr;
};