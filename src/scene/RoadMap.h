#pragma once

/**
 * @file RoadMap.h
 * @brief Legacy infinite road scene centred on the car (pre-RoadNetwork renderer).
 */

#include "raylib.h"

/**
 * @brief Renders a simple, infinite straight road that scrolls with the car position.
 *
 * This is the legacy road renderer used before the graph-based RoadNetwork system.
 * It provides a ground plane, a straight two-lane road, road markings,
 * repeating procedural buildings and a static starfield skybox.
 */
class RoadMap {
public:
    /** @brief Constructs the road map (no GPU resources). */
    RoadMap();

    /**
     * @brief Draws the complete road scene for the current frame.
     * @param carX Car world X position (metres) — used to centre the scene.
     * @param carZ Car world Z position (metres) — used to scroll markings and buildings.
     */
    void draw(float carX, float carZ);

private:
    /**
     * @brief Draws the grass ground plane and road carriageway slab.
     * @param cx Car world X (metres).
     * @param cz Car world Z (metres).
     */
    void drawRoad(float cx, float cz);

    /**
     * @brief Draws dashed centre line and solid edge lines.
     * @param cx Car world X (metres).
     * @param cz Car world Z (metres).
     */
    void drawMarkings(float cx, float cz);

    /**
     * @brief Draws the static starfield (not used — ClearBackground handles the sky).
     */
    void drawGrid(float cx, float cz);

    /** @brief Draws the static star-point skybox. */
    void drawSkybox();

    /**
     * @brief Draws repeating procedural buildings on both sides of the road.
     * @param cx Car world X (metres).
     * @param cz Car world Z (metres).
     */
    void drawBuildings(float cx, float cz);

    Color m_roadColor    = {  35,  35,  40, 255 }; ///< Road surface colour.
    Color m_lineColor    = { 240, 220,  50, 255 }; ///< Centre-line colour (yellow).
    Color m_sideColor    = { 220, 220, 220, 255 }; ///< Edge-line colour (white).
    Color m_grassColor   = {  45,  90,  35, 255 }; ///< Grass ground colour.
    Color m_skyColor     = {  15,  20,  35, 255 }; ///< Night sky background colour.

    float m_roadWidth    = 7.0f;   ///< Road width (metres).
    float m_roadLength   = 200.f;  ///< Visible road half-length on each side (metres).
};
