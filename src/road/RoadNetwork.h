#pragma once

/**
 * @file RoadNetwork.h
 * @brief Road network graph: nodes, segments, JSON loading and dynamic spawning.
 */

#include "RoadNode.h"
#include "RoadSegment.h"
#include <vector>
#include <string>

/**
 * @brief Holds the complete road network as a graph of nodes and segments.
 *
 * Supports loading from a JSON file, dynamic spawning of intersections and
 * roundabouts at runtime, and a future interface for YOLO-detected node injection.
 */
class RoadNetwork {
public:
    /** @brief Constructs an empty road network. */
    RoadNetwork();

    /**
     * @brief Loads the road network from a JSON file.
     * @param jsonPath Path to the JSON map file (e.g. assets/maps/city.json).
     * @return True on success, false if the file could not be read or parsed.
     */
    bool load(const std::string& jsonPath);

    /**
     * @brief Serialises the current network to a JSON file.
     * @param jsonPath Output file path.
     */
    void save(const std::string& jsonPath);

    /**
     * @brief Spawns a roundabout node at the given position and connects it to the nearest node.
     * @param x World X position (metres).
     * @param z World Z position (metres).
     */
    void spawnRoundabout(float x, float z);

    /**
     * @brief Spawns an intersection node and connects it to the two nearest nodes.
     * @param x World X position (metres).
     * @param z World Z position (metres).
     */
    void spawnIntersection(float x, float z);

    /**
     * @brief Creates a segment between two existing nodes and computes its curve.
     * @param fromId Source node ID.
     * @param toId   Destination node ID.
     */
    void spawnSegment(int fromId, int toId);

    /**
     * @brief Returns the list of all road nodes.
     * @return Read-only reference to the node vector.
     */
    const std::vector<RoadNode>&    nodes()    const { return m_nodes; }

    /**
     * @brief Returns the list of all road segments.
     * @return Read-only reference to the segment vector.
     */
    const std::vector<RoadSegment>& segments() const { return m_segments; }

    /**
     * @brief Injects a node detected by the camera (future YOLO interface).
     * @param x          World X position (metres).
     * @param z          World Z position (metres).
     * @param type       Semantic node type.
     * @param confidence Detection confidence (0.0–1.0).
     */
    void injectDetectedNode(float x, float z, NodeType type, float confidence);

private:
    std::vector<RoadNode>    m_nodes;    ///< All road nodes.
    std::vector<RoadSegment> m_segments; ///< All road segments.

    /** @brief Returns the next available node ID. */
    int  nextId() const { return (int)m_nodes.size(); }

    /** @brief Recomputes Bezier curves for all segments. */
    void computeAllCurves();

    /**
     * @brief Parses a JSON string into nodes and segments.
     * @param content Raw JSON string.
     * @return True if parsing succeeded.
     */
    bool parseJson(const std::string& content);
};
