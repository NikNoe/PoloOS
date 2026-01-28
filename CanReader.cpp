#include "CanReader.h"
#include <QDebug>

CanReader::CanReader(QObject *parent) : QObject(parent) {}

bool CanReader::connectToBus(const QString &interfaceName) {
    if (QCanBus::instance()->plugins().contains("socketcan")) {
        m_canDevice = QCanBus::instance()->createDevice("socketcan", interfaceName);
        if (!m_canDevice) return false;

        connect(m_canDevice, &QCanBusDevice::framesReceived, this, &CanReader::processReceivedFrames);
        return m_canDevice->connectDevice();
    }
    return false;
}

void CanReader::processReceivedFrames() {
    while (m_canDevice->framesAvailable()) {
        const QCanBusFrame frame = m_canDevice->readFrame();
        handleFrame(frame);
    }
}

void CanReader::handleFrame(const QCanBusFrame &frame) {
    uint frameId = frame.frameId();
    const QByteArray data = frame.payload();

    // EXEMPLE DE DÉCODAGE POLO 9N3 (Bus Traction/Chassis)
    switch (frameId) {
    case 0x0C2: { // ANGLE VOLANT
        // Souvent Byte 0 et 1, format Little Endian, signé
        int16_t rawAngle = (data[1] << 8) | (uint8_t)data[0];
        double angle = rawAngle * 0.1; // Facteur typique 0.1°
        // carCan->setSteeringAngle(angle);
        break;
    }
    case 0x280: { // RÉGIME MOTEUR (RPM)
        uint16_t rpm = ((uint8_t)data[3] << 8 | (uint8_t)data[2]) / 4;
        // carCan->setRpm(rpm);
        break;
    }
    case 0x4A0: { // VITESSE DES ROUES (Individuel)
        // Exemple : Roue Avant Gauche sur les 2 premiers bytes
        uint16_t flRaw = ((uint8_t)data[1] << 8 | (uint8_t)data[0]);
        double speedFL = flRaw * 0.01; // Facteur à ajuster selon tes tests
        // carCan->setWheelFL(speedFL);
        break;
    }
    }
}
