#ifndef CANHANDLER_H
#define CANHANDLER_H

#include <QObject>
#include <QCanBus>
#include <QCanBusDevice>
#include <QTimer>
#include <QRandomGenerator> // Added for Qt 6 compatibility

class CanHandler : public QObject {
    Q_OBJECT
    Q_PROPERTY(int rpm READ rpm NOTIFY rpmChanged)

public:
    explicit CanHandler(QObject *parent = nullptr) : QObject(parent), m_rpm(0) {
        QString errorString;
        // virtualcan allows testing on Mac without hardware
        m_canDevice = QCanBus::instance()->createDevice("virtualcan", "can0", &errorString);

        if (m_canDevice) {
            m_canDevice->connectDevice();
        }

        // Simulates the car's Engine data
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [this]() {
            static int mockRpm = 800;
            // QRandomGenerator is the modern replacement for qrand()
            mockRpm += QRandomGenerator::global()->bounded(60) - 25;

            if (mockRpm < 800) mockRpm = 800;
            if (mockRpm > 7000) mockRpm = 7000;
            setRpm(mockRpm);
        });
        timer->start(100);
    }

    int rpm() const { return m_rpm; }

signals:
    void rpmChanged();

private:
    void setRpm(int val) {
        if (m_rpm != val) {
            m_rpm = val;
            emit rpmChanged();
        }
    }
    QCanBusDevice *m_canDevice = nullptr;
    int m_rpm;
};

#endif
