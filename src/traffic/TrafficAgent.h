#pragma once

/**
 * @file TrafficAgent.h
 * @brief 3D scene agent representing a YOLO-detected object with smooth interpolation.
 */

#include "../network/DetectedObject.h"
#include "raylib.h"
#include "raymath.h"

/**
 * @brief Represents a YOLO-detected object as a live 3D scene entity.
 *
 * Smoothly interpolates position between successive UDP updates to avoid
 * visual jitter. Fades out as the TTL decreases and disappears when dead.
 * Shared 3D models are loaded once and reused across all instances.
 */
class TrafficAgent {
public:
    /** @brief Constructs an uninitialised agent. */
    TrafficAgent() = default;

    /**
     * @brief Constructs an agent from a fresh detection.
     * @param det Source DetectedObject from the UDP receiver.
     */
    explicit TrafficAgent(const DetectedObject& det);

    /**
     * @brief Updates the agent state with a new detection reading.
     *
     * Applies a weighted smooth blend (60% new, 40% old) for position
     * to reduce jitter between frames.
     *
     * @param det New detection data.
     * @param dt  Time step since the last frame (seconds).
     */
    void update(const DetectedObject& det, float dt);

    /**
     * @brief Draws the agent in 3D (body, ground ring, label line).
     *
     * Geometry varies by class: capsule for pedestrians, coloured box for
     * vehicles, pole + box for traffic lights and stop signs.
     * Alpha fades proportionally to remaining TTL.
     */
    void draw() const;

    /** @return Current world X position (metres). */
    float x()          const { return m_x; }

    /** @return Current world Z position (metres). */
    float z()          const { return m_z; }

    /** @return Current heading estimate (degrees). */
    float heading()    const { return m_heading; }

    /** @return Detection confidence (0.0-1.0). */
    float confidence() const { return m_confidence; }

    /** @return Remaining time-to-live (seconds). */
    float ttl()        const { return m_ttl; }

    /** @return Object class. */
    ObjectClass cls()  const { return m_cls; }

    /** @return True if the agent still has positive TTL. */
    bool  isAlive()    const { return m_ttl > 0.f; }

    /** @return Inter-frame tracking ID. */
    int trackId()      const { return m_trackId; }

    /**
     * @brief Loads the shared mesh models (car box, person cylinder, generic box).
     *
     * Idempotent -- does nothing if models are already loaded.
     */
    static void loadSharedModels();

    /** @brief Unloads all shared mesh models from GPU memory. */
    static void unloadSharedModels();

private:
    float       m_x          = 0.f;                   ///< World X position (metres).
    float       m_z          = 0.f;                   ///< World Z position (metres).
    float       m_heading    = 0.f;                   ///< Heading (degrees).
    float       m_confidence = 0.f;                   ///< Detection confidence.
    float       m_ttl        = 1.5f;                  ///< Time-to-live (seconds).
    float       m_scale      = 1.f;                   ///< Render scale factor.
    ObjectClass m_cls        = ObjectClass::UNKNOWN;  ///< Object class.
    std::string m_className;                           ///< Class name string.
    int         m_trackId    = -1;                    ///< Tracking ID.

    /**
     * @brief Returns the display colour for this agent's class.
     * @return Raylib Color with class-specific hue.
     */
    Color classColor() const;

    /**
     * @brief Returns the typical height for this agent's class (metres).
     * @return Height in metres.
     */
    float classHeight() const;

    /**
     * @brief Returns the typical ground radius for this agent's class (metres).
     * @return Radius in metres.
     */
    float classRadius() const;

    /**
     * @brief Draws a vertical line from ground to the label position.
     * @param pos 3D world position of the label anchor.
     */
    void drawLabel(Vector3 pos) const;

    static Model s_carModel;     ///< Shared box mesh for vehicle classes.
    static Model s_personModel;  ///< Shared cylinder mesh for pedestrians.
    static Model s_boxModel;     ///< Shared box mesh for generic objects.
    static bool  s_modelsLoaded; ///< True if shared models have been loaded.
};
