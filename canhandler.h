#ifndef CANHANDLER_H
#define CANHANDLER_H

#include <QObject>

class CanHandler : public QObject {
    Q_OBJECT

    // --- Properties with READ and WRITE ---
    Q_PROPERTY(int rpm READ rpm WRITE setRpm NOTIFY dataChanged)
    Q_PROPERTY(double steeringAngle READ steeringAngle WRITE setSteeringAngle NOTIFY dataChanged)
    Q_PROPERTY(bool handbrake READ handbrake WRITE setHandbrake NOTIFY dataChanged)
    Q_PROPERTY(int blinkerStatus READ blinkerStatus WRITE setBlinkerStatus NOTIFY dataChanged)
    Q_PROPERTY(bool highBeam READ highBeam WRITE setHighBeam NOTIFY dataChanged)
    Q_PROPERTY(bool acActive READ acActive WRITE setAcActive NOTIFY dataChanged)
    Q_PROPERTY(int windowPos READ windowPos WRITE setWindowPos NOTIFY dataChanged)
    Q_PROPERTY(bool doorFL READ doorFL WRITE setDoorFL NOTIFY dataChanged)
    Q_PROPERTY(bool doorFR READ doorFR WRITE setDoorFR NOTIFY dataChanged)
    Q_PROPERTY(bool isLocked READ isLocked WRITE setIsLocked NOTIFY dataChanged)
    Q_PROPERTY(bool interiorLight READ interiorLight WRITE setInteriorLight NOTIFY dataChanged)
    Q_PROPERTY(bool windshieldHeater READ windshieldHeater WRITE setWindshieldHeater NOTIFY dataChanged)
    Q_PROPERTY(int wiperLevel READ wiperLevel WRITE setWiperLevel NOTIFY dataChanged) // 0=Off, 1=Int, 2=Low, 3=High
    Q_PROPERTY(int gear READ gear WRITE setGear NOTIFY dataChanged) // 1, 2, 3, 4, 5

public:
    explicit CanHandler(QObject *parent = nullptr) : QObject(parent) {}

    // --- GETTERS ---
    int rpm() const { return m_rpm; }
    double steeringAngle() const { return m_steeringAngle; }
    bool handbrake() const { return m_handbrake; }
    int blinkerStatus() const { return m_blinkerStatus; }
    bool highBeam() const { return m_highBeam; }
    bool acActive() const { return m_acActive; }
    int windowPos() const { return m_windowPos; }
    bool doorFL() const { return m_doorFL; }
    bool doorFR() const { return m_doorFR; }
    bool isLocked() const { return m_isLocked; }
    bool interiorLight() const { return m_interiorLight; }
    bool windshieldHeater()  const {return m_windshieldHeater; }
    bool wiperLevel() const{ return m_wiperLevel; }
    bool gear() const{ return m_wiperLevel; }

public slots:
    // --- SETTERS (The Simulator uses these) ---
    void setRpm(int v) { if(m_rpm != v) { m_rpm = v; emit dataChanged(); } }
    void setSteeringAngle(double v) { if(m_steeringAngle != v) { m_steeringAngle = v; emit dataChanged(); } }
    void setHandbrake(bool v) { if(m_handbrake != v) { m_handbrake = v; emit dataChanged(); } }
    void setBlinkerStatus(int v) { if(m_blinkerStatus != v) { m_blinkerStatus = v; emit dataChanged(); } }
    void setHighBeam(bool v) { if(m_highBeam != v) { m_highBeam = v; emit dataChanged(); } }
    void setAcActive(bool v) { if(m_acActive != v) { m_acActive = v; emit dataChanged(); } }
    void setWindowPos(int v) { if(m_windowPos != v) { m_windowPos = v; emit dataChanged(); } }
    void setDoorFL(bool v) { if(m_doorFL != v) { m_doorFL = v; emit dataChanged(); } }
    void setDoorFR(bool v) { if(m_doorFR != v) { m_doorFR = v; emit dataChanged(); } }
    void setIsLocked(bool v) { if(m_isLocked != v) { m_isLocked = v; emit dataChanged(); } }
    void setInteriorLight(bool v) { if(m_interiorLight != v) { m_interiorLight = v; emit dataChanged(); } }
    void setWindshieldHeater(bool v) { if(m_windshieldHeater != v) { m_windshieldHeater = v; emit dataChanged(); } }
    void setWiperLevel(int v) { if(m_wiperLevel != v) { m_wiperLevel = v; emit dataChanged(); } }
    void setGear(int v) { if(m_gear != v) { m_gear = v; emit dataChanged(); } }

signals:
    void dataChanged();

private:
    int m_rpm = 0, m_blinkerStatus = 0, m_windowPos = 0;
    double m_steeringAngle = 0.0;
    bool m_handbrake = true, m_highBeam = false, m_acActive = false, m_isLocked = true;
    bool m_doorFL = false, m_doorFR = false;
    bool m_interiorLight = false;
    bool m_windshieldHeater = false;
    int m_wiperLevel = 0;
    int m_gear = 1;
};

#endif
