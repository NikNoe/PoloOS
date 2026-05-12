#pragma once

/**
 * @file DayNightCycle.h
 * @brief Simulates the 24-hour day/night cycle: time, ambient light, sky colour, sun and moon.
 *
 * The visibility accessor is intended for future integration with the AI camera
 * pipeline so that agents can query current lighting conditions.
 */

#include "raylib.h"

/**
 * @brief Phase of the day, used for colour interpolation decisions.
 */
enum class DayPhase {
    DAWN,  ///< Sunrise transition (05:00-07:00).
    DAY,   ///< Full daylight (07:00-19:00).
    DUSK,  ///< Sunset transition (19:00-21:00).
    NIGHT  ///< Night (21:00-05:00).
};

/**
 * @brief Manages the day/night cycle simulation.
 *
 * Advances simulated time each frame, derives the current DayPhase, interpolates
 * sky and ambient colours, and draws the sun, moon and star objects in 3D.
 */
class DayNightCycle {
public:
    /** @brief Initialises the cycle and computes the initial phase and colours. */
    DayNightCycle();

    /**
     * @brief Advances simulated time and updates phase, colours and sun angle.
     * @param dt Real elapsed time since the last frame (seconds).
     */
    void  update(float dt);

    /** @brief Draws the sky background objects (stars, sun or moon) in 3D. */
    void  drawSky();

    /** @brief Applies ambient lighting to the scene (placeholder until shaders). */
    void  applyLighting();

    /**
     * @brief Returns the current simulated time of day.
     * @return Hours in [0.0, 24.0).
     */
    float      timeOfDay()    const { return m_timeOfDay; }

    /**
     * @brief Returns the current day phase.
     * @return One of DAWN, DAY, DUSK or NIGHT.
     */
    DayPhase   phase()        const { return m_phase; }

    /**
     * @brief Returns the current ambient scene colour.
     * @return Raylib Color for ambient lighting.
     */
    Color      ambientColor() const { return m_ambient; }

    /**
     * @brief Returns the current sky/background colour.
     * @return Raylib Color for ClearBackground().
     */
    Color      skyColor()     const { return m_skyColor; }

    /**
     * @brief Returns true during the NIGHT phase.
     * @return True when phase == DayPhase::NIGHT.
     */
    bool       isNight()      const { return m_phase == DayPhase::NIGHT; }

    /**
     * @brief Returns the current sun position angle.
     * @return Sun angle in degrees (0h = -90 deg, 6h = 0 deg, 12h = 90 deg).
     */
    float      sunAngle()     const { return m_sunAngle; }

    /**
     * @brief Sets the simulation time scale.
     * @param scale Seconds of simulated time per real second (default 60).
     */
    void  setTimeScale(float scale) { m_timeScale = scale; }

    /**
     * @brief Jumps to a specific time of day.
     * @param hour Target hour in [0.0, 24.0).
     */
    void  setTimeOfDay(float hour)  { m_timeOfDay = hour; }

    /**
     * @brief Returns the estimated visibility factor for the current phase.
     *
     * Used by camera AI agents to adapt detection thresholds.
     *
     * @return Visibility in [0.0 (night), 1.0 (full daylight)].
     */
    float visibility() const { return m_visibility; }

private:
    float     m_timeOfDay  = 8.f;   ///< Current simulated hour (0-24).
    float     m_timeScale  = 60.f;  ///< 1 real second = m_timeScale simulated seconds.
    float     m_sunAngle   = 0.f;   ///< Sun/moon position angle (degrees).
    float     m_visibility = 1.f;   ///< Visibility factor (0-1).

    DayPhase  m_phase      = DayPhase::DAY;              ///< Current phase.
    Color     m_ambient    = WHITE;                       ///< Ambient light colour.
    Color     m_skyColor   = { 135, 206, 235, 255 };     ///< Sky background colour.
    Color     m_sunColor   = WHITE;                       ///< Sun disc colour.

    /** @brief Determines and sets the current DayPhase from m_timeOfDay. */
    void  updatePhase();

    /** @brief Interpolates sky and ambient colours based on phase and time. */
    void  updateColors();

    /** @brief Draws static pseudo-random star points. */
    void  drawStars();

    /** @brief Draws the sun disc and halo. */
    void  drawSun();

    /** @brief Draws the moon disc and halo. */
    void  drawMoon();

    /**
     * @brief Linearly interpolates between two Raylib colours.
     * @param a Start colour.
     * @param b End colour.
     * @param t Interpolation factor (clamped to [0, 1]).
     * @return Blended colour.
     */
    Color lerpColor(Color a, Color b, float t);
};
