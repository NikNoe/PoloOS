/**
 * @file PoloCar.cpp
 * @brief Implementation of PoloCar dynamics and animations.
 */

#include "PoloCar.h"
#include <cmath>
#include <algorithm>

#ifndef DEG2RAD
#define DEG2RAD 0.0174532925f
#endif

/**
 * @brief Linear interpolation between two values.
 * @param a Start value.
 * @param b End value.
 * @param t Interpolation factor (clamped to 1.0).
 * @return Interpolated value between @p a and @p b.
 */
static float lerp(float a, float b, float t) {
    return a + (b - a) * std::min(t, 1.f);
}

void PoloCar::applyInput(bool accel, bool brake, bool left, bool right, float dt)
{
    // -- Acceleration / braking ------------------------------------------------
    const float maxSpeed    =  120.f;  // km/h
    const float maxReverse  =  -20.f;
    const float accelRate   =   60.f;  // km/h per second
    const float brakeRate   =  120.f;
    const float friction    =   30.f;

    if (accel) {
        speed += accelRate * dt;
        handbrake = false;
    } else if (brake) {
        if (speed > 0.5f)       speed -= brakeRate * dt;
        else if (speed > -0.5f) speed  = 0.f;
        else                    speed += accelRate * dt * 0.5f; // slow reverse
    } else {
        // Natural friction
        if (speed > 0.f)       speed = std::max(0.f,  speed - friction * dt);
        else if (speed < 0.f)  speed = std::min(0.f,  speed + friction * dt);
    }

    speed = std::clamp(speed, maxReverse, maxSpeed);

    // -- Steering --------------------------------------------------------------
    const float maxSteer = 35.f;   // degrees
    const float steerRate = 90.f;

    if (left)       wheelAngle -= steerRate * dt;
    else if (right) wheelAngle += steerRate * dt;
    else            wheelAngle  = lerp(wheelAngle, 0.f, dt * 6.f);

    wheelAngle = std::clamp(wheelAngle, -maxSteer, maxSteer);
    steeringAngle = wheelAngle * 12.f; // steering ratio ~12:1
}

void PoloCar::update(float dt)
{
    // -- Movement --------------------------------------------------------------
    if (std::abs(speed) > 0.1f) {
        float turnRadius = 4.5f; // Polo wheelbase in metres
        float angularVel = (speedMs() / turnRadius)
                           * std::sin(wheelAngle * DEG2RAD)
                           * (180.f / M_PI);

        heading += angularVel * dt;

        float rad = heading * DEG2RAD;
        x += std::sin(rad) * speedMs() * dt;
        z += std::cos(rad) * speedMs() * dt;
    }

    // -- Wheel rotation --------------------------------------------------------
    // Polo tyre circumference ~185cm -> radius ~0.295m
    wheelRoll += (speedMs() / 0.295f) * dt * (180.f / M_PI);

    // -- Smooth door / trunk / hood animations ---------------------------------
    const float doorSpeed  = 5.f;
    const float trunkSpeed = 3.f;
    const float hoodSpeed  = 3.f;

    doorFLAngle = lerp(doorFLAngle, doorFL ? 65.f : 0.f, dt * doorSpeed);
    doorFRAngle = lerp(doorFRAngle, doorFR ? 65.f : 0.f, dt * doorSpeed);
    doorRLAngle = lerp(doorRLAngle, doorRL ? 55.f : 0.f, dt * doorSpeed);
    doorRRAngle = lerp(doorRRAngle, doorRR ? 55.f : 0.f, dt * doorSpeed);
    trunkAngle  = lerp(trunkAngle,  trunk  ? 70.f : 0.f, dt * trunkSpeed);
    hoodAngle   = lerp(hoodAngle,   hood   ? 60.f : 0.f, dt * hoodSpeed);

    // -- Blinker timer ---------------------------------------------------------
    if (leftBlinker || rightBlinker || hazard) {
        blinkerTimer += dt;
        if (blinkerTimer >= 0.5f) {
            blinkerTimer   = 0.f;
            blinkerVisible = !blinkerVisible;
        }
    } else {
        blinkerTimer   = 0.f;
        blinkerVisible = true;
    }
}
