#pragma once
#include "RoadNode.h"
#include "RoadSegment.h"
#include <vector>
#include <string>

class RoadNetwork {
public:
    RoadNetwork();

    bool load(const std::string& jsonPath);
    void save(const std::string& jsonPath);

    // Spawn dynamique depuis DebugPanel
    void spawnRoundabout  (float x, float z);
    void spawnIntersection(float x, float z);
    void spawnSegment     (int fromId, int toId);

    const std::vector<RoadNode>&    nodes()    const { return m_nodes; }
    const std::vector<RoadSegment>& segments() const { return m_segments; }

    // Interface YOLO future
    void injectDetectedNode(float x, float z, NodeType type, float confidence);

private:
    std::vector<RoadNode>    m_nodes;
    std::vector<RoadSegment> m_segments;

    int  nextId() const { return (int)m_nodes.size(); }
    void computeAllCurves();

    // Parser JSON minimal sans dépendance externe
    bool parseJson(const std::string& content);
};