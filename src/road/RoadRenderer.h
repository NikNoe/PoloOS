#pragma once
#include "RoadNetwork.h"
#include "../world/DayNightCycle.h"
#include "raylib.h"

class RoadRenderer {
public:
    RoadRenderer();
    void draw(const RoadNetwork& network, const DayNightCycle& day);

private:
    void drawSegment    (const RoadSegment& seg, const RoadNetwork& net, const DayNightCycle& day);
    void drawRoundabout (const RoadNode& node,   const DayNightCycle& day);
    void drawIntersection(const RoadNode& node,  const DayNightCycle& day);
    void drawMarkings   (const RoadSegment& seg, const DayNightCycle& day);
    void drawSidewalk   (const RoadSegment& seg);
    void drawBuildings  (const RoadNetwork& net);

    // Couleurs modulées par jour/nuit
    Color roadColor    (const DayNightCycle& day);
    Color markingColor (const DayNightCycle& day);
    Color sidewalkColor(const DayNightCycle& day);

    // Utilitaires géométrie
    void  drawThickLine(Vector3 a, Vector3 b, float width, Color col);
    Vector3 perpendicular(Vector3 a, Vector3 b, float offset);
};