#ifndef CANREADER_H
#define CANREADER_H

#include <QObject>
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusFrame>
#include <QTimer>
#include "canhandler.h"

class CanReader : public QObject {
    Q_OBJECT

public:
    explicit CanReader(CanHandler *handler, QObject *parent = nullptr);
    bool connectToBus(const QString &interfaceName = "can0");
    void disconnect();

signals:
    void busConnected();
    void busDisconnected();
    void busError(const QString &errorString);

private slots:
    void processReceivedFrames();
    void checkBusHealth();

private:
    QCanBusDevice *m_canDevice = nullptr;
    CanHandler    *m_handler   = nullptr;
    QTimer        *m_healthTimer = nullptr;

    // FPS counters
    int m_engineFrameCount  = 0;
    int m_comfortFrameCount = 0;

    // Watchdog: last time we saw each ECU
    qint64 m_lastEngine  = 0;  // ms since epoch
    qint64 m_lastComfort = 0;

    void handleFrame(const QCanBusFrame &frame);

    // --- Frame decoders (one per CAN ID) ---
    void decode_0x280(const QCanBusFrame &f);   // RPM, ignition
    // (à compléter au fur et à mesure du RE)
    // void decode_0x320(const QCanBusFrame &f);  // vitesse
    // void decode_0x470(const QCanBusFrame &f);  // température
};

#endif
