#ifndef CANHANDLER_H
#define CANHANDLER_H

#include <QObject>
#include <QString>

#ifndef GIT_COMMIT_HASH
#define GIT_COMMIT_HASH "no-git-hash"
#endif

#ifndef BUILD_DATE
#define BUILD_DATE "2026-01-12"
#endif

class CanHandler : public QObject {
    Q_OBJECT

    // --- 1. POWERTRAIN & PERFORMANCE ---
    Q_PROPERTY(int rpm READ rpm WRITE setRpm NOTIFY engineMetricChanged)
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(int gear READ gear WRITE setGear NOTIFY gearChanged)
    Q_PROPERTY(bool ignitionOn READ ignitionOn WRITE setIgnitionOn NOTIFY engineFlagChanged)
    Q_PROPERTY(bool engineRunning READ engineRunning WRITE setEngineRunning NOTIFY engineFlagChanged)
    Q_PROPERTY(int engineLoad READ engineLoad WRITE setEngineLoad NOTIFY engineMetricChanged)
    Q_PROPERTY(int throttlePos READ throttlePos WRITE setThrottlePos NOTIFY engineMetricChanged)
    Q_PROPERTY(int pedalPos READ pedalPos WRITE setPedalPos NOTIFY engineMetricChanged)
    Q_PROPERTY(double torqueActual READ torqueActual WRITE setTorqueActual NOTIFY engineMetricChanged)
    Q_PROPERTY(double torqueRequest READ torqueRequest WRITE setTorqueRequest NOTIFY engineMetricChanged)
    Q_PROPERTY(bool idleState READ idleState WRITE setIdleState NOTIFY engineFlagChanged)
    Q_PROPERTY(bool cruiseActive READ cruiseActive WRITE setCruiseActive NOTIFY engineFlagChanged)
    Q_PROPERTY(bool limpMode READ limpMode WRITE setLimpMode NOTIFY engineFlagChanged)
    Q_PROPERTY(bool overheat READ overheat WRITE setOverheat NOTIFY engineFlagChanged)

    // --- 2. CHASSIS & DYNAMICS ---
    Q_PROPERTY(double steeringAngle READ steeringAngle WRITE setSteeringAngle NOTIFY steeringAngleChanged)
    Q_PROPERTY(double wheelFL READ wheelFL WRITE setWheelFL NOTIFY wheelSpeedChanged)
    Q_PROPERTY(double wheelFR READ wheelFR WRITE setWheelFR NOTIFY wheelSpeedChanged)
    Q_PROPERTY(double wheelRL READ wheelRL WRITE setWheelRL NOTIFY wheelSpeedChanged)
    Q_PROPERTY(double wheelRR READ wheelRR WRITE setWheelRR NOTIFY wheelSpeedChanged)
    Q_PROPERTY(bool absActive READ absActive WRITE setAbsActive NOTIFY safetyChanged)
    Q_PROPERTY(bool espActive READ espActive WRITE setEspActive NOTIFY safetyChanged)
    Q_PROPERTY(bool tractionActive READ tractionActive WRITE setTractionActive NOTIFY safetyChanged)
    Q_PROPERTY(bool brakePressed READ brakePressed WRITE setBrakePressed NOTIFY brakeChanged)
    Q_PROPERTY(bool handbrake READ handbrake WRITE setHandbrake NOTIFY handbrakeChanged)

