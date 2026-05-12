/**
 * @file RoadRenderer.cpp
 * @brief Implementation of the road network 3D renderer.
 */

#include "RoadRenderer.h"
#include <cmath>
#include <cstdio>

#ifndef DEG2RAD
#define DEG2RAD 0.0174532925f
#endif

RoadRenderer::RoadRenderer() {}

// ── Day/night colour helpers ──────────────────────────────────────────────────

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

// ── Perpendicular offset helper ───────────────────────────────────────────────

Vector3 RoadRenderer::perpendicular(Vector3 a, Vector3 b, float offset) {
    float dx = b.x - a.x;
    float dz = b.z - a.z;
    float len = std::sqrt(dx*dx + dz*dz);
    if (len < 0.001f) return a;
    return { a.x - dz/len * offset, a.y, a.z + dx/len * offset };
}

// ── Thick line via two triangles ──────────────────────────────────────────────

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

// ── Main draw ─────────────────────────────────────────────────────────────────

void RoadRenderer::draw(const RoadNetwork& network, const DayNightCycle& day) {
    // Grass ground plane
    DrawPlane({ 0.f, -0.01f, 0.f }, { 2000.f, 2000.f },
              { 30, 65, 25, 255 });

    for (const auto& seg : network.segments())
        drawSegment(seg, network, day);

    for (const auto& node : network.nodes()) {
        if (node.type == NodeType::ROUNDABOUT)
            drawRoundabout(node, day);
        else if (node.type == NodeType::INTERSECTION)
            drawIntersection(node, day);
    }

    drawBuildings(network);
}

// ── Road segment ──────────────────────────────────────────────────────────────

void RoadRenderer::drawSegment(const RoadSegment& seg,
                                const RoadNetwork& net,
                                const DayNightCycle& day)
{
    if (seg.curvePoints.size() < 2) return;

    float roadW     = seg.lanes * 3.5f;
    float sidewalkW = 1.8f;
    Color rc = roadColor(day);
    Color sc = sidewalkColor(day);

    // Trim distance to avoid overdrawing inside roundabout/intersection radii
    float trimStart = 8.f;
    float trimEnd   = 8.f;

    // Compute total curve length
    float totalLen = 0.f;
    for (int i = 0; i < (int)seg.curvePoints.size()-1; i++) {
        float dx = seg.curvePoints[i+1].x - seg.curvePoints[i].x;
        float dz = seg.curvePoints[i+1].z - seg.curvePoints[i].z;
        totalLen += std::sqrt(dx*dx + dz*dz);
    }

    // Only trim at non-simple endpoints
    const RoadNode& fromNode = net.nodes()[seg.fromId];
    const RoadNode& toNode   = net.nodes()[seg.toId];
    float ts = (fromNode.type != NodeType::SIMPLE) ? 4.f : 0.f;
    float te = (toNode.type   != NodeType::SIMPLE) ? 4.f : 0.f;

    float accumulated = 0.f;
    for (int i = 0; i < (int)seg.curvePoints.size()-1; i++) {
        float dx  = seg.curvePoints[i+1].x - seg.curvePoints[i].x;
        float dz  = seg.curvePoints[i+1].z - seg.curvePoints[i].z;
        float len = std::sqrt(dx*dx + dz*dz);

        float segStart = accumulated;
        float segEnd   = accumulated + len;

        // Skip sub-segments inside the trim zones
        if (segEnd   <= ts)              { accumulated += len; continue; }
        if (segStart >= totalLen - te)   { accumulated += len; continue; }

        Vector3 a = { seg.curvePoints[i].x,   0.f, seg.curvePoints[i].z   };
        Vector3 b = { seg.curvePoints[i+1].x, 0.f, seg.curvePoints[i+1].z };

        drawThickLine(a, b, roadW, rc);

        // Sidewalks on each side
        float off = roadW * 0.5f + sidewalkW * 0.5f;
        Vector3 sa = perpendicular(a, b,  off);
        Vector3 sb = { perpendicular(b, a, -off).x, 0.05f,
                       perpendicular(b, a, -off).z };
        Vector3 ra = perpendicular(a, b, -off);
        Vector3 rb = { perpendicular(b, a,  off).x, 0.05f,
                       perpendicular(b, a,  off).z };

        drawThickLine(sa, sb, sidewalkW, sc);
        drawThickLine(ra, rb, sidewalkW, sc);

        accumulated += len;
    }

    drawMarkings(seg, day);
}

