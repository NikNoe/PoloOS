#pragma once
#include "DetectedObject.h"
#include <vector>
#include <string>
#include <functional>

#ifdef _WIN32
  #include <winsock2.h>
#else
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <unistd.h>
  #include <fcntl.h>
#endif

// ─── SceneReceiver.h ──────────────────────────────────────────────────────────
// Reçoit les paquets UDP depuis detector.py
// Parse le JSON et expose les DetectedObject[]
// Non-bloquant — appelé à chaque frame Raylib
// ─────────────────────────────────────────────────────────────────────────────

class SceneReceiver {
public:
    SceneReceiver();
    ~SceneReceiver();

    bool init(const std::string& host = "127.0.0.1", int port = 5005);
    void poll(float dt);   // appeler chaque frame — non-bloquant
    void close();

    const std::vector<DetectedObject>& objects() const { return m_objects; }
    bool isConnected() const { return m_socket >= 0; }
    int  lastFrame()   const { return m_lastFrame; }
    int  packetCount() const { return m_packetCount; }
    float egoSpeed()        const { return m_egoSpeed; }
    float egoHeadingDelta() const { return m_egoHeadingDelta; }



private:
    int    m_socket     = -1;
    int    m_lastFrame  = 0;
    int    m_packetCount = 0;
    float m_egoSpeed        = 0.f;
    float m_egoHeadingDelta = 0.f;

    std::vector<DetectedObject> m_objects;

    // Parser JSON minimal — sans dépendance externe
    void        parsePacket(const std::string& json);
    std::string extractString(const std::string& json,
                              const std::string& key);
    float       extractFloat (const std::string& json,
                              const std::string& key);
    int         extractInt   (const std::string& json,
                              const std::string& key);

    // Nettoyage des objets expirés
    void        updateTTL(float dt);
};