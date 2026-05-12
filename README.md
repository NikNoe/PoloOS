# PoloOS

Interface embarquée style Tesla pour VW Polo 9N3, tournant sur Raspberry Pi 5.  
Prototype Raylib isolé sur branche `raylib-proto`, fusion Qt prévue.

---

## Architecture générale

```
┌─────────────────────────────────────────────────────────────┐
│                        PoloOS                               │
│                                                             │
│  ┌──────────────┐    UDP/JSON    ┌─────────────────────┐   │
│  │  Python/YOLO │ ────────────► │   Raylib C++ (3D)   │   │
│  │  + OpenCV    │               │   SceneReceiver      │   │
│  │  detector.py │               │   TrafficAgent       │   │
│  └──────┬───────┘               └──────────┬──────────┘   │
│         │                                   │              │
│    Vidéo circulation                   RoadNetwork         │
│    (dashcam / caméra)                  DayNightCycle       │
│                                        CarRenderer         │
└─────────────────────────────────────────────────────────────┘
                              │
                    ┌─────────▼──────────┐
                    │   Qt 6 / QML       │  ← fusion future
                    │   Raspberry Pi 5   │
                    │   CAN bus          │
                    └────────────────────┘
```

## Structure du projet

```
PoloOS/
├── assets/
│   ├── maps/
│   │   └── city.json              ← carte fixe (nœuds + segments)
│   ├── models/                    ← meshes .glb (Blender export)
│   │   ├── polo.glb
│   │   ├── door_lf.glb / door_rf.glb ...
│   │   └── wheel_fl.glb ...
│   └── circulation-video/         ← vidéos dashcam pour YOLO
│
├── src/
│   ├── main.cpp                   ← boucle principale (léger)
│   ├── car/
│   │   ├── PoloCar.h/.cpp         ← état pur voiture (YOLO-ready)
│   │   └── CarRenderer.h/.cpp     ← rendu 3D Raylib
│   ├── scene/
│   │   ├── Camera.h/.cpp          ← gestion caméra 3D
│   │   └── RoadMap.h/.cpp         ← route de base (legacy)
│   ├── road/
│   │   ├── RoadNode.h             ← nœud (intersection, rond-point)
│   │   ├── RoadSegment.h          ← segment + courbes Bezier
│   │   ├── RoadNetwork.h/.cpp     ← graphe + chargement JSON
│   │   └── RoadRenderer.h/.cpp    ← rendu route + bâtiments
│   ├── world/
│   │   ├── DayNightCycle.h/.cpp   ← cycle jour/nuit + visibilité
│   │   └── WorldManager.h/.cpp    ← orchestration globale
│   ├── traffic/
│   │   ├── TrafficAgent.h/.cpp    ← voiture IA / objet YOLO
│   │   └── Pedestrian.h/.cpp      ← piéton
│   ├── network/
│   │   ├── DetectedObject.h       ← struct partagée YOLO↔Raylib
│   │   └── SceneReceiver.h/.cpp   ← réception UDP + parse JSON
│   └── ui/
│       ├── DebugPanel.h/.cpp      ← panneau debug (F1)
│       └── HUD.h/.cpp             ← speedomètre
│
├── yolo/
│   ├── detector.py                ← YOLO + OpenCV → UDP
│   ├── socket_sender.py           ← envoi UDP JSON
│   └── fake_camera.py             ← lit vidéo comme caméra
│
├── requirements/
│   ├── install.sh                 ← script maître multi-plateforme
│   ├── requirements.txt           ← dépendances Python
│   ├── apt.txt                    ← paquets Linux/Pi
│   └── brew.txt                   ← paquets macOS
│
├── CMakeLists.txt
└── README.md
```

---

## Installation

### Prérequis

| Plateforme | Prérequis |
|---|---|
| macOS M1/M2/M3 | Homebrew (`brew.sh`) |
| Ubuntu / ThinkPad | apt (inclus) |
| Raspberry Pi 5 | Ubuntu 24.04 arm64 |

