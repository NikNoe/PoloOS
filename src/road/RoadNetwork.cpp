/**
 * @file RoadNetwork.cpp
 * @brief Implementation of road network loading, parsing and dynamic spawning.
 */

#include "RoadNetwork.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstdio>

// -- Minimal JSON helpers -- no external dependency -----------------------------

/**
 * @brief Extracts a float value from a flat JSON string.
 * @param s   JSON string.
 * @param key Key to look up.
 * @return Parsed float, or 0.0 on failure.
 */
static float parseFloat(const std::string& s, const std::string& key) {
    auto pos = s.find("\"" + key + "\"");
    if (pos == std::string::npos) return 0.f;
    auto colon = s.find(':', pos);
    return std::stof(s.substr(colon + 1));
}

/**
 * @brief Extracts an integer value from a flat JSON string.
 * @param s   JSON string.
 * @param key Key to look up.
 * @return Parsed integer, or 0 on failure.
 */
static int parseInt(const std::string& s, const std::string& key) {
    auto pos = s.find("\"" + key + "\"");
    if (pos == std::string::npos) return 0;
    auto colon = s.find(':', pos);
    return std::stoi(s.substr(colon + 1));
}

/**
 * @brief Extracts a string value from a flat JSON string.
 * @param s   JSON string.
 * @param key Key to look up.
 * @return Parsed string value, or empty string on failure.
 */
static std::string parseString(const std::string& s, const std::string& key) {
    auto pos = s.find("\"" + key + "\"");
    if (pos == std::string::npos) return "";
    auto q1 = s.find('"', s.find(':', pos) + 1);
    auto q2 = s.find('"', q1 + 1);
    return s.substr(q1 + 1, q2 - q1 - 1);
}

// -----------------------------------------------------------------------------

RoadNetwork::RoadNetwork() {}

bool RoadNetwork::load(const std::string& jsonPath) {
    std::ifstream f(jsonPath);
    if (!f.is_open()) {
        printf("[RoadNetwork] File not found: %s\n", jsonPath.c_str());
        return false;
    }

    std::stringstream ss;
    ss << f.rdbuf();
    std::string content = ss.str();

    return parseJson(content);
}

bool RoadNetwork::parseJson(const std::string& content) {
    m_nodes.clear();
    m_segments.clear();

    // -- Parse nodes -----------------------------------------------------------
    auto nodesStart = content.find("\"nodes\"");
    auto nodesEnd   = content.find("\"segments\"");
    std::string nodesBlock = content.substr(nodesStart, nodesEnd - nodesStart);

    size_t pos = 0;
    while ((pos = nodesBlock.find('{', pos)) != std::string::npos) {
        auto end = nodesBlock.find('}', pos);
        std::string obj = nodesBlock.substr(pos, end - pos + 1);

        RoadNode node;
        node.id     = parseInt(obj, "id");
        node.x      = parseFloat(obj, "x");
        node.z      = parseFloat(obj, "z");
        node.radius = parseFloat(obj, "radius");

        std::string type = parseString(obj, "type");
        if      (type == "intersection") node.type = NodeType::INTERSECTION;
        else if (type == "roundabout")   node.type = NodeType::ROUNDABOUT;
        else                             node.type = NodeType::SIMPLE;

        m_nodes.push_back(node);
        pos = end + 1;
    }

    // -- Parse segments --------------------------------------------------------
    auto segStart = content.find("\"segments\"");
    std::string segBlock = content.substr(segStart);

    pos = 0;
    while ((pos = segBlock.find('{', pos)) != std::string::npos) {
        auto end = segBlock.find('}', pos);
        std::string obj = segBlock.substr(pos, end - pos + 1);

        RoadSegment seg;
        seg.fromId     = parseInt(obj, "from");
        seg.toId       = parseInt(obj, "to");
        seg.lanes      = parseInt(obj, "lanes");
        seg.speedLimit = parseInt(obj, "speedLimit");

        if (seg.fromId < (int)m_nodes.size() &&
            seg.toId   < (int)m_nodes.size()) {
            seg.computeCurve(m_nodes[seg.fromId], m_nodes[seg.toId]);
            m_segments.push_back(seg);
        }
        pos = end + 1;
    }

    printf("[RoadNetwork] Loaded: %zu nodes, %zu segments\n",
           m_nodes.size(), m_segments.size());
    return true;
}

