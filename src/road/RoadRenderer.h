#pragma once

/**
 * @file RoadRenderer.h
 * @brief Raylib renderer for the road network (segments, nodes, buildings).
 */

#include "RoadNetwork.h"
#include "../world/DayNightCycle.h"
#include "raylib.h"

/**
 * @brief Renders the full road network in 3D, including markings, sidewalks and buildings.
 *
 * All colours are modulated by the current DayNightCycle visibility factor so
 * that roads appear darker at night.
 */
class RoadRenderer {
public:
    /** @brief Constructs the renderer (no GPU resources allocated here). */
    RoadRenderer();

    /**
     * @brief Draws the complete road network for the current frame.
     *
     * Renders the grass ground plane, all road segments, special nodes
     * (roundabouts and intersections) and procedural buildings.
     *
     * @param network Road network graph to render.
     * @param day     Current day/night cycle state.
     */
    void draw(const RoadNetwork& network, const DayNightCycle& day);

private:
    /**
     * @brief Draws a single road segment with trottoirs and markings.
     * @param seg Segment to render.
     * @param net Full network (needed for node type lookup).
     * @param day Day/night state for colour modulation.
     */
    void drawSegment(const RoadSegment& seg, const RoadNetwork& net, const DayNightCycle& day);

    /**
     * @brief Draws the annular road surface and island of a roundabout node.
     * @param node Roundabout node.
     * @param day  Day/night state.
     */
    void drawRoundabout(const RoadNode& node, const DayNightCycle& day);

    /**
     * @brief Draws the junction slab and pedestrian crossings of an intersection node.
     * @param node Intersection node.
     * @param day  Day/night state.
     */
    void drawIntersection(const RoadNode& node, const DayNightCycle& day);

    /**
     * @brief Draws dashed centre-line and solid edge-line road markings for a segment.
     * @param seg Segment to mark.
     * @param day Day/night state.
     */
    void drawMarkings(const RoadSegment& seg, const DayNightCycle& day);

    /**
     * @brief Draws the raised sidewalk strips alongside a segment.
     * @param seg Segment to add sidewalks to.
     */
    void drawSidewalk(const RoadSegment& seg);

    /**
     * @brief Draws procedural buildings along all network segments.
     * @param net Road network used to place buildings beside each segment.
     */
    void drawBuildings(const RoadNetwork& net);

    /**
     * @brief Returns the road surface colour modulated by visibility.
     * @param day Day/night state.
     * @return Raylib Color for the road surface.
     */
    Color roadColor(const DayNightCycle& day);

    /**
     * @brief Returns the road marking colour modulated by visibility.
     * @param day Day/night state.
     * @return Raylib Color for line markings.
     */
    Color markingColor(const DayNightCycle& day);

    /**
     * @brief Returns the sidewalk colour modulated by visibility.
     * @param day Day/night state.
     * @return Raylib Color for the sidewalk surface.
     */
    Color sidewalkColor(const DayNightCycle& day);

    /**
     * @brief Draws a filled rectangle between two 3D points using two triangles.
     * @param a     Start point.
     * @param b     End point.
     * @param width Rectangle width (metres).
     * @param col   Fill colour.
     */
    void drawThickLine(Vector3 a, Vector3 b, float width, Color col);

    /**
     * @brief Returns a point offset perpendicularly from a line segment.
     * @param a      Line start.
     * @param b      Line end.
     * @param offset Perpendicular offset distance (metres, positive = left).
     * @return Offset 3D position at the start point.
     */
    Vector3 perpendicular(Vector3 a, Vector3 b, float offset);
};
