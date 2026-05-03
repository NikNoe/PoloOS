#include "raylib.h"
#include "raymath.h"
#include "car/PoloCar.h"
#include "car/CarRenderer.h"
#include "scene/RoadMap.h"
#include "ui/HUD.h"
#include <cmath>

// ─── main.cpp ─────────────────────────────────────────────────────────────────

enum CameraMode { CAM_FOLLOW, CAM_ORBIT, CAM_HOOD };

int main()
{
    const int SW = 1280, SH = 720;
    InitWindow(SW, SH, "PoloOS — Route 3D (raylib-proto)");
    SetTargetFPS(60);

    // ── Objets ────────────────────────────────────────────────────────────────
    PoloCar     car;
    CarRenderer renderer;
    RoadMap     road;
    HUD         hud;

    // ── Caméra ────────────────────────────────────────────────────────────────
    Camera3D cam = {};
    cam.up         = { 0.f, 1.f, 0.f };
    cam.fovy       = 50.f;
    cam.projection = CAMERA_PERSPECTIVE;

    CameraMode camMode = CAM_FOLLOW;
    float orbitAngle   = 0.f;   // pour mode orbit
    float orbitDist    = 18.f;

    // ── Boucle principale ─────────────────────────────────────────────────────
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        // ── Inputs voiture ────────────────────────────────────────────────────
        bool accel = IsKeyDown(KEY_UP)   || IsKeyDown(KEY_W);
        bool brake = IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S);
        bool left  = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
        bool right = IsKeyDown(KEY_RIGHT)|| IsKeyDown(KEY_D);

        car.applyInput(accel, brake, left, right, dt);

        // Portes / coffre / capot
        if (IsKeyPressed(KEY_ONE))   car.doorFL = !car.doorFL;
        if (IsKeyPressed(KEY_TWO))   car.doorFR = !car.doorFR;
        if (IsKeyPressed(KEY_THREE)) car.doorRL = !car.doorRL;
        if (IsKeyPressed(KEY_FOUR))  car.doorRR = !car.doorRR;
        if (IsKeyPressed(KEY_T))     car.trunk  = !car.trunk;
        if (IsKeyPressed(KEY_O))     car.hood   = !car.hood;

        // Éclairage
        if (IsKeyPressed(KEY_L))     car.lowBeam      = !car.lowBeam;
        if (IsKeyPressed(KEY_H))     car.highBeam     = !car.highBeam;
        if (IsKeyPressed(KEY_Z))     car.leftBlinker  = !car.leftBlinker;
        if (IsKeyPressed(KEY_X))     car.rightBlinker = !car.rightBlinker;
        if (IsKeyPressed(KEY_W_UPPERCASE) || IsKeyPressed(KEY_KP_0))
            car.hazard = !car.hazard;

        // Frein à main
        if (IsKeyPressed(KEY_SPACE)) car.handbrake = !car.handbrake;

        // Mise à jour physique
        car.update(dt);

        // ── Caméra mode ───────────────────────────────────────────────────────
        if (IsKeyPressed(KEY_C)) {
            camMode = (CameraMode)((camMode + 1) % 3);
        }

        // Orbit : molette ou Q/E
        if (camMode == CAM_ORBIT) {
            orbitAngle += GetMouseWheelMove() * 3.f;
            if (IsKeyDown(KEY_Q)) orbitAngle -= 60.f * dt;
            if (IsKeyDown(KEY_E)) orbitAngle += 60.f * dt;
        }

        // Calcul position caméra selon mode
        float rad = car.heading * DEG2RAD;
        float s = std::sin(rad), c = std::cos(rad);

        switch (camMode) {
        case CAM_FOLLOW: {
            // Caméra arrière à hauteur réaliste
            cam.position = {
                car.x - s * 12.f,
                5.5f,
                car.z - c * 12.f
            };
            cam.target = { car.x + s * 4.f, 0.8f, car.z + c * 4.f };
            break;
        }
        case CAM_ORBIT: {
            float oRad = orbitAngle * DEG2RAD;
            cam.position = {
                car.x + std::sin(oRad) * orbitDist,
                7.f,
                car.z + std::cos(oRad) * orbitDist
            };
            cam.target = { car.x, 1.f, car.z };
            break;
        }
        case CAM_HOOD: {
            // Vue capot (à la première personne)
            cam.position = { car.x + s * 1.8f, 1.4f, car.z + c * 1.8f };
            cam.target   = { car.x + s * 10.f, 1.2f, car.z + c * 10.f };
            break;
        }
        }

        // ── Rendu ─────────────────────────────────────────────────────────────
        BeginDrawing();
            ClearBackground({ 10, 12, 20, 255 });

            BeginMode3D(cam);
                road.draw(car.x, car.z);
                renderer.draw(car);
            EndMode3D();

            // HUD 2D par-dessus
            hud.draw(car, SW, SH);

            // Mode caméra affiché
            const char* camLabels[] = { "FOLLOW", "ORBIT", "HOOD" };
            DrawText(camLabels[camMode], SW / 2 - 30, SH - 30, 18, LIME);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}