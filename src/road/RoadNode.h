#pragma once

/**
 * @file RoadNode.h
 * @brief Represents a single node (vertex) in the road network graph.
 */

#include <string>

/**
 * @brief Semantic type of a road node.
 */
enum class NodeType {
    SIMPLE,       ///< Plain waypoint with no special geometry.
    INTERSECTION, ///< 4-way (or multi-way) intersection.
    ROUNDABOUT    ///< Circular roundabout.
};

/**
 * @brief A node in the road network graph.
 *
 * Stores the 2D world position, semantic type and optional detection metadata
 * for future YOLO-based map augmentation.
 */
struct RoadNode {
    int      id;                       ///< Unique node identifier.
    NodeType type;                     ///< Semantic type of the node.
    float    x, z;                     ///< World position (metres).
    float    radius = 0.f;             ///< Roundabout radius (metres, 0 for non-roundabouts).

    bool     detectedByCamera = false; ///< True if this node was detected via camera (future YOLO use).
    float    confidence       = 1.f;   ///< Detection confidence (0.0-1.0).
};
