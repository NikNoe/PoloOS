#pragma once

// ─── PoloCar.h ────────────────────────────────────────────────────────────────
// État pur de la voiture : zéro Raylib, zéro Qt.
// Cette struct sera réutilisable directement dans PoloOS Qt plus tard.
// ─────────────────────────────────────────────────────────────────────────────

struct PoloCar {

    // ── Position & mouvement ──────────────────────────────────────────────────
    float x        = 0.f;      // position monde X (mètres)
    float z        = 0.f;      // position monde Z (mètres)
    float heading  = 0.f;      // cap en degrés (0 = Nord)
    float speed    = 0.f;      // vitesse km/h (négatif = marche arrière)

    float steeringAngle = 0.f; // angle volant : -450 à +450 deg
    float wheelAngle    = 0.f; // angle roues avant : -35 à +35 deg (calculé)

    // ── Animations (smooth, 0.0=fermé → 1.0=ouvert) ──────────────────────────
    float doorFLAngle = 0.f;   // porte avant gauche  (degrés, 0–65)
    float doorFRAngle = 0.f;   // porte avant droite
    float doorRLAngle = 0.f;   // porte arrière gauche
    float doorRRAngle = 0.f;   // porte arrière droite
    float trunkAngle  = 0.f;   // coffre               (0–70)
    float hoodAngle   = 0.f;   // capot                (0–60)
    float wheelRoll   = 0.f;   // rotation cumulative des roues (degrés)

    // ── États booléens ────────────────────────────────────────────────────────
    bool doorFL = false;
    bool doorFR = false;
    bool doorRL = false;
    bool doorRR = false;
    bool trunk  = false;
    bool hood   = false;

    bool lowBeam      = false;
    bool highBeam     = false;
    bool leftBlinker  = false;
    bool rightBlinker = false;
    bool hazard       = false;

    bool handbrake = true;

    // ── Blinker timer (interne) ───────────────────────────────────────────────
    float blinkerTimer   = 0.f;
    bool  blinkerVisible = true;

    // ── Méthodes ─────────────────────────────────────────────────────────────
    void update(float dt);
    void applyInput(bool accel, bool brake, bool left, bool right, float dt);

    // Helpers
    float speedMs() const { return speed * 0.2778f; } // km/h → m/s
};