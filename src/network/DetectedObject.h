#pragma once
#include <string>

// ─── DetectedObject.h ─────────────────────────────────────────────────────────
// Struct partagée YOLO → Raylib.
// Même format que le JSON socket — zéro conversion nécessaire.
// ─────────────────────────────────────────────────────────────────────────────

enum class ObjectClass {
    CAR, TRUCK, BUS, MOTORCYCLE, BICYCLE,
    PEDESTRIAN, TRAFFIC_LIGHT, STOP_SIGN,
    UNKNOWN
};

struct DetectedObject {
    ObjectClass cls        = ObjectClass::UNKNOWN;
    std::string className;
    float       x          = 0.f;   // position monde latérale (m)
    float       z          = 0.f;   // position monde profondeur (m)
    float       heading    = 0.f;   // cap estimé (degrés)
    float       confidence = 0.f;   // 0.0 – 1.0
    float       distance   = 0.f;   // distance estimée (m)
    int         frame      = 0;
    float       timestamp  = 0.f;
    int trackId = -1;

    // Durée de vie — objet supprimé si pas mis à jour
    float       ttl        = 1.5f;  // secondes

    static ObjectClass fromString(const std::string& s) {
        if (s == "car")           return ObjectClass::CAR;
        if (s == "truck")         return ObjectClass::TRUCK;
        if (s == "bus")           return ObjectClass::BUS;
        if (s == "motorcycle")    return ObjectClass::MOTORCYCLE;
        if (s == "bicycle")       return ObjectClass::BICYCLE;
        if (s == "pedestrian")    return ObjectClass::PEDESTRIAN;
        if (s == "traffic_light") return ObjectClass::TRAFFIC_LIGHT;
        if (s == "stop_sign")     return ObjectClass::STOP_SIGN;
        return ObjectClass::UNKNOWN;
    }
};