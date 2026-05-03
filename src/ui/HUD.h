#pragma once
#include "raylib.h"
#include "../car/PoloCar.h"

// ─── HUD.h ────────────────────────────────────────────────────────────────────

class HUD {
public:
    void draw(const PoloCar& car, int screenW, int screenH);

private:
    void drawSpeedometer (const PoloCar& car, int sw, int sh);
    void drawCarState    (const PoloCar& car, int sw, int sh);
    void drawControls    (int sw, int sh);
    void drawBlinkerBar  (const PoloCar& car, int sw, int sh);
};