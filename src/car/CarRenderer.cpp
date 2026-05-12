/**
 * @file CarRenderer.cpp
 * @brief Implementation of the Polo 3D rendering via Raylib.
 */

#include "CarRenderer.h"
#include "raymath.h"

CarRenderer::CarRenderer() {
    m_model  = LoadModel("assets/models/polo.glb");
    m_loaded = true;
}

CarRenderer::~CarRenderer() {
    if (m_loaded) UnloadModel(m_model);
}

void CarRenderer::draw(const PoloCar& car) {
    if (!m_loaded) return;
    Vector3 pos = { car.x, 0.f, car.z };
    DrawModelEx(m_model, pos, { 0.f, 1.f, 0.f }, car.heading, { 1.f, 1.f, 1.f }, WHITE);
}
