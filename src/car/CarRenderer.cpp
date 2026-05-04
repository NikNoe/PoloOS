#include <string>
#include <string>
#include "CarRenderer.h"
#include <cmath>

// ─── CarRenderer.cpp ──────────────────────────────────────────────────────────

#ifndef DEG2RAD
#define DEG2RAD 0.0174532925f
#endif

// ── Positions locales des parties (mètres, repère voiture) ───────────────────
// Z+ = avant, Z- = arrière, X+ = droite, Y+ = haut

static const float WHEEL_FL_PX = -1.208f, WHEEL_FL_PY = 0.326f, WHEEL_FL_PZ = 0.0f;
static const float WHEEL_FR_PX =  1.353f, WHEEL_FR_PY = 0.326f, WHEEL_FR_PZ = 0.0f;
static const float WHEEL_RL_PX = -1.208f, WHEEL_RL_PY = 0.321f, WHEEL_RL_PZ = 0.0f;
static const float WHEEL_RR_PX =  1.354f, WHEEL_RR_PY = 0.321f, WHEEL_RR_PZ = 0.0f;

static const float DOOR_LF_PIVOT_X = -1.208f, DOOR_LF_PIVOT_Y = -0.717f;
static const float DOOR_RF_PIVOT_X = -1.208f, DOOR_RF_PIVOT_Y =  0.717f;
static const float TRUNK_PIVOT_X   =  1.675f, TRUNK_PIVOT_Z   =  1.015f;


// ─────────────────────────────────────────────────────────────────────────────

Model CarRenderer::loadPart(const std::string& name) {
    std::string path = "assets/models/" + name + ".glb";
    return LoadModel(path.c_str());
}

CarRenderer::CarRenderer() {
    m_body      = loadPart("body");
    m_doorLF    = loadPart("door_lf");
    m_doorLR    = loadPart("door_lr");
    m_doorRF    = loadPart("door_rf");
    m_doorRR    = loadPart("door_rr");
    m_trunk     = loadPart("trunk");
    m_wheelFL   = loadPart("wheel_fl");
    m_wheelFR   = loadPart("wheel_fr");
    m_wheelRL   = loadPart("wheel_rl");
    m_wheelRR   = loadPart("wheel_rr");
    m_headL     = loadPart("headlight_l");
    m_headR     = loadPart("headlight_r");
    m_tailL     = loadPart("taillight_l");
    m_tailR     = loadPart("taillight_r");
    m_blinkerFL = loadPart("blinker_fl");
    m_blinkerFR = loadPart("blinker_fr");
    m_blinkerRL = loadPart("blinker_rl");
    m_blinkerRR = loadPart("blinker_rr");
}

CarRenderer::~CarRenderer() {
    UnloadModel(m_body);
    UnloadModel(m_doorLF);  UnloadModel(m_doorLR);
    UnloadModel(m_doorRF);  UnloadModel(m_doorRR);
    UnloadModel(m_trunk);
    UnloadModel(m_wheelFL); UnloadModel(m_wheelFR);
    UnloadModel(m_wheelRL); UnloadModel(m_wheelRR);
    UnloadModel(m_headL);   UnloadModel(m_headR);
    UnloadModel(m_tailL);   UnloadModel(m_tailR);
    UnloadModel(m_blinkerFL); UnloadModel(m_blinkerFR);
    UnloadModel(m_blinkerRL); UnloadModel(m_blinkerRR);
}

// ── localToWorld ──────────────────────────────────────────────────────────────
Vector3 CarRenderer::localToWorld(const PoloCar& car, float lx, float ly, float lz) {
    float rad = car.heading * DEG2RAD;
    float s = std::sin(rad), c = std::cos(rad);
    return {
        car.x + c * lx + s * lz,
        ly,
        car.z - s * lx + c * lz
    };
}

