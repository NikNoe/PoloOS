#ifndef CANHANDLER_H
#define CANHANDLER_H

#include <QObject>
#include <QTimer>
#include <QRandomGenerator>
#include <QCanBusDevice>

class CanHandler : public QObject {
    Q_OBJECT

    // --- Performance & Engine ---
    Q_PROPERTY(int rpm READ rpm NOTIFY dataChanged)
    Q_PROPERTY(int temp READ temp NOTIFY dataChanged)
    Q_PROPERTY(double consumption READ consumption NOTIFY dataChanged)
    Q_PROPERTY(double steeringAngle READ steeringAngle NOTIFY dataChanged)

    // --- Fuel ---
    Q_PROPERTY(int fuel READ fuel NOTIFY dataChanged)
    Q_PROPERTY(double fuelLiters READ fuelLiters NOTIFY dataChanged)

    // --- Safety & Lights ---
    Q_PROPERTY(bool handbrake READ handbrake NOTIFY dataChanged)
    Q_PROPERTY(bool brakeActive READ brakeActive NOTIFY dataChanged) // For "STOP" overlay
    Q_PROPERTY(bool highBeam READ highBeam NOTIFY dataChanged)
    Q_PROPERTY(int blinkerStatus READ blinkerStatus NOTIFY dataChanged) // 0=off, 1=left, 2=right

    // --- Doors & Windows ---
    Q_PROPERTY(bool isLocked READ isLocked NOTIFY dataChanged)
    Q_PROPERTY(bool doorOpen READ doorOpen NOTIFY dataChanged) // Master "Any door"
    Q_PROPERTY(bool doorFL READ doorFL NOTIFY dataChanged)
    Q_PROPERTY(bool doorFR READ doorFR NOTIFY dataChanged)
    Q_PROPERTY(bool doorRL READ doorRL NOTIFY dataChanged)
    Q_PROPERTY(bool doorRR READ doorRR NOTIFY dataChanged)
    Q_PROPERTY(bool trunk READ trunk NOTIFY dataChanged)
    Q_PROPERTY(int windowPos READ windowPos NOTIFY dataChanged)

    // --- Comfort ---
    Q_PROPERTY(bool acActive READ acActive NOTIFY dataChanged)
    Q_PROPERTY(bool interiorLight READ interiorLight NOTIFY dataChanged)

public:
    explicit CanHandler(QObject *parent = nullptr) : QObject(parent) {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [this]() {
            // --- SIMULATION LOGIC ---

            // 1. Engine & Driving
            m_rpm = 800 + QRandomGenerator::global()->bounded(2000);
            if (m_temp < 90) m_temp += 1;
            m_consumption = 5.2 + (m_rpm / 1500.0);

            // 2. Steering Swing (For 3D Wheel Rotation)
            static double angleDir = 1.0;
            m_steeringAngle += (5.0 * angleDir);
            if (m_steeringAngle > 45 || m_steeringAngle < -45) angleDir *= -1;

            // 3. Safety Signals
            m_handbrake = (m_rpm < 1000); // Set brake if idling
            m_brakeActive = (m_rpm > 2500); // Simulate braking at high revs

            // 4. Blinker Logic (Left, then Right, then Off)
            static int cycle = 0;
            cycle = (cycle + 1) % 30;
            if (cycle < 10) m_blinkerStatus = 1;
            else if (cycle < 20) m_blinkerStatus = 2;
            else m_blinkerStatus = 0;

            // 5. Door & Trunk Logic
            m_doorFL = (cycle == 5); // Pop the door open occasionally
            m_trunk = (m_rpm < 900 && cycle > 25);

            // 6. Fuel Depletion
            if (m_fuelLiters > 5.0) m_fuelLiters -= 0.01;
            m_fuel = static_cast<int>((m_fuelLiters / 45.0) * 100);

            emit dataChanged();
        });
        timer->start(100); // Fast update for smooth 3D movement
    }

    // --- Getters (Required for QML to READ the data) ---
    int rpm() const { return m_rpm; }
    int temp() const { return m_temp; }
    int fuel() const { return m_fuel; }
    double fuelLiters() const { return m_fuelLiters; }
    double consumption() const { return m_consumption; }
    double steeringAngle() const { return m_steeringAngle; }

    bool handbrake() const { return m_handbrake; }
    bool brakeActive() const { return m_brakeActive; }
    bool highBeam() const { return m_highBeam; }
    int blinkerStatus() const { return m_blinkerStatus; }

    bool isLocked() const { return m_isLocked; }
    bool doorOpen() const { return m_doorFL || m_doorFR || m_doorRL || m_doorRR || m_trunk; }
    bool doorFL() const { return m_doorFL; }
    bool doorFR() const { return m_doorFR; }
    bool doorRL() const { return m_doorRL; }
    bool doorRR() const { return m_doorRR; }
    bool trunk() const { return m_trunk; }
    int windowPos() const { return m_windowPos; }

    bool acActive() const { return m_acActive; }
    bool interiorLight() const { return m_interiorLight; }

signals:
    void dataChanged();

private:
    // Initial Values (Polo 9N3 Defaults)
    int m_rpm = 0, m_temp = 20, m_fuel = 100, m_blinkerStatus = 0;
    int m_windowPos = 0;
    bool m_handbrake = true, m_brakeActive = false, m_highBeam = false;
    bool m_isLocked = false, m_acActive = false, m_interiorLight = false;
    bool m_doorFL = false, m_doorFR = false, m_doorRL = false, m_doorRR = false, m_trunk = false;
    double m_consumption = 0.0, m_steeringAngle = 0.0, m_fuelLiters = 45.0;
};

#endif
