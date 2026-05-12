#pragma once

/**
 * @file CarRenderer.h
 * @brief Raylib 3D renderer for the Volkswagen Polo model.
 */

#include "PoloCar.h"
#include "raylib.h"

/**
 * @brief Loads and renders the Polo 3D GLB model.
 *
 * Manages the Raylib model lifecycle (GPU upload on construction,
 * release on destruction). Reads position and heading from PoloCar.
 */
class CarRenderer {
public:
    /** @brief Loads the 3D model from assets/models/polo.glb. */
    CarRenderer();

    /** @brief Unloads the 3D model from GPU memory. */
    ~CarRenderer();

    /**
     * @brief Draws the car at its current position and orientation.
     * @param car Current car state (world x/z position and heading).
     */
    void draw(const PoloCar& car);

private:
    Model m_model;          ///< Raylib 3D model handle.
    bool  m_loaded = false; ///< True if the model was successfully loaded.
};