// ── Road markings ─────────────────────────────────────────────────────────────

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

        // Dashed yellow centre line
        if (dashOn)
            drawThickLine(a, b, 0.12f, mc);

        // Solid white edge lines
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

// ── Roundabout ────────────────────────────────────────────────────────────────

void RoadRenderer::drawRoundabout(const RoadNode& node, const DayNightCycle& day) {
    Vector3 center = { node.x, 0.f, node.z };
    float   r      = node.radius > 0.f ? node.radius : 22.f;
    float   roadW  = 7.f;
    float   outer  = r + roadW;

    Color rc = roadColor(day);
    Color gc = { 35, 85, 30, 255 };   // green island
    Color mc = markingColor(day);
    Color cc = { 60, 60, 65, 255 };   // kerb colour

    int steps = 32;
    for (int i = 0; i < steps; i++) {
        float a0 = (float)i     / steps * 2.f * PI;
        float a1 = (float)(i+1) / steps * 2.f * PI;

        // Carriageway ring
        Vector3 o0  = { center.x + outer * std::cos(a0), 0.001f, center.z + outer * std::sin(a0) };
        Vector3 o1  = { center.x + outer * std::cos(a1), 0.001f, center.z + outer * std::sin(a1) };
        Vector3 i0  = { center.x + r     * std::cos(a0), 0.001f, center.z + r     * std::sin(a0) };
        Vector3 i1  = { center.x + r     * std::cos(a1), 0.001f, center.z + r     * std::sin(a1) };

        DrawTriangle3D(o0, i0, o1, rc);
        DrawTriangle3D(i0, i1, o1, rc);

        // Outer edge marking
        DrawLine3D(o0, o1, mc);
        // Inner edge marking
        DrawLine3D(i0, i1, mc);

        // Central green island
        Vector3 c0 = { center.x + (r-0.5f) * std::cos(a0), 0.002f, center.z + (r-0.5f) * std::sin(a0) };
        Vector3 c1 = { center.x + (r-0.5f) * std::cos(a1), 0.002f, center.z + (r-0.5f) * std::sin(a1) };
        DrawTriangle3D(c0, center, c1, gc);

        // Island kerb
        DrawCube({ center.x + (r-0.3f) * std::cos((a0+a1)*0.5f),
                   0.08f,
                   center.z + (r-0.3f) * std::sin((a0+a1)*0.5f) },
                  0.3f, 0.15f, 0.3f, cc);
    }

    // Directional arrows at the four cardinal entries
    for (int i = 0; i < 4; i++) {
        float angle = i * PI * 0.5f;
        float mx    = center.x + (r + roadW*0.5f) * std::cos(angle);
        float mz    = center.z + (r + roadW*0.5f) * std::sin(angle);
        Vector3 tip  = { mx + std::cos(angle+PI*0.5f)*1.5f, 0.02f,
                         mz + std::sin(angle+PI*0.5f)*1.5f };
        Vector3 bl   = { mx + std::cos(angle+PI*0.8f)*1.f,  0.02f,
                         mz + std::sin(angle+PI*0.8f)*1.f };
        Vector3 br   = { mx + std::cos(angle+PI*0.2f)*1.f,  0.02f,
                         mz + std::sin(angle+PI*0.2f)*1.f };
        DrawTriangle3D(tip, bl, br, mc);
    }
}

// ── Intersection ──────────────────────────────────────────────────────────────

