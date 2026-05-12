#pragma once

/**
 * @file RoadSegment.h
 * @brief Represents a directed road segment between two nodes, with Bezier curve geometry.
 */

#include "RoadNode.h"
#include <vector>

/**
 * @brief A 2D point along a road curve.
 */
struct CurvePoint {
    float x, z; ///< World position (metres).
};

/**
 * @brief A directed road segment connecting two RoadNode instances.
 *
 * Stores lane count, speed limit and the pre-computed quadratic Bezier
 * polyline used for rendering and agent navigation.
 */
struct RoadSegment {
    int   fromId, toId;    ///< Source and destination node IDs.
    int   lanes      = 2;  ///< Number of lanes.
    int   speedLimit = 50; ///< Speed limit in km/h.

    std::vector<CurvePoint> curvePoints; ///< Pre-computed Bezier polyline (auto-generated).

    /**
     * @brief Returns the straight-line length of the segment (metres).
     * @return Euclidean distance between the two endpoint nodes.
     */
    float length() const { return m_length; }

    /**
     * @brief Generates the quadratic Bezier polyline between two nodes.
     *
     * The control point is offset perpendicularly from the midpoint to produce
     * an organic curve. The sign of the offset alternates based on node IDs.
     *
     * @param from Source node.
     * @param to   Destination node.
     */
    void computeCurve(const RoadNode& from, const RoadNode& to);

private:
    float m_length = 0.f; ///< Cached straight-line length (set by computeCurve).
};
