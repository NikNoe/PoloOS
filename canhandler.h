#ifndef CANHANDLER_H
#define CANHANDLER_H

#include <QObject>

class CanHandler : public QObject {
    Q_OBJECT

    // --- 1. ENGINE & TRANSMISSION ---
    Q_PROPERTY(int rpm READ rpm WRITE setRpm NOTIFY rpmChanged)
    Q_PROPERTY(int gear READ gear WRITE setGear NOTIFY gearChanged)
    Q_PROPERTY(double steeringAngle READ steeringAngle WRITE setSteeringAngle NOTIFY steeringAngleChanged)

    // --- 2. SAFETY & EXTERIOR ---
    Q_PROPERTY(bool handbrake READ handbrake WRITE setHandbrake NOTIFY handbrakeChanged)
    Q_PROPERTY(int blinkerStatus READ blinkerStatus WRITE setBlinkerStatus NOTIFY blinkerStatusChanged)
    Q_PROPERTY(bool highBeam READ highBeam WRITE setHighBeam NOTIFY highBeamChanged)
    Q_PROPERTY(int wiperLevel READ wiperLevel WRITE setWiperLevel NOTIFY wiperLevelChanged)

    // --- 3. BODY & SECURITY ---
    Q_PROPERTY(bool beltDriver READ beltDriver WRITE setBeltDriver NOTIFY beltDriverChanged)
    Q_PROPERTY(bool beltPassenger READ beltPassenger WRITE setBeltPassenger NOTIFY beltPassengerChanged)
    Q_PROPERTY(bool isLocked READ isLocked WRITE setIsLocked NOTIFY lockStatusChanged)
    Q_PROPERTY(bool doorFL READ doorFL WRITE setDoorFL NOTIFY doorFLChanged)
    Q_PROPERTY(bool doorFR READ doorFR WRITE setDoorFR NOTIFY doorFRChanged)
    Q_PROPERTY(bool doorRL READ doorRL WRITE setDoorRL NOTIFY doorRLChanged)
    Q_PROPERTY(bool doorRR READ doorRR WRITE setDoorRR NOTIFY doorRRChanged)
    Q_PROPERTY(bool trunk READ trunk WRITE setTrunk NOTIFY trunkChanged)
    Q_PROPERTY(int windowPos READ windowPos WRITE setWindowPos NOTIFY windowPosChanged)

    // --- 4. COMFORT & INTERIOR ---
    Q_PROPERTY(bool acActive READ acActive WRITE setAcActive NOTIFY acActiveChanged)
    Q_PROPERTY(bool interiorLight READ interiorLight WRITE setInteriorLight NOTIFY interiorLightChanged)
    Q_PROPERTY(bool windshieldHeater READ windshieldHeater WRITE setWindshieldHeater NOTIFY windshieldHeaterChanged)

public:
    explicit CanHandler(QObject *parent = nullptr) : QObject(parent) {}

    // --- GETTERS ---
    int rpm() const { return m_rpm; }
    int gear() const { return m_gear; }
    double steeringAngle() const { return m_steeringAngle; }
    bool handbrake() const { return m_handbrake; }
    int blinkerStatus() const { return m_blinkerStatus; }
    bool highBeam() const { return m_highBeam; }
    int wiperLevel() const { return m_wiperLevel; }
    bool beltDriver() const { return m_beltDriver; }
    bool beltPassenger() const { return m_beltPassenger; }
    bool isLocked() const { return m_isLocked; }
    bool doorFL() const { return m_doorFL; }
    bool doorFR() const { return m_doorFR; }
    bool doorRL() const { return m_doorRL; }
    bool doorRR() const { return m_doorRR; }
    bool trunk() const { return m_trunk; }
    int windowPos() const { return m_windowPos; }
    bool acActive() const { return m_acActive; }
    bool interiorLight() const { return m_interiorLight; }
    bool windshieldHeater() const { return m_windshieldHeater; }

public slots:
    // --- SETTERS WITH INDIVIDUAL SIGNALS ---
    void setRpm(int v) { if(m_rpm != v) { m_rpm = v; emit rpmChanged(); emit dataChanged(); } }
    void setGear(int v) { if(m_gear != v) { m_gear = v; emit gearChanged(); emit dataChanged(); } }
    void setSteeringAngle(double v) { if(m_steeringAngle != v) { m_steeringAngle = v; emit steeringAngleChanged(); emit dataChanged(); } }

