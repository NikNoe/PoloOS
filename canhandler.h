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

signals:
    void dataChanged();

private:
    int m_rpm, m_temp, m_fuel;
    bool m_doorOpen;
    double m_consumption;
};

#endif
