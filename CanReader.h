#ifndef CANREADER_H
#define CANREADER_H

#include <QObject>
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusFrame>

class CanReader : public QObject {
    Q_OBJECT
public:
    explicit CanReader(QObject *parent = nullptr);
    bool connectToBus(const QString &interfaceName = "can0");

private slots:
    void processReceivedFrames();

private:
    QCanBusDevice *m_canDevice = nullptr;
    void handleFrame(const QCanBusFrame &frame);
};

#endif
