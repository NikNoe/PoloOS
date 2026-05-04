#include "RoadRenderer.h"
#include <cmath>
#include <cstdio>

// ─── RoadRenderer.cpp ─────────────────────────────────────────────────────────

#ifndef DEG2RAD
#define DEG2RAD 0.0174532925f
#endif

RoadRenderer::RoadRenderer() {}

// ── Couleurs modulées jour/nuit ────────────────────────────────────────────────
Color RoadRenderer::roadColor(const DayNightCycle& day) {
    float v = day.visibility();
    unsigned char b = (unsigned char)(35 + v * 20);
    return { b, b, (unsigned char)(b+5), 255 };
}

Color RoadRenderer::markingColor(const DayNightCycle& day) {
    float v = day.visibility();
    unsigned char b = (unsigned char)(180 * v + 20);
    return { b, b, (unsigned char)(b * 0.8f), 255 };
}

Color RoadRenderer::sidewalkColor(const DayNightCycle& day) {
    float v = day.visibility();
    unsigned char b = (unsigned char)(80 + v * 40);
    return { b, b, b, 255 };
}

// ── Point perpendiculaire à une ligne ─────────────────────────────────────────
Vector3 RoadRenderer::perpendicular(Vector3 a, Vector3 b, float offset) {
    float dx = b.x - a.x;
    float dz = b.z - a.z;
    float len = std::sqrt(dx*dx + dz*dz);
    if (len < 0.001f) return a;
    return { a.x - dz/len * offset, a.y, a.z + dx/len * offset };
}

// ── Ligne épaisse via triangles ────────────────────────────────────────────────
void RoadRenderer::drawThickLine(Vector3 a, Vector3 b, float width, Color col) {
    float dx = b.x - a.x;
    float dz = b.z - a.z;
    float len = std::sqrt(dx*dx + dz*dz);
    if (len < 0.001f) return;

    float nx = -dz / len * width * 0.5f;
    float nz =  dx / len * width * 0.5f;

    Vector3 a1 = { a.x + nx, a.y, a.z + nz };
    Vector3 a2 = { a.x - nx, a.y, a.z - nz };
    Vector3 b1 = { b.x + nx, b.y, b.z + nz };
    Vector3 b2 = { b.x - nx, b.y, b.z - nz };

    DrawTriangle3D(a1, b1, a2, col);
    DrawTriangle3D(b1, b2, a2, col);
}

// ── Rendu principal ───────────────────────────────────────────────────────────
void RoadRenderer::draw(const RoadNetwork& network, const DayNightCycle& day) {
    // Sol herbe général
    DrawPlane({ 0.f, -0.01f, 0.f }, { 2000.f, 2000.f },
              { 30, 65, 25, 255 });

    // Segments
    for (const auto& seg : network.segments())
        drawSegment(seg, network, day);

    // Nœuds spéciaux
    for (const auto& node : network.nodes()) {
        if (node.type == NodeType::ROUNDABOUT)
            drawRoundabout(node, day);
        else if (node.type == NodeType::INTERSECTION)
            drawIntersection(node, day);
    }

    drawBuildings(network);
}

// ── Segment de route ──────────────────────────────────────────────────────────
void RoadRenderer::drawSegment(const RoadSegment& seg,
                                const RoadNetwork& net,
                                const DayNightCycle& day)
{
    if (seg.curvePoints.size() < 2) return;

    float roadW     = seg.lanes * 3.5f;   // 3.5m par voie
    float sidewalkW = 1.8f;
    Color rc  = roadColor(day);
    Color sc  = sidewalkColor(day);

    for (int i = 0; i < (int)seg.curvePoints.size() - 1; i++) {
        Vector3 a = { seg.curvePoints[i].x,   0.f, seg.curvePoints[i].z   };
        Vector3 b = { seg.curvePoints[i+1].x, 0.f, seg.curvePoints[i+1].z };

        // Chaussée
        drawThickLine(a, b, roadW, rc);

        // Trottoirs
        Vector3 sa1 = perpendicular(a, b,  roadW * 0.5f + sidewalkW * 0.5f);
        Vector3 sb1 = perpendicular(b, a, -roadW * 0.5f - sidewalkW * 0.5f);
        drawThickLine(sa1, { perpendicular(b, a, -(roadW*0.5f+sidewalkW*0.5f)).x,
                              0.05f,
                              perpendicular(b, a, -(roadW*0.5f+sidewalkW*0.5f)).z },
                      sidewalkW, sc);

        Vector3 sa2 = perpendicular(a, b, -(roadW * 0.5f + sidewalkW * 0.5f));
        drawThickLine(sa2, { perpendicular(b, a, roadW*0.5f+sidewalkW*0.5f).x,
                              0.05f,
                              perpendicular(b, a, roadW*0.5f+sidewalkW*0.5f).z },
                      sidewalkW, sc);
    }

    // Marquages
    drawMarkings(seg, day);
}