    // --- 3. BODY & SECURITY ---
    Q_PROPERTY(bool isLocked READ isLocked WRITE setIsLocked NOTIFY lockStatusChanged)
    Q_PROPERTY(bool doorFL READ doorFL WRITE setDoorFL NOTIFY doorChanged)
    Q_PROPERTY(bool doorFR READ doorFR WRITE setDoorFR NOTIFY doorChanged)
    Q_PROPERTY(bool doorRL READ doorRL WRITE setDoorRL NOTIFY doorChanged)
    Q_PROPERTY(bool doorRR READ doorRR WRITE setDoorRR NOTIFY doorChanged)
    Q_PROPERTY(bool trunk READ trunk WRITE setTrunk NOTIFY doorChanged)
    Q_PROPERTY(int windowPos READ windowPos WRITE setWindowPos NOTIFY windowChanged)
    Q_PROPERTY(int windowPos READ windowPos WRITE setWindowPos NOTIFY windowChanged)
    Q_PROPERTY(int windshieldHeater READ windshieldHeater WRITE setWindshieldHeater NOTIFY windshieldChanged)
    Q_PROPERTY(bool beltDriver READ beltDriver WRITE setBeltDriver NOTIFY beltChanged)
    Q_PROPERTY(bool beltPassenger READ beltPassenger WRITE setBeltPassenger NOTIFY beltChanged)
    Q_PROPERTY(int blinkerStatus READ blinkerStatus WRITE setBlinkerStatus NOTIFY blinkerChanged)
    Q_PROPERTY(int wiperLevel READ wiperLevel WRITE setWiperLevel NOTIFY wiperChanged)
    Q_PROPERTY(bool interiorLight READ interiorLight WRITE setInteriorLight NOTIFY lightChanged)
    Q_PROPERTY(bool acActive READ acActive WRITE setAcActive NOTIFY acChanged)

    // --- 4. ENERGY, THERMAL & ELECTRICAL ---
    Q_PROPERTY(double tempCoolant READ tempCoolant WRITE setTempCoolant NOTIFY tempChanged)
    Q_PROPERTY(double tempOil READ tempOil WRITE setTempOil NOTIFY tempChanged)
    Q_PROPERTY(double tempAmbient READ tempAmbient WRITE setTempAmbient NOTIFY tempChanged)
    Q_PROPERTY(double tempIntake READ tempIntake WRITE setTempIntake NOTIFY tempChanged)
    Q_PROPERTY(double tempFuel READ tempFuel WRITE setTempFuel NOTIFY tempChanged)
    Q_PROPERTY(double batteryVoltage READ batteryVoltage WRITE setBatteryVoltage NOTIFY elecChanged)
    Q_PROPERTY(bool altCharging READ altCharging WRITE setAltCharging NOTIFY elecChanged)
    Q_PROPERTY(int rangePossible READ rangePossible WRITE setRangePossible NOTIFY fuelLevelChanged)
    Q_PROPERTY(int fuelToFill READ fuelToFill WRITE setFuelToFill NOTIFY fuelLevelChanged)
    Q_PROPERTY(double fuelInst READ fuelInst WRITE setFuelInst NOTIFY fuelChanged)
    Q_PROPERTY(double fuelAvg READ fuelAvg WRITE setFuelAvg NOTIFY fuelChanged)

    // --- 5. DIAGNOSTICS & BUS HEALTH ---
    Q_PROPERTY(bool busEngineActive READ busEngineActive WRITE setBusEngineActive NOTIFY diagChanged)
    Q_PROPERTY(bool busComfortActive READ busComfortActive WRITE setBusComfortActive NOTIFY diagChanged)
    Q_PROPERTY(int engineFps READ engineFps WRITE setEngineFps NOTIFY diagChanged)
    Q_PROPERTY(int comfortFps READ comfortFps WRITE setComfortFps NOTIFY diagChanged)
    Q_PROPERTY(int errorFrames READ errorFrames WRITE setErrorFrames NOTIFY diagChanged)
    Q_PROPERTY(QString lastFaultCode READ lastFaultCode WRITE setLastFaultCode NOTIFY diagChanged)
    Q_PROPERTY(bool ecuEngineOnline READ ecuEngineOnline WRITE setEcuEngineOnline NOTIFY ecuStatusChanged)
    Q_PROPERTY(bool ecuAbsOnline READ ecuAbsOnline WRITE setEcuAbsOnline NOTIFY ecuStatusChanged)
    Q_PROPERTY(bool ecuBodyOnline READ ecuBodyOnline WRITE setEcuBodyOnline NOTIFY ecuStatusChanged)

