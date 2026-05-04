#pragma once
#include "PoloCar.h"
#include "raylib.h"

class CarRenderer {
public:
    CarRenderer();
    ~CarRenderer();
    void draw(const PoloCar& car);

private:
    Model m_model;
    bool  m_loaded = false;
};