// ── drawPart : partie fixe relative à la voiture ──────────────────────────────
void CarRenderer::drawPart(Model& model, const PoloCar& car,
                            float lx, float ly, float lz,
                            float ax, float ay, float az,
                            float extraAngle, Color tint)
{
    Vector3 pos = localToWorld(car, lx, ly, lz);
    // Rotation de base = cap voiture + rotation extra
    float totalAngle = car.heading + extraAngle;
    DrawModelEx(model, pos, { ax, ay, az }, totalAngle, { 1, 1, 1 }, tint);
}

// ── drawPivot : rotation autour d'un pivot local (portes, coffre) ─────────────
void CarRenderer::drawPivot(Model& model, const PoloCar& car,
                             float pivotLX, float pivotLY, float pivotLZ,
                             float rax, float ray, float raz,
                             float angle, Color tint)
{
    // On translate au pivot, on tourne, on dessine
    Vector3 pivot = localToWorld(car, pivotLX, pivotLY, pivotLZ);

    // Matrice : rotation voiture * rotation porte
    Matrix rotCar  = MatrixRotateY(car.heading * DEG2RAD);
    Matrix rotDoor = MatrixRotate({ rax, ray, raz }, angle * DEG2RAD);
    Matrix transform = MatrixMultiply(rotDoor, rotCar);

    model.transform = transform;
    DrawModel(model, pivot, 1.0f, tint);
    model.transform = MatrixIdentity(); // reset
}

// ── Point d'entrée ────────────────────────────────────────────────────────────
void CarRenderer::draw(const PoloCar& car) {
    drawBody  (car);
    drawDoors (car);
    drawTrunk (car);
    drawWheels(car);
    drawLights(car);
}

// ── Carrosserie ───────────────────────────────────────────────────────────────
void CarRenderer::drawBody(const PoloCar& car) {
    Vector3 pos = { car.x, 0.f, car.z };
    DrawModelEx(m_body, pos, { 0, 1, 0 }, car.heading, { 1, 1, 1 }, WHITE);
}

// ── Portes ────────────────────────────────────────────────────────────────────
void CarRenderer::drawDoors(const PoloCar& car) {
    Vector3 carPos = { car.x, 0.f, car.z };
    float   hRad   = car.heading * DEG2RAD;

    // Pivot local LF = charnière avant gauche
    auto animateDoor = [&](Model& model, float pivLX, float pivLZ,
                            float openAngle, float sign) {
        // Pivot en coordonnées monde
        float s = std::sin(hRad), c = std::cos(hRad);
        Vector3 pivot = {
            car.x + c * pivLX + s * pivLZ,
            0.f,
            car.z - s * pivLX + c * pivLZ
        };

        Matrix mCar  = MatrixRotateY(hRad);
        Matrix mOpen = MatrixRotateY(sign * openAngle * DEG2RAD);
        Matrix mTrs  = MatrixTranslate(-pivot.x, 0, -pivot.z);
        Matrix mTrsB = MatrixTranslate( pivot.x, 0,  pivot.z);

        // T^-1 * Ropen * Rcar * T
        Matrix t = MatrixMultiply(mTrs, MatrixMultiply(mOpen,
                   MatrixMultiply(mCar, mTrsB)));
        model.transform = t;
        DrawModel(model, {0,0,0}, 1.f, WHITE);
        model.transform = MatrixIdentity();
    };

    animateDoor(m_doorLF, -0.782f,  0.278f, car.doorFLAngle, -1.f);
    animateDoor(m_doorLR,  0.288f,  0.297f, car.doorRLAngle, -1.f);
    animateDoor(m_doorRF, -0.782f,  0.278f, car.doorFRAngle,  1.f);
    animateDoor(m_doorRR,  0.288f,  0.297f, car.doorRRAngle,  1.f);
}