    // --- SYSTEM INFO ---
    Q_PROPERTY(QString vin READ vin CONSTANT)
    Q_PROPERTY(double mileage READ mileage NOTIFY mileageChanged)
    Q_PROPERTY(QString gitHash READ gitHash CONSTANT)
    Q_PROPERTY(QString buildDate READ buildDate CONSTANT)


    Q_PROPERTY(bool posLights READ posLights WRITE setPosLights NOTIFY lightsChanged)
    Q_PROPERTY(bool lowBeam READ lowBeam WRITE setLowBeam NOTIFY lightsChanged)
    Q_PROPERTY(bool highBeam READ highBeam WRITE setHighBeam NOTIFY lightsChanged)

public:
    explicit CanHandler(QObject *parent = nullptr) : QObject(parent) {}

    // --- GETTERS ---
    int rpm() const { return m_rpm; }
    int speed() const { return m_speed; }
    int gear() const { return m_gear; }
    bool ignitionOn() const { return m_ignitionOn; }
    bool engineRunning() const { return m_engineRunning; }
    int engineLoad() const { return m_engineLoad; }
    int throttlePos() const { return m_throttlePos; }
    int pedalPos() const { return m_pedalPos; }
    double torqueActual() const { return m_torqueActual; }
    double torqueRequest() const { return m_torqueRequest; }
    bool idleState() const { return m_idleState; }
    bool cruiseActive() const { return m_cruiseActive; }
    bool limpMode() const { return m_limpMode; }
    bool overheat() const { return m_overheat; }
    double steeringAngle() const { return m_steeringAngle; }
    double wheelFL() const { return m_wheelFL; }
    double wheelFR() const { return m_wheelFR; }
    double wheelRL() const { return m_wheelRL; }
    double wheelRR() const { return m_wheelRR; }
    bool absActive() const { return m_absActive; }
    bool espActive() const { return m_espActive; }
    bool tractionActive() const { return m_tractionActive; }
    bool brakePressed() const { return m_brakePressed; }
    bool handbrake() const { return m_handbrake; }
    bool isLocked() const { return m_isLocked; }
    bool doorFL() const { return m_doorFL; }
    bool doorFR() const { return m_doorFR; }
    bool doorRL() const { return m_doorRL; }
    bool doorRR() const { return m_doorRR; }
    bool trunk() const { return m_trunk; }
    int windowPos() const { return m_windowPos; }
    bool windshieldHeater() const { return m_windshieldHeater; }
    bool beltDriver() const { return m_beltDriver; }
    bool beltPassenger() const { return m_beltPassenger; }
    double tempCoolant() const { return m_tempCoolant; }
    double tempOil() const { return m_tempOil; }
    double tempAmbient() const { return m_tempAmbient; }
    double tempIntake() const { return m_tempIntake; }
    double tempFuel() const { return m_tempFuel; }
    double batteryVoltage() const { return m_batteryVoltage; }
    bool altCharging() const { return m_altCharging; }
    int rangePossible() const { return m_rangePossible; }
    int fuelToFill() const { return m_fuelToFill; }
    double fuelInst() const { return m_fuelInst; }
    double fuelAvg() const { return m_fuelAvg; }
    bool busEngineActive() const { return m_busEngineActive; }
    bool busComfortActive() const { return m_busComfortActive; }
    int engineFps() const { return m_engineFps; }
    int comfortFps() const { return m_comfortFps; }
    int errorFrames() const { return m_errorFrames; }
    QString lastFaultCode() const { return m_lastFaultCode; }
    bool ecuEngineOnline() const { return m_ecuEngineOnline; }
    bool ecuAbsOnline() const { return m_ecuAbsOnline; }
    bool ecuBodyOnline() const { return m_ecuBodyOnline; }
    QString vin() const { return "WVWZZZ9NZ6Yxxxxxx"; } // Mock VIN for Polo 9N3
    double mileage() const { return m_mileage; }
    QString gitHash() const { return GIT_COMMIT_HASH; }
    QString buildDate() const { return BUILD_DATE; }
    int blinkerStatus() const { return m_blinkerStatus; }
    int wiperLevel() const { return m_wiperLevel; }
    bool interiorLight() const { return m_interiorLight; }
    bool acActive() const { return m_acActive; }
    bool posLights() const { return m_posLights; }
    bool lowBeam() const { return m_lowBeam; }
    bool highBeam() const { return m_highBeam; }

public slots:
    // --- SETTERS ---
    void setRpm(int v) { if(m_rpm != v) { m_rpm = v; emit engineMetricChanged(); } }
    void setSpeed(int v) { if(m_speed != v) { m_speed = v; emit speedChanged(); } }
    void setGear(int v) { if(m_gear != v) { m_gear = v; emit gearChanged(); } }
    void setIgnitionOn(bool v) { if(m_ignitionOn != v) { m_ignitionOn = v; emit engineFlagChanged(); } }
    void setEngineRunning(bool v) { if(m_engineRunning != v) { m_engineRunning = v; emit engineFlagChanged(); } }
    void setEngineLoad(int v) { if(m_engineLoad != v) { m_engineLoad = v; emit engineMetricChanged(); } }
    void setThrottlePos(int v) { if(m_throttlePos != v) { m_throttlePos = v; emit engineMetricChanged(); } }
    void setPedalPos(int v) { if(m_pedalPos != v) { m_pedalPos = v; emit engineMetricChanged(); } }
    void setTorqueActual(double v) { if(m_torqueActual != v) { m_torqueActual = v; emit engineMetricChanged(); } }
    void setTorqueRequest(double v) { if(m_torqueRequest != v) { m_torqueRequest = v; emit engineMetricChanged(); } }
    void setIdleState(bool v) { if(m_idleState != v) { m_idleState = v; emit engineFlagChanged(); } }
    void setCruiseActive(bool v) { if(m_cruiseActive != v) { m_cruiseActive = v; emit engineFlagChanged(); } }
    void setLimpMode(bool v) { if(m_limpMode != v) { m_limpMode = v; emit engineFlagChanged(); } }
    void setOverheat(bool v) { if(m_overheat != v) { m_overheat = v; emit engineFlagChanged(); } }
    void setSteeringAngle(double v) { if(m_steeringAngle != v) { m_steeringAngle = v; emit steeringAngleChanged(); } }
    void setWheelFL(double v) { if(m_wheelFL != v) { m_wheelFL = v; emit wheelSpeedChanged(); } }
    void setWheelFR(double v) { if(m_wheelFR != v) { m_wheelFR = v; emit wheelSpeedChanged(); } }
    void setWheelRL(double v) { if(m_wheelRL != v) { m_wheelRL = v; emit wheelSpeedChanged(); } }
    void setWheelRR(double v) { if(m_wheelRR != v) { m_wheelRR = v; emit wheelSpeedChanged(); } }
    void setAbsActive(bool v) { if(m_absActive != v) { m_absActive = v; emit safetyChanged(); } }
    void setEspActive(bool v) { if(m_espActive != v) { m_espActive = v; emit safetyChanged(); } }
    void setTractionActive(bool v) { if(m_tractionActive != v) { m_tractionActive = v; emit safetyChanged(); } }
    void setBrakePressed(bool v) { if(m_brakePressed != v) { m_brakePressed = v; emit brakeChanged(); } }
    void setHandbrake(bool v) { if(m_handbrake != v) { m_handbrake = v; emit handbrakeChanged(); } }
    void setIsLocked(bool v) { if(m_isLocked != v) { m_isLocked = v; emit lockStatusChanged(); } }
    void setDoorFL(bool v) { if(m_doorFL != v) { m_doorFL = v; emit doorChanged(); } }
    void setDoorFR(bool v) { if(m_doorFR != v) { m_doorFR = v; emit doorChanged(); } }
    void setDoorRL(bool v) { if(m_doorRL != v) { m_doorRL = v; emit doorChanged(); } }
    void setDoorRR(bool v) { if(m_doorRR != v) { m_doorRR = v; emit doorChanged(); } }
    void setTrunk(bool v) { if(m_trunk != v) { m_trunk = v; emit doorChanged(); } }
    void setWindshieldHeater(bool v ) { if(m_windshieldHeater != v) { m_windshieldHeater = v ; emit windshieldChanged();}}
    void setWindowPos(int v) { if(m_windowPos != v) { m_windowPos = v; emit windowChanged(); } }
    void setBeltDriver(bool v) { if(m_beltDriver != v) { m_beltDriver = v; emit beltChanged(); } }
    void setBeltPassenger(bool v) { if(m_beltPassenger != v) { m_beltPassenger = v; emit beltChanged(); } }
    void setTempCoolant(double v) { if(m_tempCoolant != v) { m_tempCoolant = v; emit tempChanged(); } }
    void setTempOil(double v) { if(m_tempOil != v) { m_tempOil = v; emit tempChanged(); } }
    void setTempAmbient(double v) { if(m_tempAmbient != v) { m_tempAmbient = v; emit tempChanged(); } }
    void setTempIntake(double v) { if(m_tempIntake != v) { m_tempIntake = v; emit tempChanged(); } }
    void setTempFuel(double v) { if(m_tempFuel != v) { m_tempFuel = v; emit tempChanged(); } }
    void setBatteryVoltage(double v) { if(m_batteryVoltage != v) { m_batteryVoltage = v; emit elecChanged(); } }
    void setAltCharging(bool v) { if(m_altCharging != v) { m_altCharging = v; emit elecChanged(); } }
    void setRangePossible(int v) { if(m_rangePossible != v) { m_rangePossible = v; emit fuelLevelChanged(); } }
    void setFuelToFill(int v) { if(m_fuelToFill != v) { m_fuelToFill = v; emit fuelLevelChanged(); } }
    void setFuelInst(double v) { if(m_fuelInst != v) { m_fuelInst = v; emit fuelChanged(); } }
    void setFuelAvg(double v) { if(m_fuelAvg != v) { m_fuelAvg = v; emit fuelChanged(); } }
    void setBusEngineActive(bool v) { if(m_busEngineActive != v) { m_busEngineActive = v; emit diagChanged(); } }
    void setBusComfortActive(bool v) { if(m_busComfortActive != v) { m_busComfortActive = v; emit diagChanged(); } }
    void setEngineFps(int v) { if(m_engineFps != v) { m_engineFps = v; emit diagChanged(); } }
    void setComfortFps(int v) { if(m_comfortFps != v) { m_comfortFps = v; emit diagChanged(); } }
    void setErrorFrames(int v) { if(m_errorFrames != v) { m_errorFrames = v; emit diagChanged(); } }
    void setLastFaultCode(QString v) { if(m_lastFaultCode != v) { m_lastFaultCode = v; emit diagChanged(); } }
    void setEcuEngineOnline(bool v) { if(m_ecuEngineOnline != v) { m_ecuEngineOnline = v; emit ecuStatusChanged(); } }
    void setEcuAbsOnline(bool v) { if(m_ecuAbsOnline != v) { m_ecuAbsOnline = v; emit ecuStatusChanged(); } }
    void setEcuBodyOnline(bool v) { if(m_ecuBodyOnline != v) { m_ecuBodyOnline = v; emit ecuStatusChanged(); } }
    void setBlinkerStatus(int v) {
        if (m_blinkerStatus != v) {
            m_blinkerStatus = v;
            emit blinkerChanged();
        }
    }

