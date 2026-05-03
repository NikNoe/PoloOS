#include "raylib.h"
#include "car/PoloCar.h"
#include "car/CarRenderer.h"
#include "scene/RoadMap.h"
#include "scene/Camera.h"
#include "ui/HUD.h"

int main()
{
    const int SW = 1280, SH = 720;
    InitWindow(SW, SH, "PoloOS — Route 3D (raylib-proto)");
    SetTargetFPS(60);
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    PoloCar     car;
    CarRenderer renderer;
    RoadMap     road;
    CarCamera   camera;
    HUD         hud;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        bool accel = IsKeyDown(KEY_UP)    || IsKeyDown(KEY_W);
        bool brake = IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S);
        bool left  = IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A);
        bool right = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
        car.applyInput(accel, brake, left, right, dt);

        if (IsKeyPressed(KEY_ONE))   car.doorFL = !car.doorFL;
        if (IsKeyPressed(KEY_TWO))   car.doorFR = !car.doorFR;
        if (IsKeyPressed(KEY_THREE)) car.doorRL = !car.doorRL;
        if (IsKeyPressed(KEY_FOUR))  car.doorRR = !car.doorRR;
        if (IsKeyPressed(KEY_T))     car.trunk  = !car.trunk;
        if (IsKeyPressed(KEY_O))     car.hood   = !car.hood;
        if (IsKeyPressed(KEY_L))     car.lowBeam      = !car.lowBeam;
        if (IsKeyPressed(KEY_H))     car.highBeam     = !car.highBeam;
        if (IsKeyPressed(KEY_Z))     car.leftBlinker  = !car.leftBlinker;
        if (IsKeyPressed(KEY_X))     car.rightBlinker = !car.rightBlinker;
        if (IsKeyPressed(KEY_GRAVE)) car.hazard       = !car.hazard;
        if (IsKeyPressed(KEY_SPACE)) car.handbrake    = !car.handbrake;

        car.update(dt);
        camera.update(car, dt);

        BeginDrawing();
            ClearBackground({ 10, 12, 20, 255 });
            BeginMode3D(camera.get());
                road.draw(car.x, car.z);
                renderer.draw(car);
            EndMode3D();
            hud.draw(car, SW, SH);
            const char* labels[] = { "FOLLOW", "ORBIT", "HOOD" };
            DrawText(labels[camera.mode()], SW/2 - 30, SH - 30, 18, LIME);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}