#pragma once

/**
 * @file DebugPanel.h
 * @brief On-screen debug overlay toggled with F1.
 *
 * Replaces the HUD during development. Exposes controls for the day/night
 * cycle, headlights, turn signals and door/boot/hood states. Can be disabled
 * cleanly for production builds.
 */

#include "raylib.h"
#include "../car/PoloCar.h"
#include "../world/DayNightCycle.h"

/**
 * @brief Immediate-mode debug overlay panel rendered over the 3D scene.
 *
 * The speedometer is always visible. The full panel (lights, doors, time slider)
 * is toggled with F1. All interactive controls modify the car and day/night state
 * directly via the references stored during update().
 */
class DebugPanel {
public:
    /** @brief Constructs the panel in the visible state. */
    DebugPanel();

    /**
     * @brief Processes input and updates car/day state accordingly.
     *
     * Handles F1 panel toggle, quick-time buttons, the time-of-day slider,
     * headlight toggles, blinker toggles and door/boot/hood toggles.
     *
     * @param car Reference to the player car state (modified directly).
     * @param day Reference to the day/night cycle (modified directly).
     */
    void update(PoloCar& car, DayNightCycle& day);

    /**
     * @brief Draws the overlay panel and speedometer for the current frame.
     * @param car Current car state (read-only).
     * @param day Current day/night state (read-only).
     * @param sw  Screen width in pixels.
     * @param sh  Screen height in pixels.
     */
    void draw(const PoloCar& car, const DayNightCycle& day, int sw, int sh);

    /**
     * @brief Returns true if the debug panel is currently visible.
     * @return True when the panel overlay is shown.
     */
    bool isVisible() const { return m_visible; }

private:
    bool  m_visible   = true;  ///< Panel visibility state.
    float m_panelX    = 20.f;  ///< Panel left edge X (pixels).
    float m_panelY    = 20.f;  ///< Panel top edge Y (pixels).
    float m_panelW    = 260.f; ///< Panel width (pixels).

    // ── Section draw helpers ──────────────────────────────────────────────────

    /**
     * @brief Draws the panel title bar.
     * @param y Vertical cursor position, advanced by the section height.
     */
    void drawHeader(int& y);

    /**
     * @brief Draws the day/night section: time display, quick buttons and slider.
     * @param day Day/night state to display.
     * @param y   Vertical cursor, advanced in place.
     */
    void drawTimeSection(const DayNightCycle& day, int& y);

    /**
     * @brief Draws the car telemetry section: position, speed, heading.
     * @param car Car state to display.
     * @param y   Vertical cursor, advanced in place.
     */
    void drawCarSection(const PoloCar& car, int& y);

    /**
     * @brief Draws the lighting toggle section: headlights and turn signals.
     * @param car Car state to display.
     * @param y   Vertical cursor, advanced in place.
     */
    void drawLightSection(const PoloCar& car, int& y);

    /**
     * @brief Draws the door/boot/hood toggle section.
     * @param car Car state to display.
     * @param y   Vertical cursor, advanced in place.
     */
    void drawDoorSection(const PoloCar& car, int& y);

    /**
     * @brief Draws the circular analogue speedometer in the bottom-right corner.
     * @param car Car state (speed used for the needle).
     * @param sw  Screen width in pixels.
     * @param sh  Screen height in pixels.
     */
    void drawSpeedometer(const PoloCar& car, int sw, int sh);

    // ── Widget helpers ────────────────────────────────────────────────────────

    /**
     * @brief Draws a clickable button and returns true on click.
     * @param label Button text.
     * @param x, y  Top-left position (pixels).
     * @param w, h  Dimensions (pixels).
     * @param col   Background colour.
     * @return True if the left mouse button was pressed inside the button.
     */
    bool button(const char* label, int x, int y, int w, int h, Color col);

    /**
     * @brief Draws a labelled boolean state indicator.
     * @param label Text label.
     * @param state Current boolean value (green = true, grey = false).
     * @param x, y  Position (pixels).
     */
    void toggle(const char* label, bool state, int x, int y);

    /**
     * @brief Draws a horizontal progress-bar style slider.
     * @param label Text label.
     * @param val   Current value.
     * @param min   Minimum value.
     * @param max   Maximum value.
     * @param x, y  Position (pixels).
     * @param w     Width (pixels).
     */
    void slider(const char* label, float val, float min, float max, int x, int y, int w);

    /**
     * @brief Draws a two-column key/value text row.
     * @param label Left column text.
     * @param value Right column text.
     * @param x, y  Position (pixels).
     */
    void infoRow(const char* label, const char* value, int x, int y);

    bool           m_draggingTime = false; ///< True while the time slider is being dragged.
    DayNightCycle* m_dayRef       = nullptr; ///< Non-owning pointer set each update().
    PoloCar*       m_carRef       = nullptr; ///< Non-owning pointer set each update().
};
