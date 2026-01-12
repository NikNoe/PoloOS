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
    Q_PROPERTY(bool beltDriver READ beltDriver WRITE setBeltDriver NOTIFY beltDriverChanged)
    Q_PROPERTY(bool beltPassenger READ beltPassenger WRITE setBeltPassenger NOTIFY beltPassengerChanged)

    // --- 5. CHASSIS & DYNAMICS ---
    Q_PROPERTY(double wheelFL READ wheelFL WRITE setWheelFL NOTIFY wheelSpeedChanged)
    Q_PROPERTY(double wheelFR READ wheelFR WRITE setWheelFR NOTIFY wheelSpeedChanged)
    Q_PROPERTY(double wheelRL READ wheelRL WRITE setWheelRL NOTIFY wheelSpeedChanged)
    Q_PROPERTY(double wheelRR READ wheelRR WRITE setWheelRR NOTIFY wheelSpeedChanged)
    Q_PROPERTY(bool absActive READ absActive WRITE setAbsActive NOTIFY safetyChanged)
    Q_PROPERTY(bool espActive READ espActive WRITE setEspActive NOTIFY safetyChanged)
    Q_PROPERTY(bool tractionActive READ tractionActive WRITE setTractionActive NOTIFY safetyChanged)
    Q_PROPERTY(bool brakePressed READ brakePressed WRITE setBrakePressed NOTIFY brakeChanged)


    // --- ENGINE METRICS (Real-time) ---
    Q_PROPERTY(int engineLoad READ engineLoad WRITE setEngineLoad NOTIFY engineMetricChanged)
    Q_PROPERTY(int throttlePos READ throttlePos WRITE setThrottlePos NOTIFY engineMetricChanged)
    Q_PROPERTY(int pedalPos READ pedalPos WRITE setPedalPos NOTIFY engineMetricChanged)
    Q_PROPERTY(double torqueActual READ torqueActual WRITE setTorqueActual NOTIFY engineMetricChanged)
    Q_PROPERTY(double torqueRequest READ torqueRequest WRITE setTorqueRequest NOTIFY engineMetricChanged)

    // --- STATUS & FLAGS ---
    Q_PROPERTY(bool idleState READ idleState WRITE setIdleState NOTIFY engineFlagChanged)
    Q_PROPERTY(bool cruiseActive READ cruiseActive WRITE setCruiseActive NOTIFY engineFlagChanged)
    Q_PROPERTY(bool limpMode READ limpMode WRITE setLimpMode NOTIFY engineFlagChanged)
    Q_PROPERTY(bool overheat READ overheat WRITE setOverheat NOTIFY engineFlagChanged)

    // --- CONSUMPTION ---
    Q_PROPERTY(double fuelInst READ fuelInst WRITE setFuelInst NOTIFY fuelChanged)
    Q_PROPERTY(double fuelAvg READ fuelAvg WRITE setFuelAvg NOTIFY fuelChanged)

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
    bool beltDriver() const { return m_beltDriver; }
    bool beltPassenger() const { return m_beltPassenger; }
    double wheelFL() const { return m_wheelFL; }
    double wheelFR() const { return m_wheelFR; }
    double wheelRL() const { return m_wheelRL; }
    double wheelRR() const { return m_wheelRR; }
    bool absActive() const { return m_absActive; }
    bool espActive() const { return m_espActive; }
    bool tractionActive() const { return m_tractionActive; }
    bool brakePressed() const { return m_brakePressed; }
    int engineLoad() const { return m_engineLoad; }
    int throttlePos() const { return m_throttlePos; }
    int pedalPos() const { return m_pedalPos; }
    double torqueActual() const { return m_torqueActual; }
    double torqueRequest() const { return m_torqueRequest; }
    bool idleState() const { return m_idleState; }
    bool cruiseActive() const { return m_cruiseActive; }
    bool limpMode() const { return m_limpMode; }
    bool overheat() const { return m_overheat; }
    double fuelInst() const { return m_fuelInst; }
    double fuelAvg() const { return m_fuelAvg; }

