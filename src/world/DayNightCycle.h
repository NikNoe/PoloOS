#pragma once
#include "raylib.h"

// ─── DayNightCycle.h ──────────────────────────────────────────────────────────
// Gère le cycle jour/nuit : heure, lumière ambiante, couleur ciel, soleil/lune.
// Compatible future intégration caméra IA (expose timeOfDay pour les agents).
// ─────────────────────────────────────────────────────────────────────────────

enum class DayPhase { DAWN, DAY, DUSK, NIGHT };

class DayNightCycle {
public:
    DayNightCycle();

    void  update(float dt);
    void  drawSky();          // fond + étoiles + soleil/lune
    void  applyLighting();    // lumière ambiante scène

    // ── Accesseurs pour les autres systèmes ──────────────────────────────────
    float      timeOfDay()   const { return m_timeOfDay; }   // 0.0–24.0h
    DayPhase   phase()       const { return m_phase; }
    Color      ambientColor()const { return m_ambient; }
    Color      skyColor()    const { return m_skyColor; }
    bool       isNight()     const { return m_phase == DayPhase::NIGHT; }
    float      sunAngle()    const { return m_sunAngle; }    // degrés

    // ── Contrôle vitesse simulation ───────────────────────────────────────────
    void  setTimeScale(float scale) { m_timeScale = scale; }
    void  setTimeOfDay(float hour)  { m_timeOfDay = hour; }

    // ── Interface future caméra IA ────────────────────────────────────────────
    // Retourne les conditions de visibilité estimées (0.0=nuit, 1.0=plein jour)
    float visibility() const { return m_visibility; }

private:
    float     m_timeOfDay  = 8.f;   // heure actuelle (0–24)
    float     m_timeScale  = 60.f;  // 1 sec réelle = 60 sec simulées
    float     m_sunAngle   = 0.f;   // position soleil en degrés
    float     m_visibility = 1.f;   // visibilité 0–1

    DayPhase  m_phase      = DayPhase::DAY;
    Color     m_ambient    = WHITE;
    Color     m_skyColor   = { 135, 206, 235, 255 };
    Color     m_sunColor   = WHITE;

    void  updatePhase();
    void  updateColors();
    void  drawStars();
    void  drawSun();
    void  drawMoon();

    // Interpolation linéaire couleur
    Color lerpColor(Color a, Color b, float t);
};