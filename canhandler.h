#ifndef CANHANDLER_H
#define CANHANDLER_H

#include <QObject>
#include <QTimer>
#include <QRandomGenerator>// Added for Qt 6 compatibility

#include <QCanBusDevice>


class CanHandler : public QObject {
    Q_OBJECT
    // Define all the data points we want to show on the right side
    Q_PROPERTY(int rpm READ rpm NOTIFY dataChanged)
    Q_PROPERTY(int temp READ temp NOTIFY dataChanged)
    Q_PROPERTY(int fuel READ fuel NOTIFY dataChanged)
    Q_PROPERTY(bool doorOpen READ doorOpen NOTIFY dataChanged)
    Q_PROPERTY(double consumption READ consumption NOTIFY dataChanged)
    Q_PROPERTY(bool handbrake READ handbrake NOTIFY dataChanged)
    Q_PROPERTY(bool highBeam READ highBeam NOTIFY dataChanged)
    Q_PROPERTY(int blinkerStatus READ blinkerStatus NOTIFY dataChanged) // 0=off, 1=left, 2=right



public:
    explicit CanHandler(QObject *parent = nullptr) : QObject(parent),
        m_rpm(800), m_temp(20), m_fuel(75), m_doorOpen(false), m_consumption(5.5)
    {
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [this]() {
            // SIMULATION LOGIC:
            m_rpm = 800 + QRandomGenerator::global()->bounded(200);
            if (m_temp < 90) m_temp += 1; // Engine warming up
            if (m_rpm > 950) m_doorOpen = false; // Simulate auto-lock
            m_consumption = 5.0 + (m_rpm / 1000.0);

            // Let's simulate the Handbrake being ON
            m_handbrake = true;

            // Let's simulate the high beam being OFF
            m_highBeam = false;

            // Simulate the left blinker flashing every 2 seconds
            static int tick = 0;
            tick++;
            if (tick % 2 == 0) m_blinkerStatus = 1; else m_blinkerStatus = 0;


            emit dataChanged();
        });

        timer->start(1000);
    }

    // Getters for QML
    int rpm() const { return m_rpm; }
    int temp() const { return m_temp; }
    int fuel() const { return m_fuel; }
    bool doorOpen() const { return m_doorOpen; }
    double consumption() const { return m_consumption; }
    bool handbrake() const { return m_handbrake; }
    bool highBeam() const { return m_highBeam; }
    int blinkerStatus() const { return m_blinkerStatus; }

signals:
    void dataChanged();

private:
    int m_rpm, m_temp, m_fuel, m_blinkerStatus;
    bool m_doorOpen, m_handbrake, m_highBeam;
    double m_consumption;};

#endif