    void setWiperLevel(int v) {
        if (m_wiperLevel != v) {
            m_wiperLevel = v;
            emit wiperChanged();
        }
    }

    void setInteriorLight(bool v) {
        if (m_interiorLight != v) {
            m_interiorLight = v;
            emit lightChanged();
        }
    }

    void setAcActive(bool v) {
        if (m_acActive != v) {
            m_acActive = v;
            emit acChanged();
        }
    }
    void setPosLights(bool v) {
        if (m_posLights != v) {
            m_posLights = v;
            emit lightsChanged();
        }
    }

    void setLowBeam(bool v) {
        if (m_lowBeam != v) {
            m_lowBeam = v;
            // Si on éteint les codes, on force l'extinction des pleins phares
            if (!v) setHighBeam(false);
            emit lightsChanged();
        }
    }

    void setHighBeam(bool v) {
        if (m_highBeam != v) {
            m_highBeam = v;
            emit lightsChanged();
        }
    }



signals:
    void engineMetricChanged();
    void engineFlagChanged();
    void speedChanged();
    void gearChanged();
    void steeringAngleChanged();
    void wheelSpeedChanged();
    void safetyChanged();
    void brakeChanged();
    void handbrakeChanged();
    void lockStatusChanged();
    void doorChanged();
    void windowChanged();
    void windshieldChanged();
    void beltChanged();
    void tempChanged();
    void elecChanged();
    void fuelLevelChanged();
    void fuelChanged();
    void diagChanged();
    void ecuStatusChanged();
    void mileageChanged();
    void blinkerChanged();
    void wiperChanged();
    void lightChanged();
    void acChanged();
    void lightsChanged();

private:
    int m_rpm = 0;
    int m_speed = 0;
    int m_gear = 1;
    bool m_ignitionOn = false;
    bool m_engineRunning = false;
    int m_engineLoad = 0;
    int m_throttlePos = 0;
    int m_pedalPos = 0;
    double m_torqueActual = 0.0;
    double m_torqueRequest = 0.0;
    bool m_idleState = false;
    bool m_cruiseActive = false;
    bool m_limpMode = false;
    bool m_overheat = false;
    double m_steeringAngle = 0.0;
    double m_wheelFL = 0.0;
    double m_wheelFR = 0.0;
    double m_wheelRL = 0.0;
    double m_wheelRR = 0.0;
    bool m_absActive = false;
    bool m_espActive = false;
    bool m_tractionActive = false;
    bool m_brakePressed = false;
    bool m_handbrake = true;
    bool m_isLocked = true;
    bool m_doorFL = false;
    bool m_doorFR = false;
    bool m_doorRL = false;
    bool m_doorRR = false;
    bool m_trunk = false;
    int m_windowPos = 0;
    bool m_windshieldHeater = false ;
    bool m_beltDriver = false;
    bool m_beltPassenger = false;
    double m_tempCoolant = 90.0;
    double m_tempOil = 90.0;
    double m_tempAmbient = 20.0;
    double m_tempIntake = 35.0;
    double m_tempFuel = 30.0;
    double m_batteryVoltage = 12.6;
    bool m_altCharging = false;
    int m_rangePossible = 450;
    int m_fuelToFill = 15;
    double m_fuelInst = 0.0;
    double m_fuelAvg = 6.5;
    bool m_busEngineActive = false;
    bool m_busComfortActive = false;
    int m_engineFps = 0;
    int m_comfortFps = 0;
    int m_errorFrames = 0;
    QString m_lastFaultCode = "";
    bool m_ecuEngineOnline = false;
    bool m_ecuAbsOnline = false;
    bool m_ecuBodyOnline = false;
    double m_mileage = 0.0;
    int m_blinkerStatus = 0; // 0=Off, 1=Left, 2=Right
    int m_wiperLevel = 0;    // 0=Off, 1=Int, 2=Low, 3=High
    bool m_interiorLight = false;
    bool m_acActive = false;
    bool m_posLights = false;
    bool m_lowBeam = false;
    bool m_highBeam = false;
};

#endif
