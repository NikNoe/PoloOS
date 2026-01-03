#ifndef CANHANDLER_H
#define CANHANDLER_H

#include <QObject>

class CanHandler : public QObject {
    Q_OBJECT

    // --- 1. ENGINE & TRANSMISSION ---
    Q_PROPERTY(int rpm READ rpm WRITE setRpm NOTIFY dataChanged)
    Q_PROPERTY(int gear READ gear WRITE setGear NOTIFY dataChanged)
    Q_PROPERTY(double steeringAngle READ steeringAngle WRITE setSteeringAngle NOTIFY dataChanged)

    // --- 2. SAFETY & EXTERIOR ---
    Q_PROPERTY(bool handbrake READ handbrake WRITE setHandbrake NOTIFY dataChanged)
    Q_PROPERTY(int blinkerStatus READ blinkerStatus WRITE setBlinkerStatus NOTIFY dataChanged)
    Q_PROPERTY(bool highBeam READ highBeam WRITE setHighBeam NOTIFY dataChanged)
    Q_PROPERTY(int wiperLevel READ wiperLevel WRITE setWiperLevel NOTIFY dataChanged)

    // --- 3. BODY & SECURITY ---
    Q_PROPERTY(bool isLocked READ isLocked WRITE setIsLocked NOTIFY dataChanged)
    Q_PROPERTY(bool doorFL READ doorFL WRITE setDoorFL NOTIFY dataChanged)
    Q_PROPERTY(bool doorFR READ doorFR WRITE setDoorFR NOTIFY dataChanged)
    Q_PROPERTY(int windowPos READ windowPos WRITE setWindowPos NOTIFY dataChanged)

    // --- 4. COMFORT & INTERIOR ---
    Q_PROPERTY(bool acActive READ acActive WRITE setAcActive NOTIFY dataChanged)
    Q_PROPERTY(bool interiorLight READ interiorLight WRITE setInteriorLight NOTIFY dataChanged)
    Q_PROPERTY(bool windshieldHeater READ windshieldHeater WRITE setWindshieldHeater NOTIFY dataChanged)

public:
    explicit CanHandler(QObject *parent = nullptr) : QObject(parent) {}

    // --- GETTERS ---
    // Engine/Drive
    int rpm() const { return m_rpm; }
    int gear() const { return m_gear; }
    double steeringAngle() const { return m_steeringAngle; }

    // Safety/Lights
    bool handbrake() const { return m_handbrake; }
    int blinkerStatus() const { return m_blinkerStatus; }
    bool highBeam() const { return m_highBeam; }
    int wiperLevel() const { return m_wiperLevel; }

    // Body
    bool isLocked() const { return m_isLocked; }
    bool doorFL() const { return m_doorFL; }
    bool doorFR() const { return m_doorFR; }
    int windowPos() const { return m_windowPos; }

    // Comfort
    bool acActive() const { return m_acActive; }
    bool interiorLight() const { return m_interiorLight; }
    bool windshieldHeater() const { return m_windshieldHeater; }

public slots:
    // --- SETTERS (Used by CockpitWindow) ---
    void setRpm(int v) { if(m_rpm != v) { m_rpm = v; emit dataChanged(); } }
    void setGear(int v) { if(m_gear != v) { m_gear = v; emit dataChanged(); } }
    void setSteeringAngle(double v) { if(m_steeringAngle != v) { m_steeringAngle = v; emit dataChanged(); } }

    void setHandbrake(bool v) { if(m_handbrake != v) { m_handbrake = v; emit dataChanged(); } }
    void setBlinkerStatus(int v) { if(m_blinkerStatus != v) { m_blinkerStatus = v; emit dataChanged(); } }
    void setHighBeam(bool v) { if(m_highBeam != v) { m_highBeam = v; emit dataChanged(); } }
    void setWiperLevel(int v) { if(m_wiperLevel != v) { m_wiperLevel = v; emit dataChanged(); } }

    void setIsLocked(bool v) { if(m_isLocked != v) { m_isLocked = v; emit dataChanged(); } }
    void setDoorFL(bool v) { if(m_doorFL != v) { m_doorFL = v; emit dataChanged(); } }
    void setDoorFR(bool v) { if(m_doorFR != v) { m_doorFR = v; emit dataChanged(); } }
    void setWindowPos(int v) { if(m_windowPos != v) { m_windowPos = v; emit dataChanged(); } }

    void setAcActive(bool v) { if(m_acActive != v) { m_acActive = v; emit dataChanged(); } }
    void setInteriorLight(bool v) { if(m_interiorLight != v) { m_interiorLight = v; emit dataChanged(); } }
    void setWindshieldHeater(bool v) { if(m_windshieldHeater != v) { m_windshieldHeater = v; emit dataChanged(); } }

signals:
    void dataChanged();

private:
    // Engine/Drive
    int m_rpm = 0;
    int m_gear = 1;
    double m_steeringAngle = 0.0;

    // Safety/Lights
    bool m_handbrake = true;
    int m_blinkerStatus = 0;
    bool m_highBeam = false;
    int m_wiperLevel = 0;

    // Body
    bool m_isLocked = true;
    bool m_doorFL = false;
    bool m_doorFR = false;
    int m_windowPos = 0;

    // Comfort
    bool m_acActive = false;
    bool m_interiorLight = false;
    bool m_windshieldHeater = false;
};

#endif
