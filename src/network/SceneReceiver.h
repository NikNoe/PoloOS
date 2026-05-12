#pragma once

/**
 * @file SceneReceiver.h
 * @brief Non-blocking UDP receiver for YOLO detection packets.
 *
 * Receives JSON packets from detector.py, parses them into DetectedObject
 * instances, merges them with existing objects and manages their TTL.
 * Must be polled every Raylib frame — never blocks.
 */

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

/**
 * @brief Receives and parses UDP detection packets from the Python YOLO pipeline.
 *
 * Opens a non-blocking UDP socket, reads one datagram per frame in poll(),
 * and exposes the merged list of live DetectedObject instances.
 */
class SceneReceiver {
public:
    /** @brief Constructs an uninitialised receiver. Call init() before use. */
    SceneReceiver();

    /** @brief Closes the UDP socket if open. */
    ~SceneReceiver();

    /**
     * @brief Opens and binds the UDP socket.
     * @param host Local address to bind (default "127.0.0.1").
     * @param port UDP port to listen on (default 5005).
     * @return True on success, false if socket creation or bind failed.
     */
    bool init(const std::string& host = "127.0.0.1", int port = 5005);

    /**
     * @brief Reads one pending UDP datagram and updates the object list.
     *
     * Non-blocking — returns immediately if no datagram is available.
     * Also decrements TTL of all tracked objects and removes expired ones.
     *
     * @param dt Time step since the last frame (seconds).
     */
    void poll(float dt);

    /** @brief Closes the UDP socket. */
    void close();

    /**
     * @brief Returns the current list of live detected objects.
     * @return Read-only reference to the internal object vector.
     */
    const std::vector<DetectedObject>& objects() const { return m_objects; }

    /**
     * @brief Returns true if the socket is open.
     * @return True when a valid file descriptor is held.
     */
    bool isConnected() const { return m_socket >= 0; }

    /**
     * @brief Returns the frame number from the last received packet.
     * @return Last parsed frame index.
     */
    int  lastFrame()   const { return m_lastFrame; }

    /**
     * @brief Returns the total number of packets received since init().
     * @return Cumulative packet counter.
     */
    int  packetCount() const { return m_packetCount; }

    /**
     * @brief Returns the ego-vehicle speed from the last packet.
     * @return Estimated speed in m/s as reported by detector.py.
     */
    float egoSpeed()        const { return m_egoSpeed; }

    /**
     * @brief Returns the ego-vehicle heading delta from the last packet.
     * @return Heading change in degrees as reported by detector.py.
     */
    float egoHeadingDelta() const { return m_egoHeadingDelta; }

private:
    int   m_socket      = -1;  ///< UDP socket file descriptor.
    int   m_lastFrame   = 0;   ///< Frame number from last received packet.
    int   m_packetCount = 0;   ///< Total number of packets received.
    float m_egoSpeed        = 0.f; ///< Ego speed from last packet (m/s).
    float m_egoHeadingDelta = 0.f; ///< Ego heading delta from last packet (degrees).

    std::vector<DetectedObject> m_objects; ///< Live object list.

    /**
     * @brief Parses a raw JSON string into DetectedObject instances.
     * @param json Raw JSON string from the UDP datagram.
     */
    void        parsePacket(const std::string& json);

    /**
     * @brief Extracts a string value from a flat JSON object.
     * @param json JSON string to search.
     * @param key  Key name to look up.
     * @return The string value, or empty string if not found.
     */
    std::string extractString(const std::string& json, const std::string& key);

    /**
     * @brief Extracts a float value from a flat JSON object.
     * @param json JSON string to search.
     * @param key  Key name to look up.
     * @return The float value, or 0.0 if not found or parse error.
     */
    float       extractFloat (const std::string& json, const std::string& key);

    /**
     * @brief Extracts an integer value from a flat JSON object.
     * @param json JSON string to search.
     * @param key  Key name to look up.
     * @return The integer value, or 0 if not found or parse error.
     */
    int         extractInt   (const std::string& json, const std::string& key);

    /**
     * @brief Decrements TTL of all objects and removes expired ones.
     * @param dt Time step since the last frame (seconds).
     */
    void        updateTTL(float dt);
};