void RoadRenderer::drawIntersection(const RoadNode& node, const DayNightCycle& day) {
    Color rc = roadColor(day);
    Color mc = markingColor(day);

    float size = 10.f;

    // Central junction slab
    DrawCylinder({ node.x, 0.001f, node.z }, size, size, 0.05f, 16, rc);

    // Pedestrian crossings on all four sides
    for (int dir = 0; dir < 4; dir++) {
        float angle = dir * 90.f * DEG2RAD;
        float cx = node.x + std::cos(angle) * (size + 1.5f);
        float cz = node.z + std::sin(angle) * (size + 1.5f);

        for (int b = -2; b <= 2; b++) {
            float bx = cx + std::cos(angle + 1.5708f) * b * 0.9f;
            float bz = cz + std::sin(angle + 1.5708f) * b * 0.9f;
            DrawCube({ bx, 0.02f, bz },
                     std::abs(std::cos(angle)) < 0.5f ? 0.6f : 3.f,
                     0.01f,
                     std::abs(std::cos(angle)) < 0.5f ? 3.f : 0.6f,
                     mc);
        }
    }

    // Stop lines at each entry
    for (int dir = 0; dir < 4; dir++) {
        float angle  = dir * 90.f * DEG2RAD;
        float lx     = node.x + std::cos(angle) * (size - 1.f);
        float lz     = node.z + std::sin(angle) * (size - 1.f);
        float perpAx = std::cos(angle + 1.5708f);
        float perpAz = std::sin(angle + 1.5708f);

        Vector3 a = { lx + perpAx * 3.5f, 0.02f, lz + perpAz * 3.5f };
        Vector3 b = { lx - perpAx * 3.5f, 0.02f, lz - perpAz * 3.5f };
        drawThickLine(a, b, 0.25f, { 255, 255, 255, 220 });
    }
}

// ── Buildings alongside roads ─────────────────────────────────────────────────

void RoadRenderer::drawBuildings(const RoadNetwork& net) {
    for (const auto& seg : net.segments()) {
        if (seg.curvePoints.size() < 2) continue;

        // One building approximately every 40 m
        for (int i = 0; i < (int)seg.curvePoints.size()-1; i += 2) {
            Vector3 a = { seg.curvePoints[i].x,   0.f, seg.curvePoints[i].z };
            Vector3 b = { seg.curvePoints[i+1].x, 0.f, seg.curvePoints[i+1].z };

            float roadW = seg.lanes * 3.5f * 0.5f + 8.f;

            for (int side = -1; side <= 1; side += 2) {
                Vector3 bp = perpendicular(a, b, side * (roadW + 6.f));
                float h = 6.f + ((int)(bp.x * 7 + bp.z * 3) % 20);  // variable height
                Color bc = {
                    (unsigned char)(40 + ((int)(bp.x*3) % 30)),
                    (unsigned char)(40 + ((int)(bp.z*2) % 25)),
                    (unsigned char)(50 + ((int)(bp.x+bp.z) % 20)),
                    255
                };
                DrawCube({ bp.x, h*0.5f, bp.z }, 5.f, h, 5.f, bc);
                DrawCubeWires({ bp.x, h*0.5f, bp.z }, 5.f, h, 5.f, { 60, 60, 70, 255 });

                // Windows on all four faces
                for (int row = 0; row < (int)(h / 2.5f); row++) {
                    for (int col = -1; col <= 1; col++) {
                        bool lit = ((int)(bp.x + bp.z + row + col) % 3) != 0;
                        if (!lit) continue;
                        Color wc = { 255, 220, 120, 200 };

                        DrawCube({ bp.x + col * 1.4f, 1.8f + row * 2.5f, bp.z + 2.51f },
                                0.7f, 0.9f, 0.05f, wc);
                        DrawCube({ bp.x + col * 1.4f, 1.8f + row * 2.5f, bp.z - 2.51f },
                                0.7f, 0.9f, 0.05f, wc);
                        DrawCube({ bp.x - 2.51f, 1.8f + row * 2.5f, bp.z + col * 1.4f },
                                0.05f, 0.9f, 0.7f, wc);
                        DrawCube({ bp.x + 2.51f, 1.8f + row * 2.5f, bp.z + col * 1.4f },
                                0.05f, 0.9f, 0.7f, wc);
                    }
                }
            }
        }
    }
}
