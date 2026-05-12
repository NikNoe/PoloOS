#pragma once

/**
 * @file PoloCar.h
 * @brief Pure car state: no Raylib, no Qt dependencies.
 *
 * This struct can be reused directly in the future PoloOS Qt module.
 */

/**
 * @brief Represents the complete state of a simulated Volkswagen Polo.
 *
 * Holds position, driving dynamics, animated part angles (doors, trunk, hood)
 * and lighting states. No dependency on Raylib or Qt — pure transferable state.
 */
struct PoloCar {

    // ── Position & motion ─────────────────────────────────────────────────────

    float x        = 0.f;      ///< World position X (metres).
    float z        = 0.f;      ///< World position Z (metres).
    float heading  = 0.f;      ///< Heading in degrees (0 = North).
    float speed    = 0.f;      ///< Speed in km/h (negative = reverse).

    float steeringAngle = 0.f; ///< Steering wheel angle: -450 to +450 degrees.
    float wheelAngle    = 0.f; ///< Front wheel angle: -35 to +35 degrees (computed).

    // ── Animations (smooth, 0.0 = closed → target angle = open) ─────────────

    float doorFLAngle = 0.f;   ///< Front-left door angle (degrees, 0–65).
    float doorFRAngle = 0.f;   ///< Front-right door angle (degrees, 0–65).
    float doorRLAngle = 0.f;   ///< Rear-left door angle (degrees, 0–55).
    float doorRRAngle = 0.f;   ///< Rear-right door angle (degrees, 0–55).
    float trunkAngle  = 0.f;   ///< Boot/trunk angle (degrees, 0–70).
    float hoodAngle   = 0.f;   ///< Hood/bonnet angle (degrees, 0–60).
    float wheelRoll   = 0.f;   ///< Cumulative wheel rotation (degrees).

    // ── Boolean states ────────────────────────────────────────────────────────

    bool doorFL = false; ///< Front-left door open.
    bool doorFR = false; ///< Front-right door open.
    bool doorRL = false; ///< Rear-left door open.
    bool doorRR = false; ///< Rear-right door open.
    bool trunk  = false; ///< Boot open.
    bool hood   = false; ///< Hood open.

    bool lowBeam      = false; ///< Dipped headlights on.
    bool highBeam     = false; ///< Full-beam headlights on.
    bool leftBlinker  = false; ///< Left turn signal active.
    bool rightBlinker = false; ///< Right turn signal active.
    bool hazard       = false; ///< Hazard warning lights active.

    bool handbrake = true; ///< Handbrake engaged.

    // ── Blinker timer (internal) ──────────────────────────────────────────────

    float blinkerTimer   = 0.f;  ///< Time accumulator for blink cycle (seconds).
    bool  blinkerVisible = true; ///< Current blinker display state.

    // ── Methods ───────────────────────────────────────────────────────────────

    /**
     * @brief Updates physics, animations and blinker state.
     *
     * Computes displacement and yaw from speed and wheel angle, smoothly
     * interpolates door/trunk/hood angles, and toggles blinkers at 2 Hz.
     *
     * @param dt Time step since the last frame (seconds).
     */
    void update(float dt);

    /**
     * @brief Applies keyboard inputs to the car dynamics.
     *
     * Handles acceleration, braking (with slow reverse), natural friction,
     * and steering with self-centering return.
     *
     * @param accel Accelerator key held.
     * @param brake Brake / reverse key held.
     * @param left  Left-turn key held.
     * @param right Right-turn key held.
     * @param dt    Time step since the last frame (seconds).
     */
    void applyInput(bool accel, bool brake, bool left, bool right, float dt);

    /**
     * @brief Converts speed from km/h to m/s.
     * @return Speed in metres per second.
     */
    float speedMs() const { return speed * 0.2778f; }
};
