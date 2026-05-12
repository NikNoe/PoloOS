/**
 * @file SceneReceiver.cpp
 * @brief Implementation of the UDP receiver and minimal JSON parser.
 */

#include "SceneReceiver.h"
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <errno.h>
#include <sys/time.h>
#include <fcntl.h>

SceneReceiver::SceneReceiver() {}

SceneReceiver::~SceneReceiver() { close(); }

bool SceneReceiver::init(const std::string& host, int port) {
    m_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_socket < 0) {
        printf("[SceneReceiver] Socket creation error\n");
        return false;
    }

    int reuse = 1;
    setsockopt(m_socket, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));
    setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    // Set non-blocking mode
#ifndef _WIN32
    int flags = fcntl(m_socket, F_GETFL, 0);
    fcntl(m_socket, F_SETFL, flags | O_NONBLOCK);
    printf("[SceneReceiver] Non-blocking socket: flags=%d\n", fcntl(m_socket, F_GETFL, 0));
#endif

    struct sockaddr_in addr{};
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(m_socket, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        printf("[SceneReceiver] Bind error on port %d\n", port);
        return false;
    }

    printf("[SceneReceiver] Listening on UDP %s:%d\n", host.c_str(), port);
    return true;
}

void SceneReceiver::poll(float dt) {
    if (m_socket < 0) return;

    updateTTL(dt);

    char buf[65536];
    struct sockaddr_in sender{};
    socklen_t senderLen = sizeof(sender);

    int n = recvfrom(m_socket, buf, sizeof(buf)-1, 0,
                 (struct sockaddr*)&sender, &senderLen);

    if (n > 0) {
        buf[n] = '\0';
        printf("[SceneReceiver] Packet received: %d bytes\n", n);
        parsePacket(std::string(buf, n));
        m_packetCount++;
    }
}

// -- Minimal JSON parser -------------------------------------------------------

std::string SceneReceiver::extractString(const std::string& json,
                                          const std::string& key) {
    auto pos = json.find("\"" + key + "\"");
    if (pos == std::string::npos) return "";
    auto q1 = json.find('"', json.find(':', pos) + 1);
    if (q1 == std::string::npos) return "";
    auto q2 = json.find('"', q1 + 1);
    if (q2 == std::string::npos) return "";
    return json.substr(q1 + 1, q2 - q1 - 1);
}

float SceneReceiver::extractFloat(const std::string& json,
                                   const std::string& key) {
    auto pos = json.find("\"" + key + "\"");
    if (pos == std::string::npos) return 0.f;
    auto colon = json.find(':', pos);
    if (colon == std::string::npos) return 0.f;
    try { return std::stof(json.substr(colon + 1)); }
    catch (...) { return 0.f; }
}

int SceneReceiver::extractInt(const std::string& json,
                               const std::string& key) {
    auto pos = json.find("\"" + key + "\"");
    if (pos == std::string::npos) return 0;
    auto colon = json.find(':', pos);
    if (colon == std::string::npos) return 0;
    try { return std::stoi(json.substr(colon + 1)); }
    catch (...) { return 0; }
}

void SceneReceiver::parsePacket(const std::string& json) {
    m_lastFrame = extractInt(json, "frame");

    // Ego motion block
    auto egoStart = json.find("\"ego\"");
    if (egoStart != std::string::npos) {
        auto egoEnd = json.find('}', egoStart);
        std::string egoBlock = json.substr(egoStart, egoEnd - egoStart);
        m_egoSpeed        = extractFloat(egoBlock, "speed");
        m_egoHeadingDelta = extractFloat(egoBlock, "heading_delta");
    }

    float ts = extractFloat(json, "timestamp");

    // Find the "objects" array
    auto objStart = json.find("\"objects\"");
    if (objStart == std::string::npos) return;

    auto arrStart = json.find('[', objStart);
    auto arrEnd   = json.find(']', arrStart);
    if (arrStart == std::string::npos || arrEnd == std::string::npos) return;

    std::string arr = json.substr(arrStart + 1, arrEnd - arrStart - 1);

    // Parse each { ... } object block
    std::vector<DetectedObject> newObjects;
    size_t pos = 0;

    while ((pos = arr.find('{', pos)) != std::string::npos) {
        auto end = arr.find('}', pos);
        if (end == std::string::npos) break;

        std::string obj = arr.substr(pos, end - pos + 1);

        DetectedObject det;
        det.className  = extractString(obj, "class");
        det.cls        = DetectedObject::fromString(det.className);
        det.x          = extractFloat(obj, "x");
        det.z          = extractFloat(obj, "z");
        det.heading    = extractFloat(obj, "heading");
        det.confidence = extractFloat(obj, "confidence");
        det.distance   = extractFloat(obj, "distance");
        det.trackId    = extractInt(obj, "id");
        det.frame      = m_lastFrame;
        det.timestamp  = ts;
        det.ttl        = 1.5f;

        if (det.cls != ObjectClass::UNKNOWN)
            newObjects.push_back(det);

        pos = end + 1;
    }

    // Merge with existing objects to avoid flickering
    for (auto& newObj : newObjects) {
        bool found = false;
        for (auto& existing : m_objects) {
            float dx = existing.x - newObj.x;
            float dz = existing.z - newObj.z;
            float dist = std::sqrt(dx*dx + dz*dz);

            // Same object if same class and distance < 5 m
            if (existing.cls == newObj.cls && dist < 5.f) {
                // Smooth position update
                existing.x          = existing.x * 0.3f + newObj.x * 0.7f;
                existing.z          = existing.z * 0.3f + newObj.z * 0.7f;
                existing.confidence = newObj.confidence;
                existing.ttl        = 1.5f;
                found = true;
                break;
            }
        }
        if (!found)
            m_objects.push_back(newObj);
    }
}

void SceneReceiver::updateTTL(float dt) {
    for (auto& obj : m_objects)
        obj.ttl -= dt;

    m_objects.erase(
        std::remove_if(m_objects.begin(), m_objects.end(),
                       [](const DetectedObject& o) { return o.ttl <= 0.f; }),
        m_objects.end()
    );
}

void SceneReceiver::close() {
    if (m_socket >= 0) {
#ifdef _WIN32
        closesocket(m_socket);
#else
        ::close(m_socket);
#endif
        m_socket = -1;
    }
}