    void setHandbrake(bool v) { if(m_handbrake != v) { m_handbrake = v; emit handbrakeChanged(); emit dataChanged(); } }
    void setBlinkerStatus(int v) { if(m_blinkerStatus != v) { m_blinkerStatus = v; emit blinkerStatusChanged(); emit dataChanged(); } }
    void setHighBeam(bool v) { if(m_highBeam != v) { m_highBeam = v; emit highBeamChanged(); emit dataChanged(); } }
    void setWiperLevel(int v) { if(m_wiperLevel != v) { m_wiperLevel = v; emit wiperLevelChanged(); emit dataChanged(); } }

    void setBeltDriver(bool v) { if(m_beltDriver != v) { m_beltDriver = v; emit beltDriverChanged(); emit dataChanged(); } }
    void setBeltPassenger(bool v) { if(m_beltPassenger != v) { m_beltPassenger = v; emit beltPassengerChanged(); emit dataChanged(); } }
    void setIsLocked(bool v) { if(m_isLocked != v) { m_isLocked = v; emit lockStatusChanged(); emit dataChanged(); } }
    void setDoorFL(bool v) { if(m_doorFL != v) { m_doorFL = v; emit doorFLChanged(); emit dataChanged(); } }
    void setDoorFR(bool v) { if(m_doorFR != v) { m_doorFR = v; emit doorFRChanged(); emit dataChanged(); } }
    void setDoorRL(bool v) { if(m_doorRL != v) { m_doorRL = v; emit doorRLChanged(); emit dataChanged(); } }
    void setDoorRR(bool v) { if(m_doorRR != v) { m_doorRR = v; emit doorRRChanged(); emit dataChanged(); } }
    void setTrunk(bool v) { if(m_trunk != v) { m_trunk = v; emit trunkChanged(); emit dataChanged(); } }
    void setWindowPos(int v) { if(m_windowPos != v) { m_windowPos = v; emit windowPosChanged(); emit dataChanged(); } }

    void setAcActive(bool v) { if(m_acActive != v) { m_acActive = v; emit acActiveChanged(); emit dataChanged(); } }
    void setInteriorLight(bool v) { if(m_interiorLight != v) { m_interiorLight = v; emit interiorLightChanged(); emit dataChanged(); } }
    void setWindshieldHeater(bool v) { if(m_windshieldHeater != v) { m_windshieldHeater = v; emit windshieldHeaterChanged(); emit dataChanged(); } }

signals:
    void dataChanged(); // Global signal
    void rpmChanged();
    void gearChanged();
    void steeringAngleChanged();
    void handbrakeChanged();
    void blinkerStatusChanged();
    void highBeamChanged();
    void wiperLevelChanged();
    void beltDriverChanged();
    void beltPassengerChanged();
    void lockStatusChanged();
    void doorFLChanged();
    void doorFRChanged();
    void doorRLChanged();
    void doorRRChanged();
    void trunkChanged();
    void windowPosChanged();
    void acActiveChanged();
    void interiorLightChanged();
    void windshieldHeaterChanged();

private:
    int m_rpm = 0;
    int m_gear = 1;
    double m_steeringAngle = 0.0;
    bool m_handbrake = true;
    int m_blinkerStatus = 0;
    bool m_highBeam = false;
    int m_wiperLevel = 0;
    bool m_beltDriver = false; // false = unbuckled
    bool m_beltPassenger = false;
    bool m_isLocked = true;
    bool m_doorFL = false;
    bool m_doorFR = false;
    bool m_doorRL = false;
    bool m_doorRR = false;
    bool m_trunk = false;
    int m_windowPos = 0;
    bool m_acActive = false;
    bool m_interiorLight = false;
    bool m_windshieldHeater = false;
};

#endif
