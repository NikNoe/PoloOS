#pragma once
#include "RoadNode.h"
#include <vector>

struct CurvePoint {
    float x, z;
};

struct RoadSegment {
    int   fromId, toId;
    int   lanes      = 2;
    int   speedLimit = 50;

    // Points de contrôle de la courbe (générés automatiquement)
    std::vector<CurvePoint> curvePoints;

    float length()  const { return m_length; }
    void  computeCurve(const RoadNode& from, const RoadNode& to);

private:
    float m_length = 0.f;
};