// ── Coffre ────────────────────────────────────────────────────────────────────
void CarRenderer::drawTrunk(const PoloCar& car) {
    float hRad = car.heading * DEG2RAD;
    float s = std::sin(hRad), c = std::cos(hRad);

    float pivLX = 1.387f, pivLZ = 0.648f;
    Vector3 pivot = {
        car.x + c * pivLX + s * pivLZ,
        0.f,
        car.z - s * pivLX + c * pivLZ
    };

    Matrix mCar   = MatrixRotateY(hRad);
    Matrix mOpen  = MatrixRotateX(-car.trunkAngle * DEG2RAD);
    Matrix mTrs   = MatrixTranslate(-pivot.x, -pivot.y, -pivot.z);
    Matrix mTrsB  = MatrixTranslate( pivot.x,  pivot.y,  pivot.z);
    Matrix t = MatrixMultiply(mTrs, MatrixMultiply(mOpen,
               MatrixMultiply(mCar, mTrsB)));

    m_trunk.transform = t;
    DrawModel(m_trunk, {0,0,0}, 1.f, WHITE);
    m_trunk.transform = MatrixIdentity();
}

// ── Roues ─────────────────────────────────────────────────────────────────────
void CarRenderer::drawWheels(const PoloCar& car) {
    float hRad  = car.heading * DEG2RAD;
    float s = std::sin(hRad), c = std::cos(hRad);

    auto drawWheel = [&](Model& model, float lx, float ly, float lz, float steer) {
        Vector3 pos = {
            car.x + c * lx + s * lz,
            ly,
            car.z - s * lx + c * lz
        };
        Matrix mRoll  = MatrixRotateX(car.wheelRoll * DEG2RAD);
        Matrix mSteer = MatrixRotateY((car.heading + steer) * DEG2RAD);
        model.transform = MatrixMultiply(mRoll, mSteer);
        DrawModel(model, pos, 1.f, WHITE);
        model.transform = MatrixIdentity();
    };

    drawWheel(m_wheelFL, WHEEL_FL_PX, WHEEL_FL_PY, WHEEL_FL_PZ, car.wheelAngle);
    drawWheel(m_wheelFR, WHEEL_FR_PX, WHEEL_FR_PY, WHEEL_FR_PZ, car.wheelAngle);
    drawWheel(m_wheelRL, WHEEL_RL_PX, WHEEL_RL_PY, WHEEL_RL_PZ, 0.f);
    drawWheel(m_wheelRR, WHEEL_RR_PX, WHEEL_RR_PY, WHEEL_RR_PZ, 0.f);
}

// ── Phares et feux ────────────────────────────────────────────────────────────
void CarRenderer::drawLights(const PoloCar& car) {
    // Phares avant
    Color headCol = car.highBeam ? WHITE
                  : car.lowBeam  ? YELLOW
                  : DARKGRAY;
    drawPart(m_headL, car, -0.65f, 0.45f,  2.1f, 0, 1, 0, 0, headCol);
    drawPart(m_headR, car,  0.65f, 0.45f,  2.1f, 0, 1, 0, 0, headCol);

    // Feux arrière
    Color tailCol = (car.speed < -0.5f || car.handbrake) ? RED : Color{100,10,10,255};
    drawPart(m_tailL, car, -0.65f, 0.45f, -2.1f, 0, 1, 0, 0, tailCol);
    drawPart(m_tailR, car,  0.65f, 0.45f, -2.1f, 0, 1, 0, 0, tailCol);

    // Clignotants
    Color blinkOn  = ORANGE;
    Color blinkOff = Color{60, 40, 0, 255};

    bool lVis = (car.leftBlinker  || car.hazard) && car.blinkerVisible;
    bool rVis = (car.rightBlinker || car.hazard) && car.blinkerVisible;

    drawPart(m_blinkerFL, car, -0.72f, 0.4f,  2.0f, 0,1,0, 0, lVis ? blinkOn : blinkOff);
    drawPart(m_blinkerFR, car,  0.72f, 0.4f,  2.0f, 0,1,0, 0, rVis ? blinkOn : blinkOff);
    drawPart(m_blinkerRL, car, -0.72f, 0.4f, -2.0f, 0,1,0, 0, lVis ? blinkOn : blinkOff);
    drawPart(m_blinkerRR, car,  0.72f, 0.4f, -2.0f, 0,1,0, 0, rVis ? blinkOn : blinkOff);
}