### Installation automatique (une seule commande)

```bash
chmod +x requirements/install.sh && ./requirements/install.sh
```

Ce script fait tout :
1. Dépendances système (brew ou apt selon l'OS)
2. Raylib 5.5 (brew sur Mac, compilé sur Linux/Pi)
3. Build C++ (cmake + make)
4. Python 3.13 venv + YOLO + OpenCV

---

## Lancer PoloOS

### 1. Interface 3D Raylib seule

```bash
cd build-raylib && ./PoloRaylib
```

### 2. Avec détection YOLO (pipeline complet)

Terminal 1 — Raylib :
```bash
cd build-raylib && ./PoloRaylib
```

Terminal 2 — YOLO :
```bash
source .venv/bin/activate
python3 yolo/detector.py --video assets/circulation-video/Paris\ Drive\ 4K\ -\ Sunset\ Drive\ -\ France.mp4
```

---

## Contrôles clavier

| Touche | Action |
|---|---|
| ↑ / ↓ | Accélérer / Freiner |
| ← / → | Direction |
| `C` | Changer mode caméra (Follow / Orbit / Hood) |
| Clic droit + glisser | Orbite caméra (mode Orbit) |
| Molette | Zoom |
| `Q` / `E` | Rotation orbite |
| `1` `2` `3` `4` | Portes FL FR RL RR |
| `T` | Coffre |
| `O` | Capot |
| `L` | Feux de croisement |
| `H` | Feux de route |
| `Z` / `X` | Clignotant gauche / droite |
| `ESPACE` | Frein à main |
| `F1` | Debug Panel |
| `N` (maintenu) | Accélérer le cycle jour/nuit |

---

## Pipeline YOLO → Raylib

```
Vidéo dashcam
     │
     ▼
detector.py (Python)
  - Lit frame par frame (OpenCV)
  - Détecte objets (YOLOv8)
  - Estime position 3D approximative
  - Sérialise en JSON
     │
     ▼  UDP port 5005
SceneReceiver.cpp (C++)
  - Reçoit paquets UDP
  - Parse JSON → DetectedObject[]
  - Met à jour TrafficAgent[]
     │
     ▼
Raylib (rendu)
  - Affiche voitures/piétons détectés sur la map
```

### Format JSON socket

```json
{
  "frame": 1042,
  "timestamp": 34.7,
  "objects": [
    { "class": "car",        "x": 12.3, "z": 45.1, "heading": 180.0, "confidence": 0.92 },
    { "class": "pedestrian", "x":  8.1, "z": 38.5, "heading":  90.0, "confidence": 0.87 },
    { "class": "stop_sign",  "x": 15.0, "z": 50.0, "heading":   0.0, "confidence": 0.95 }
  ]
}
```

---

## Stack technique

| Composant | Technologie |
|---|---|
| Interface 3D (proto) | Raylib 5.5 + C++17 |
| Interface 3D (prod) | Qt 6 / QML / Qt Quick3D |
| Détection IA | YOLOv8 (Ultralytics) |
| Vision | OpenCV 4.13 |
| Communication | UDP socket (JSON) |
| Meshes 3D | Blender → glTF/glb |
| CAN bus | SocketCAN + Qt SerialBus |
| Cible | Raspberry Pi 5 (Ubuntu 24.04 arm64) |

---

## Roadmap

- [x] Interface 3D Raylib avec Polo glb
- [x] Route procédurale avec courbes Bezier
- [x] Cycle jour/nuit
- [x] Debug Panel (F1)
- [x] Pipeline YOLO + OpenCV installé
- [x] detector.py → SceneReceiver UDP
- [ ] TrafficAgent (voitures IA)
- [ ] Piétons
- [ ] Signalisation (feux, panneaux)
- [ ] Animations portes/coffre (Blender armature)
- [ ] Fusion Qt 6 / QML
- [ ] Intégration CAN bus (RPM, vitesse, portes)
- [ ] Déploiement Raspberry Pi 5