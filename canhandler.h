#ifndef CANHANDLER_H
#define CANHANDLER_H

#include <QObject>
#include <QCanBus>
#include <QCanBusDevice>
#include <QTimer>

class CanHandler : public QObject {
    Q_OBJECT
    Q_PROPERTY(int rpm READ rpm NOTIFY rpmChanged)

public:
    explicit CanHandler(QObject *parent = nullptr) : QObject(parent), m_rpm(0) {
        QString errorString;
        // Using "virtualcan" so it works on your Mac without hardware
        m_canDevice = QCanBus::instance()->createDevice("virtualcan", "can0", &errorString);

        if (m_canDevice) {
            m_canDevice->connectDevice();
            connect(m_canDevice, &QCanBusDevice::framesReceived, this, &CanHandler::processFrames);
        }

        // SIMULATOR: Send fake RPM data every 100ms so we can see it on screen
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [this]() {
            static int mockRpm = 800;
            mockRpm += (qrand() % 50) - 20; // Randomize RPM slightly
            if (mockRpm < 800) mockRpm = 800;
            setRpm(mockRpm);
        });
        timer->start(100);
    }

    int rpm() const { return m_rpm; }

signals:
    void rpmChanged();

private slots:
    void processFrames() {
        while (m_canDevice->framesAvailable()) {
            const QCanBusFrame frame = m_canDevice->readFrame();
            // 0x280 is the real VW Polo IV ID for Engine Data
            if (frame.frameId() == 0x280) {
                // Byte 2 and 3 usually contain RPM in VW TP2.0
                // This is where you will write the real decoding logic later
            }
        }
    }

    void setRpm(int val) {
        if (m_rpm != val) {
            m_rpm = val;
            emit rpmChanged();
        }
    }

private:
    QCanBusDevice *m_canDevice = nullptr;
    int m_rpm;
};

#endif