// -- Bezier curve generation ----------------------------------------------------

void RoadSegment::computeCurve(const RoadNode& from, const RoadNode& to) {
    curvePoints.clear();

    float dx = to.x - from.x;
    float dz = to.z - from.z;
    float len = std::sqrt(dx*dx + dz*dz);

    // Bezier control point offset perpendicularly from the midpoint
    float offset = len * 0.3f;
    float nx = -dz / len;  // normal direction
    float nz =  dx / len;

    // Alternate offset sign based on node IDs for organic variety
    float sign = ((from.id + to.id) % 2 == 0) ? 1.f : -1.f;
    float cpx = (from.x + to.x) * 0.5f + nx * offset * sign;
    float cpz = (from.z + to.z) * 0.5f + nz * offset * sign;

    // Sample 20 points along the quadratic Bezier curve
    int steps = 20;
    for (int i = 0; i <= steps; i++) {
        float t  = (float)i / steps;
        float it = 1.f - t;
        float x  = it*it*from.x + 2*it*t*cpx + t*t*to.x;
        float z  = it*it*from.z + 2*it*t*cpz + t*t*to.z;
        curvePoints.push_back({ x, z });
    }

    m_length = len;
}

// -- Dynamic spawning ----------------------------------------------------------

void RoadNetwork::spawnRoundabout(float x, float z) {
    RoadNode node;
    node.id     = nextId();
    node.type   = NodeType::ROUNDABOUT;
    node.x      = x;
    node.z      = z;
    node.radius = 22.f;
    m_nodes.push_back(node);

    // Connect to the nearest existing node
    float minDist = 9999.f;
    int   nearest = 0;
    for (int i = 0; i < (int)m_nodes.size()-1; i++) {
        float dx = m_nodes[i].x - x;
        float dz = m_nodes[i].z - z;
        float d  = std::sqrt(dx*dx + dz*dz);
        if (d < minDist) { minDist = d; nearest = i; }
    }

    RoadSegment seg;
    seg.fromId = nearest;
    seg.toId   = node.id;
    seg.lanes  = 2;
    seg.speedLimit = 30;
    seg.computeCurve(m_nodes[nearest], node);
    m_segments.push_back(seg);

    printf("[RoadNetwork] Roundabout spawned at (%.1f, %.1f)\n", x, z);
}

void RoadNetwork::spawnIntersection(float x, float z) {
    RoadNode node;
    node.id   = nextId();
    node.type = NodeType::INTERSECTION;
    node.x    = x;
    node.z    = z;
    m_nodes.push_back(node);

    // Connect to the 2 nearest existing nodes
    std::vector<std::pair<float,int>> dists;
    for (int i = 0; i < (int)m_nodes.size()-1; i++) {
        float dx = m_nodes[i].x - x;
        float dz = m_nodes[i].z - z;
        dists.push_back({ std::sqrt(dx*dx+dz*dz), i });
    }
    std::sort(dists.begin(), dists.end());

    for (int k = 0; k < std::min(2, (int)dists.size()); k++) {
        RoadSegment seg;
        seg.fromId = dists[k].second;
        seg.toId   = node.id;
        seg.lanes  = 2;
        seg.speedLimit = 50;
        seg.computeCurve(m_nodes[dists[k].second], node);
        m_segments.push_back(seg);
    }

    printf("[RoadNetwork] Intersection spawned at (%.1f, %.1f)\n", x, z);
}

void RoadNetwork::injectDetectedNode(float x, float z, NodeType type, float confidence) {
    // Future YOLO interface
    RoadNode node;
    node.id                 = nextId();
    node.type               = type;
    node.x                  = x;
    node.z                  = z;
    node.detectedByCamera   = true;
    node.confidence         = confidence;
    m_nodes.push_back(node);
}
