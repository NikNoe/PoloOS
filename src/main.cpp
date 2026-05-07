#include "raylib.h"
#include "car/PoloCar.h"
#include "car/CarRenderer.h"
#include "scene/RoadMap.h"
#include "scene/Camera.h"
#include "world/DayNightCycle.h"
#include "ui/DebugPanel.h"
#include "road/RoadNetwork.h"
#include "road/RoadRenderer.h"
#include "network/SceneReceiver.h"
#include "traffic/TrafficAgent.h"
#include <vector>
#include <algorithm>

int main()
{
    const int SW = 1280, SH = 720;
    InitWindow(SW, SH, "PoloOS — Route 3D (raylib-proto)");
    SetTargetFPS(60);
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    std::vector<TrafficAgent> agents;

    PoloCar     car;
    CarRenderer renderer;
    RoadMap     road;
    CarCamera   camera;
    DebugPanel debugPanel;
    DayNightCycle dayNight;
    RoadNetwork  roadNet;
    RoadRenderer roadRend;
    SceneReceiver receiver;
    receiver.init("127.0.0.1", 5005);
    roadNet.load("assets/maps/city.json");


    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        bool accel = IsKeyDown(KEY_UP)    || IsKeyDown(KEY_W);
        bool brake = IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S);
        bool left  = IsKeyDown(KEY_RIGHT)  || IsKeyDown(KEY_A);
        bool right = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_D);
        //car.applyInput(accel, brake, left, right, dt);
        debugPanel.update(car, dayNight);

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
        if (IsKeyDown(KEY_N)) dayNight.setTimeScale(600.f);
        else dayNight.setTimeScale(60.f);

        car.update(dt);
        camera.update(car, dt);
        dayNight.update(dt);
        receiver.poll(dt);

        for (const auto& det : receiver.objects()) {
            // Transforme coordonnées relatives → monde
            float rad = car.heading * DEG2RAD;
            float wx = car.x + det.x * std::cos(rad) - det.z * std::sin(rad);
            float wz = car.z + det.x * std::sin(rad) + det.z * std::cos(rad);

            DetectedObject worldDet = det;
            worldDet.x = wx;
            worldDet.z = wz;

            bool found = false;
            for (auto& agent : agents) {
                float dx = agent.x() - worldDet.x;
                float dz = agent.z() - worldDet.z;
                if (agent.cls() == worldDet.cls &&
                    std::sqrt(dx*dx + dz*dz) < 5.f) {
                    agent.update(worldDet, dt);
                    found = true;
                    break;
                }
            }
            if (!found)
                agents.emplace_back(worldDet);
                printf("[Agent NEW] cls=%s x=%.1f z=%.1f ttl=%.2f\n",
                    worldDet.className.c_str(), worldDet.x, worldDet.z, worldDet.ttl);
                agents.emplace_back(worldDet);
        }

        
        // Supprime les agents morts
        agents.erase(
            std::remove_if(agents.begin(), agents.end(),
                        [](const TrafficAgent& a) { return !a.isAlive(); }),
            agents.end()
        );

        if (!agents.empty()) {
            printf("[Agents] Count: %zu | First: cls=%d x=%.1f z=%.1f ttl=%.2f\n",
                agents.size(),
                (int)agents[0].cls(),
                agents[0].x(),
                agents[0].z(),
                agents[0].ttl());
        }

        // Log temporaire — à supprimer après confirmation
        static int lastCount = 0;
        if (receiver.packetCount() != lastCount) {
            lastCount = receiver.packetCount();
            printf("[UDP] Paquet #%d | Objets: %zu\n",
                   lastCount,
                   receiver.objects().size());
        }

        BeginDrawing();
            ClearBackground(dayNight.skyColor());
            dayNight.drawSky();
            BeginMode3D(camera.get());
                roadRend.draw(roadNet, dayNight);
                renderer.draw(car);
                for (const auto& agent : agents)
                {
                    agent.draw();
                }
            EndMode3D();
            debugPanel.draw(car, dayNight, SW, SH);
            const char* labels[] = { "FOLLOW", "ORBIT", "HOOD" };
            DrawText(labels[camera.mode()], SW/2 - 30, SH - 30, 18, LIME);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}