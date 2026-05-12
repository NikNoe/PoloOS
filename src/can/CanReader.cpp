#include "canreader.h"
#include <QDebug>
#include <QDateTime>

// ─── Constantes de décodage ──────────────────────────────────────────────────

// 0x280 – Moteur (Polo 9N3 – validé par capture SavvyCAN)
//   D1 : statut  (0xC9 = contact ON, 0x49 = transitoire)
//   D2 : RPM high byte  \
//   D3 : RPM low  byte   }  RPM = ((D2<<8)|D3) / 4.0
//   D4 : inconnu (dominant 0x0E)
//   D5 : miroir exact de D2
//   D6 : inconnu / variable
//   D7 : compteur montant
//   D8 : proche de D2

static constexpr quint32 ID_ENGINE_RPM    = 0x280;
// static constexpr quint32 ID_SPEED        = 0x320;  // à RE
// static constexpr quint32 ID_TEMP         = 0x470;  // à RE

static constexpr qint64  ECU_TIMEOUT_MS   = 2000;  // 2 s sans trame → ECU offline
static constexpr int     HEALTH_INTERVAL_MS = 1000; // tick watchdog/FPS

// ─── Constructeur ────────────────────────────────────────────────────────────

CanReader::CanReader(CanHandler *handler, QObject *parent)
    : QObject(parent)
    , m_handler(handler)
{
    // Timer watchdog / FPS : toutes les secondes
    m_healthTimer = new QTimer(this);
    m_healthTimer->setInterval(HEALTH_INTERVAL_MS);
    connect(m_healthTimer, &QTimer::timeout, this, &CanReader::checkBusHealth);
}

// ─── Connexion au bus ────────────────────────────────────────────────────────

bool CanReader::connectToBus(const QString &interfaceName)
{
    if (m_canDevice) {
        m_canDevice->disconnectDevice();
        delete m_canDevice;
        m_canDevice = nullptr;
    }

    QString errorString;
    m_canDevice = QCanBus::instance()->createDevice("socketcan", interfaceName, &errorString);

    if (!m_canDevice) {
        qWarning() << "[CanReader] Impossible de créer le device:" << errorString;
        m_handler->setBusEngineActive(false);
        emit busError(errorString);
        return false;
    }

    connect(m_canDevice, &QCanBusDevice::framesReceived,
            this,        &CanReader::processReceivedFrames);

    connect(m_canDevice, &QCanBusDevice::errorOccurred,
            this, [this](QCanBusDevice::CanBusError error) {
                qWarning() << "[CanReader] Erreur bus:" << error;
                m_handler->setErrorFrames(m_handler->errorFrames() + 1);
            });

    if (!m_canDevice->connectDevice()) {
        qWarning() << "[CanReader] connectDevice() échoué:" << m_canDevice->errorString();
        emit busError(m_canDevice->errorString());
        return false;
    }

    qInfo() << "[CanReader] Connecté sur" << interfaceName;
    m_handler->setBusEngineActive(true);
    m_healthTimer->start();
    emit busConnected();
    return true;
}

void CanReader::disconnect()
{
    m_healthTimer->stop();
    if (m_canDevice) {
        m_canDevice->disconnectDevice();
        delete m_canDevice;
        m_canDevice = nullptr;
    }
    m_handler->setBusEngineActive(false);
    m_handler->setEcuEngineOnline(false);
    emit busDisconnected();
}

// ─── Réception des trames ────────────────────────────────────────────────────

void CanReader::processReceivedFrames()
{
    if (!m_canDevice) return;

    while (m_canDevice->framesAvailable()) {
        const QCanBusFrame frame = m_canDevice->readFrame();

        if (!frame.isValid()) {
            m_handler->setErrorFrames(m_handler->errorFrames() + 1);
            continue;
        }

        handleFrame(frame);
    }
}

void CanReader::handleFrame(const QCanBusFrame &frame)
{
    const quint32 id  = frame.frameId();
    const QByteArray payload = frame.payload();

    if (payload.size() < 1) return;

    switch (id) {

    case ID_ENGINE_RPM:
        m_engineFrameCount++;
        m_lastEngine = QDateTime::currentMSecsSinceEpoch();
        decode_0x280(frame);
        break;

        // case ID_SPEED:
        //     m_comfortFrameCount++;
        //     m_lastComfort = QDateTime::currentMSecsSinceEpoch();
        //     decode_0x320(frame);
        //     break;

    default:
        break;
    }
}

// ─── Watchdog / FPS ──────────────────────────────────────────────────────────

void CanReader::checkBusHealth()
{
    const qint64 now = QDateTime::currentMSecsSinceEpoch();

    // --- FPS moteur ---
    m_handler->setEngineFps(m_engineFrameCount);
    m_engineFrameCount = 0;

    // --- FPS confort ---
    m_handler->setComfortFps(m_comfortFrameCount);
    m_comfortFrameCount = 0;

    // --- ECU engine online ? ---
    const bool engineOnline = (now - m_lastEngine) < ECU_TIMEOUT_MS;
    m_handler->setEcuEngineOnline(engineOnline);

    if (!engineOnline && m_lastEngine != 0) {
        // Timeout : on remet le RPM à 0 pour éviter une valeur figée à l'écran
        m_handler->setRpm(0);
        m_handler->setEngineRunning(false);
        qWarning() << "[CanReader] ECU moteur timeout – pas de trame 0x280 depuis"
                   << (now - m_lastEngine) << "ms";
    }
}

// ─── Décodeur 0x280 : RPM + statut allumage ──────────────────────────────────
//
//  Structure validée sur Polo 9N3 (capture SavvyCAN, mars 2026) :
//
//  Byte  Rôle
//  ────  ─────────────────────────────────────────────────
//  D1    Statut ignition : 0xC9 = contact ON, 0x49 = transitoire
//        bit 7 = 1 → contact activé
//        bit 0 = toggle compteur (alterne 0/1)
//  D2    RPM octet haut  (MSB)
//  D3    RPM octet bas   (LSB)
//  D4    Inconnu (dominant 0x0E) – à décoder
//  D5    Miroir exact de D2 (redondance VAG)
//  D6    Inconnu / variable – à décoder (charge moteur ?)
//  D7    Compteur montant (~0x1A à ralenti)
//  D8    Proche de D2 (~D2 ± 1)
//
//  Formule RPM : RPM = ((D2 << 8) | D3) / 4
//  Idle froid  : ~1 987 rpm   Idle chaud attendu : ~850 rpm

void CanReader::decode_0x280(const QCanBusFrame &frame)
{
    const QByteArray &d = frame.payload();
    if (d.size() < 8) return;

    const quint8 d1 = static_cast<quint8>(d[0]);
    const quint8 d2 = static_cast<quint8>(d[1]);
    const quint8 d3 = static_cast<quint8>(d[2]);
    // d4 = static_cast<quint8>(d[3]);  // inconnu – réservé
    // d6 = static_cast<quint8>(d[5]);  // inconnu – réservé

    // --- Ignition ---
    const bool ignition = (d1 & 0x80) != 0;  // bit 7
    m_handler->setIgnitionOn(ignition);

    // --- RPM ---
    const quint16 raw = (static_cast<quint16>(d2) << 8) | d3;
    const int rpm = static_cast<int>(raw / 4.0);

    m_handler->setRpm(rpm);
    m_handler->setEngineRunning(ignition && rpm > 200);

    // --- Idle détection (< 1000 rpm en chaud, < 2500 en froid) ---
    m_handler->setIdleState(rpm > 200 && rpm < 2500
                            && m_handler->throttlePos() == 0);
}