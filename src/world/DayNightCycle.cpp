/**
 * @file DayNightCycle.cpp
 * @brief Implementation of the 24-hour day/night cycle simulation.
 */

#include "DayNightCycle.h"
#include "raymath.h"
#include <cmath>

DayNightCycle::DayNightCycle() {
    updatePhase();
    updateColors();
}

void DayNightCycle::update(float dt) {
    m_timeOfDay += dt * m_timeScale / 3600.f;
    if (m_timeOfDay >= 24.f) m_timeOfDay -= 24.f;

    // Sun angle: 0h = -90 deg, 6h = 0 deg, 12h = 90 deg, 18h = 180 deg, 24h = 270 deg
    m_sunAngle = (m_timeOfDay / 24.f) * 360.f - 90.f;

    updatePhase();
    updateColors();
}

void DayNightCycle::updatePhase() {
    if      (m_timeOfDay >= 5.f  && m_timeOfDay < 7.f)  m_phase = DayPhase::DAWN;
    else if (m_timeOfDay >= 7.f  && m_timeOfDay < 19.f) m_phase = DayPhase::DAY;
    else if (m_timeOfDay >= 19.f && m_timeOfDay < 21.f) m_phase = DayPhase::DUSK;
    else                                                  m_phase = DayPhase::NIGHT;
}

void DayNightCycle::updateColors() {
    // Key colours for each phase
    Color nightSky  = {  8,  10,  25, 255 };
    Color dawnSky   = { 180, 100,  60, 255 };  // warm orange, not pink
    Color daySky    = {  80, 140, 210, 255 };  // natural blue sky
    Color duskSky   = { 160,  60,  30, 255 };  // deep red

    Color nightAmb  = {  15,  15,  35, 255 };
    Color dawnAmb   = { 160, 100,  60, 255 };
    Color dayAmb    = { 220, 210, 190, 255 };  // warm natural light
    Color duskAmb   = { 160,  60,  25, 255 };

    float t = 0.f;

    if (m_phase == DayPhase::NIGHT) {
        float span = m_timeOfDay < 5.f ? m_timeOfDay + 3.f : m_timeOfDay - 21.f;
        t = Clamp(span / 3.f, 0.f, 1.f);
        m_skyColor   = nightSky;
        m_ambient    = nightAmb;
        m_visibility = 0.15f;
    }
    else if (m_phase == DayPhase::DAWN) {
        t = (m_timeOfDay - 5.f) / 2.f;
        m_skyColor   = lerpColor(nightSky, dawnSky, t);
        m_ambient    = lerpColor(nightAmb, dawnAmb, t);
        m_visibility = Clamp(t * 0.85f + 0.15f, 0.f, 1.f);
    }
    else if (m_phase == DayPhase::DAY) {
        // Peak at noon, slightly different at morning/evening
        float noon = std::abs(m_timeOfDay - 13.f) / 6.f;
        t = 1.f - Clamp(noon, 0.f, 1.f);
        m_skyColor   = lerpColor(dawnSky, daySky, Clamp((m_timeOfDay-7.f)/4.f,0,1));
        m_ambient    = lerpColor(dawnAmb, dayAmb, t);
        m_visibility = 1.f;
    }
    else { // DUSK
        t = (m_timeOfDay - 19.f) / 2.f;
        m_skyColor   = lerpColor(duskSky, nightSky, t);
        m_ambient    = lerpColor(duskAmb, nightAmb, t);
        m_visibility = Clamp(1.f - t * 0.85f, 0.f, 1.f);
    }
}

void DayNightCycle::drawSky() {
    // ClearBackground (called in main) handles the sky colour;
    // here we only draw the 3D sun/moon/stars objects.
    if (m_phase == DayPhase::NIGHT || m_phase == DayPhase::DAWN)
        drawStars();

    if (m_phase != DayPhase::NIGHT)
        drawSun();
    else
        drawMoon();
}

void DayNightCycle::drawStars() {
    float alpha = m_phase == DayPhase::NIGHT ? 1.f
                : (1.f - (m_timeOfDay - 5.f) / 2.f);
    unsigned char a = (unsigned char)(Clamp(alpha, 0.f, 1.f) * 255.f);

    // Static pseudo-random star distribution using golden-angle stepping
    for (int i = 0; i < 150; i++) {
        float angle = (i * 137.508f) * DEG2RAD;
        float elev  = ((i * 73) % 60 + 20) * DEG2RAD;
        float dist  = 180.f;
        Vector3 pos = {
            std::cos(elev) * std::sin(angle) * dist,
            std::sin(elev) * dist,
            std::cos(elev) * std::cos(angle) * dist
        };
        float size = (i % 3 == 0) ? 0.3f : 0.15f;
        DrawSphere(pos, size, { 255, 255, 255, a });
    }
}

void DayNightCycle::drawSun() {
    float rad = m_sunAngle * DEG2RAD;
    float dist = 150.f;
    Vector3 sunPos = {
        std::cos(rad) * dist,
        std::sin(rad) * dist,
        0.f
    };

    Color col = m_phase == DayPhase::DAWN || m_phase == DayPhase::DUSK
              ? Color{ 255, 160, 60, 255 }
              : Color{ 255, 245, 180, 255 };

    DrawSphere(sunPos, 6.f, col);
    DrawSphere(sunPos, 9.f, ColorAlpha(col, 0.15f));  // halo
}

void DayNightCycle::drawMoon() {
    float rad = (m_sunAngle + 180.f) * DEG2RAD;  // moon is opposite the sun
    float dist = 150.f;
    Vector3 moonPos = {
        std::cos(rad) * dist,
        std::sin(rad) * dist,
        0.f
    };
    DrawSphere(moonPos, 4.f, { 220, 220, 200, 255 });
    DrawSphere(moonPos, 6.f, ColorAlpha(WHITE, 0.08f));  // soft halo
}

void DayNightCycle::applyLighting() {
    // Raylib does not support dynamic lights without custom shaders.
    // Ambient atmosphere is simulated via ClearBackground colour instead.
    // Proper PBR lighting will be added in a future shader pass.
}

Color DayNightCycle::lerpColor(Color a, Color b, float t) {
    t = Clamp(t, 0.f, 1.f);
    return {
        (unsigned char)(a.r + (b.r - a.r) * t),
        (unsigned char)(a.g + (b.g - a.g) * t),
        (unsigned char)(a.b + (b.b - a.b) * t),
        255
    };
}