// ── Marquages au sol ──────────────────────────────────────────────────────────
void RoadRenderer::drawMarkings(const RoadSegment& seg, const DayNightCycle& day) {
    if (seg.curvePoints.size() < 2) return;

    Color mc = markingColor(day);
    Color wc = { (unsigned char)(mc.r * 0.9f),
                 (unsigned char)(mc.g * 0.9f),
                 (unsigned char)(mc.b * 0.9f), 255 };

    float dashLen = 3.f, dashGap = 3.f;
    float accumulated = 0.f;
    bool  dashOn = true;

    for (int i = 0; i < (int)seg.curvePoints.size() - 1; i++) {
        Vector3 a = { seg.curvePoints[i].x,   0.01f, seg.curvePoints[i].z   };
        Vector3 b = { seg.curvePoints[i+1].x, 0.01f, seg.curvePoints[i+1].z };

        float dx  = b.x - a.x;
        float dz  = b.z - a.z;
        float len = std::sqrt(dx*dx + dz*dz);

        accumulated += len;
        float threshold = dashOn ? dashLen : dashGap;

        if (accumulated >= threshold) {
            accumulated = 0.f;
            dashOn = !dashOn;
        }

        // Ligne centrale jaune discontinue
        if (dashOn)
            drawThickLine(a, b, 0.12f, mc);

        // Bandes blanches de bord continues
        float roadW = seg.lanes * 3.5f * 0.5f - 0.3f;
        Vector3 la = perpendicular(a, b,  roadW);
        Vector3 lb = { perpendicular(b, a, -roadW).x, 0.01f,
                       perpendicular(b, a, -roadW).z };
        Vector3 ra = perpendicular(a, b, -roadW);
        Vector3 rb = { perpendicular(b, a, roadW).x, 0.01f,
                       perpendicular(b, a, roadW).z };

        drawThickLine(la, lb, 0.12f, wc);
        drawThickLine(ra, rb, 0.12f, wc);
    }
}

// ── Rond-point ────────────────────────────────────────────────────────────────
void RoadRenderer::drawRoundabout(const RoadNode& node, const DayNightCycle& day) {
    Vector3 center = { node.x, 0.f, node.z };
    float   r      = node.radius > 0.f ? node.radius : 22.f;
    float   roadW  = 7.f;

    Color rc = roadColor(day);
    Color gc = { 30, 90, 30, 255 };  // vert îlot central

    // Anneau routier
    DrawCylinder(center, r + roadW, r + roadW, 0.05f, 32, rc);
    // Trou central vert
    DrawCylinder(center, r, r, 0.08f, 32, gc);
    // Marquage blanc anneau
    Color mc = markingColor(day);
    DrawCircle3D(center, r + 0.3f,  { 1,0,0 }, 90.f, mc);
    DrawCircle3D(center, r + roadW - 0.3f, { 1,0,0 }, 90.f, mc);

    // Indicateur nœud (debug)
    DrawCylinder({ node.x, 0.1f, node.z }, 1.f, 1.f, 0.3f, 8,
                 { 0, 200, 255, 80 });
}

// ── Intersection ──────────────────────────────────────────────────────────────
void RoadRenderer::drawIntersection(const RoadNode& node, const DayNightCycle& day) {
    float size = 8.f;
    Color rc = roadColor(day);
    DrawCube({ node.x, 0.f, node.z }, size*2, 0.05f, size*2, rc);

    // Passage piéton
    Color wc = markingColor(day);
    for (int i = -3; i <= 3; i++) {
        if (i == 0) continue;
        DrawCube({ node.x + i*1.2f, 0.02f, node.z + size },
                  0.8f, 0.01f, 2.5f, wc);
        DrawCube({ node.x + i*1.2f, 0.02f, node.z - size },
                  0.8f, 0.01f, 2.5f, wc);
    }

    // Indicateur debug
    DrawCylinder({ node.x, 0.1f, node.z }, 0.8f, 0.8f, 0.3f, 4,
                 { 255, 200, 0, 80 });
}

// ── Bâtiments le long des routes ──────────────────────────────────────────────
void RoadRenderer::drawBuildings(const RoadNetwork& net) {
    for (const auto& seg : net.segments()) {
        if (seg.curvePoints.size() < 2) continue;

        // Un bâtiment tous les ~40m
        for (int i = 0; i < (int)seg.curvePoints.size()-1; i += 2) {
            Vector3 a = { seg.curvePoints[i].x,   0.f, seg.curvePoints[i].z };
            Vector3 b = { seg.curvePoints[i+1].x, 0.f, seg.curvePoints[i+1].z };

            float roadW = seg.lanes * 3.5f * 0.5f + 3.f;

            for (int side = -1; side <= 1; side += 2) {
                Vector3 bp = perpendicular(a, b, side * (roadW + 6.f));
                float h = 4.f + ((int)(bp.x * 7 + bp.z * 3) % 12);
                Color bc = {
                    (unsigned char)(40 + ((int)(bp.x*3) % 30)),
                    (unsigned char)(40 + ((int)(bp.z*2) % 25)),
                    (unsigned char)(50 + ((int)(bp.x+bp.z) % 20)),
                    255
                };
                DrawCube({ bp.x, h*0.5f, bp.z }, 8.f, h, 8.f, bc);
                DrawCubeWires({ bp.x, h*0.5f, bp.z }, 8.f, h, 8.f,
                              { 60, 60, 70, 255 });

                // Fenêtres
                for (int row = 0; row < (int)(h/2.f); row++) {
                    bool lit = ((int)(bp.x + row) % 3) != 0;
                    if (lit) DrawCube({ bp.x + side*3.5f, 1.5f + row*2.f, bp.z },
                                      0.5f, 0.8f, 0.05f,
                                      { 255, 220, 120, 180 });
                }
            }
        }
    }
}