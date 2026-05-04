#pragma once
#include <string>

enum class NodeType { SIMPLE, INTERSECTION, ROUNDABOUT };

struct RoadNode {
    int      id;
    NodeType type;
    float    x, z;
    float    radius = 0.f;  // pour les ronds-points

    // Futur YOLO : un nœud peut être détecté par caméra
    bool     detectedByCamera = false;
    float    confidence       = 1.f;
};