public slots:
    // --- SETTERS ---
    void setRpm(int v) { if(m_rpm != v) { m_rpm = v; emit rpmChanged(); emit dataChanged(); } }
    void setGear(int v) { if(m_gear != v) { m_gear = v; emit gearChanged(); emit dataChanged(); } }
    void setSteeringAngle(double v) { if(m_steeringAngle != v) { m_steeringAngle = v; emit steeringAngleChanged(); emit dataChanged(); } }
    void setHandbrake(bool v) { if(m_handbrake != v) { m_handbrake = v; emit handbrakeChanged(); emit dataChanged(); } }
    void setBlinkerStatus(int v) { if(m_blinkerStatus != v) { m_blinkerStatus = v; emit blinkerStatusChanged(); emit dataChanged(); } }
    void setHighBeam(bool v) { if(m_highBeam != v) { m_highBeam = v; emit highBeamChanged(); emit dataChanged(); } }
    void setWiperLevel(int v) { if(m_wiperLevel != v) { m_wiperLevel = v; emit wiperLevelChanged(); emit dataChanged(); } }
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
    void setBeltDriver(bool v) { if(m_beltDriver != v) { m_beltDriver = v; emit beltDriverChanged(); emit dataChanged(); } }
    void setBeltPassenger(bool v) { if(m_beltPassenger != v) { m_beltPassenger = v; emit beltPassengerChanged(); emit dataChanged(); } }

    // Chassis Setters
    void setWheelFL(double v) { if(m_wheelFL != v) { m_wheelFL = v; emit wheelSpeedChanged(); } }
    void setWheelFR(double v) { if(m_wheelFR != v) { m_wheelFR = v; emit wheelSpeedChanged(); } }
    void setWheelRL(double v) { if(m_wheelRL != v) { m_wheelRL = v; emit wheelSpeedChanged(); } }
    void setWheelRR(double v) { if(m_wheelRR != v) { m_wheelRR = v; emit wheelSpeedChanged(); } }
    void setAbsActive(bool v) { if(m_absActive != v) { m_absActive = v; emit safetyChanged(); } }
    void setEspActive(bool v) { if(m_espActive != v) { m_espActive = v; emit safetyChanged(); } }
    void setTractionActive(bool v) { if(m_tractionActive != v) { m_tractionActive = v; emit safetyChanged(); } }
    void setBrakePressed(bool v) { if(m_brakePressed != v) { m_brakePressed = v; emit brakeChanged(); } }

    // engine
    void setEngineLoad(int v) {
        if(m_engineLoad != v) { m_engineLoad = v; emit engineMetricChanged(); }
    }
    void setThrottlePos(int v) {
        if(m_throttlePos != v) { m_throttlePos = v; emit engineMetricChanged(); }
    }
    void setPedalPos(int v) {
        if(m_pedalPos != v) { m_pedalPos = v; emit engineMetricChanged(); }
    }
    void setTorqueActual(double v) {
        if(m_torqueActual != v) { m_torqueActual = v; emit engineMetricChanged(); }
    }
    void setTorqueRequest(double v) {
        if(m_torqueRequest != v) { m_torqueRequest = v; emit engineMetricChanged(); }
    }

    void setIdleState(bool v) {
        if(m_idleState != v) { m_idleState = v; emit engineFlagChanged(); }
    }
    void setCruiseActive(bool v) {
        if(m_cruiseActive != v) { m_cruiseActive = v; emit engineFlagChanged(); }
    }
    void setLimpMode(bool v) {
        if(m_limpMode != v) { m_limpMode = v; emit engineFlagChanged(); }
    }
    void setOverheat(bool v) {
        if(m_overheat != v) { m_overheat = v; emit engineFlagChanged(); }
    }

    void setFuelInst(double v) {
        if(m_fuelInst != v) { m_fuelInst = v; emit fuelChanged(); }
    }
    void setFuelAvg(double v) {
        if(m_fuelAvg != v) { m_fuelAvg = v; emit fuelChanged(); }
    }

signals:
    void dataChanged();
    void rpmChanged();
    void gearChanged();
    void steeringAngleChanged();
    void handbrakeChanged();
    void blinkerStatusChanged();
    void highBeamChanged();
    void wiperLevelChanged();
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
    void beltDriverChanged();
    void beltPassengerChanged();
    void wheelSpeedChanged();
    void safetyChanged();
    void brakeChanged();
    void engineMetricChanged();
    void engineFlagChanged();
    void fuelChanged();

private:
    int m_rpm = 0;
    int m_gear = 1;
    double m_steeringAngle = 0.0;
    bool m_handbrake = true;
    int m_blinkerStatus = 0;
    bool m_highBeam = false;
    int m_wiperLevel = 0;
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
    bool m_beltDriver = false;
    bool m_beltPassenger = false;

    // Chassis Values
    double m_wheelFL = 0.0;
    double m_wheelFR = 0.0;
    double m_wheelRL = 0.0;
    double m_wheelRR = 0.0;
    bool m_absActive = false;
    bool m_espActive = false;
    bool m_tractionActive = false;
    bool m_brakePressed = false;


    int m_engineLoad = 0;
    int m_throttlePos = 0;
    int m_pedalPos = 0;
    double m_torqueActual = 0.0;
    double m_torqueRequest = 0.0;

    bool m_idleState = false;
    bool m_cruiseActive = false;
    bool m_limpMode = false;
    bool m_overheat = false;

    double m_fuelInst = 0.0;
    double m_fuelAvg = 0.0;
};

#endif
