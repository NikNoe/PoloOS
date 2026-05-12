#pragma once

/**
 * @file DetectedObject.h
 * @brief Shared data structure between the YOLO detector (Python) and the 3D engine (Raylib).
 *
 * The layout matches the UDP socket JSON format exactly --
 * no conversion is needed between the two processes.
 */

#include <string>

/**
 * @brief Object categories recognised by the YOLO detector.
 */
enum class ObjectClass {
    CAR,           ///< Passenger car.
    TRUCK,         ///< Truck or lorry.
    BUS,           ///< Bus.
    MOTORCYCLE,    ///< Motorcycle.
    BICYCLE,       ///< Bicycle.
    PEDESTRIAN,    ///< Pedestrian.
    TRAFFIC_LIGHT, ///< Traffic light.
    STOP_SIGN,     ///< Stop sign.
    UNKNOWN        ///< Unrecognised class.
};

/**
 * @brief Represents a single object detected by the YOLO pipeline.
 *
 * Contains the estimated world-space position, object class, confidence score,
 * a per-track identifier for inter-frame association, and a time-to-live (TTL).
 */
struct DetectedObject {
    ObjectClass cls        = ObjectClass::UNKNOWN; ///< Object class enum value.
    std::string className;                          ///< Class name as received in JSON.
    float       x          = 0.f;   ///< Lateral world position (metres).
    float       z          = 0.f;   ///< Depth world position (metres).
    float       heading    = 0.f;   ///< Estimated heading (degrees).
    float       confidence = 0.f;   ///< YOLO confidence score (0.0-1.0).
    float       distance   = 0.f;   ///< Estimated distance from ego vehicle (metres).
    int         frame      = 0;     ///< Source frame number.
    float       timestamp  = 0.f;   ///< Packet timestamp (seconds).
    int         trackId    = -1;    ///< Inter-frame tracking ID (-1 = unassigned).

    float       ttl        = 1.5f;  ///< Time-to-live -- object removed when ttl <= 0.

    /**
     * @brief Converts a class name string to the corresponding enum value.
     * @param s Class name string as received in JSON (e.g. "car", "pedestrian").
     * @return Matching @ref ObjectClass value, or UNKNOWN if not recognised.
     */
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
