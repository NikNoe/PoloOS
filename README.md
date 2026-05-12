# PoloOS

Tesla-style embedded interface for a VW Polo 9N3, running on a Raspberry Pi 5.  
Raylib prototype isolated on the `raylib-proto` branch; Qt merge planned.

---

## General Architecture

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
│    Traffic video                       RoadNetwork         │
│    (dashcam / camera)                  DayNightCycle       │
│                                        CarRenderer         │
└─────────────────────────────────────────────────────────────┘
                              │
                    ┌─────────▼──────────┐
                    │   Qt 6 / QML       │  ← future merge
                    │   Raspberry Pi 5   │
                    │   CAN bus          │
                    └────────────────────┘
```

## Project Structure

```
PoloOS/
├── assets/
│   ├── maps/
│   │   └── city.json              ← static map (nodes + segments)
│   ├── models/                    ← .glb meshes (Blender export)
│   │   ├── polo.glb
│   │   ├── door_lf.glb / door_rf.glb ...
│   │   └── wheel_fl.glb ...
│   └── circulation-video/         ← dashcam videos for YOLO
│
├── src/
│   ├── main.cpp                   ← main loop (lightweight)
│   ├── car/
│   │   ├── PoloCar.h/.cpp         ← pure car state (YOLO-ready)
│   │   └── CarRenderer.h/.cpp     ← Raylib 3D renderer
│   ├── scene/
│   │   ├── Camera.h/.cpp          ← 3D camera controller
│   │   └── RoadMap.h/.cpp         ← legacy basic road
│   ├── road/
│   │   ├── RoadNode.h             ← node (intersection, roundabout)
│   │   ├── RoadSegment.h          ← segment + Bezier curves
│   │   ├── RoadNetwork.h/.cpp     ← graph + JSON loading
│   │   └── RoadRenderer.h/.cpp    ← road + buildings renderer
│   ├── world/
│   │   ├── DayNightCycle.h/.cpp   ← day/night cycle + visibility
│   │   └── WorldManager.h/.cpp    ← global orchestration
│   ├── traffic/
│   │   ├── TrafficAgent.h/.cpp    ← AI car / YOLO object
│   │   └── Pedestrian.h/.cpp      ← pedestrian
│   ├── network/
│   │   ├── DetectedObject.h       ← shared struct YOLO↔Raylib
│   │   └── SceneReceiver.h/.cpp   ← UDP receiver + JSON parser
│   └── ui/
│       ├── DebugPanel.h/.cpp      ← debug overlay (F1)
│       └── HUD.h/.cpp             ← speedometer
│
├── yolo/
│   ├── detector.py                ← YOLO + OpenCV → UDP
│   ├── socket_sender.py           ← UDP JSON sender
│   └── fake_camera.py             ← reads video as camera feed
│
├── requirements/
│   ├── install.sh                 ← master cross-platform script
│   ├── requirements.txt           ← Python dependencies
│   ├── apt.txt                    ← Linux/Pi packages
│   └── brew.txt                   ← macOS packages
│
├── CMakeLists.txt
└── README.md
```

---

## Installation

### Prerequisites

| Platform | Requirements |
|---|---|
| macOS M1/M2/M3 | Homebrew (`brew.sh`) |
| Ubuntu / ThinkPad | apt (included) |
| Raspberry Pi 5 | Ubuntu 24.04 arm64 |

### Automated installation (single command)

```bash
chmod +x requirements/install.sh && ./requirements/install.sh
```

This script handles everything:
1. System dependencies (brew or apt depending on OS)
2. Raylib 5.5 (brew on Mac, compiled from source on Linux/Pi)
3. C++ build (cmake + make)
4. Python 3.13 venv + YOLO + OpenCV

---

## Running PoloOS

### 1. Raylib 3D interface only

```bash
cd build-raylib && ./PoloRaylib
```

### 2. With YOLO detection (full pipeline)

Terminal 1 — Raylib:
```bash
cd build-raylib && ./PoloRaylib
```

Terminal 2 — YOLO:
```bash
source .venv/bin/activate
python3 yolo/detector.py --video assets/circulation-video/Paris\ Drive\ 4K\ -\ Sunset\ Drive\ -\ France.mp4
```

---

## Keyboard Controls

| Key | Action |
|---|---|
| ↑ / ↓ | Accelerate / Brake |
| ← / → | Steer |
| `C` | Cycle camera mode (Follow / Orbit / Hood) |
| Right-click + drag | Orbit camera (Orbit mode) |
| Scroll wheel | Zoom |
| `Q` / `E` | Orbit rotation |
| `1` `2` `3` `4` | Doors FL FR RL RR |
| `T` | Boot / trunk |
| `O` | Hood / bonnet |
| `L` | Dipped headlights |
| `H` | Full-beam headlights |
| `Z` / `X` | Left / right turn signal |
| `SPACE` | Handbrake |
| `F1` | Debug Panel |
| `N` (held) | Speed up day/night cycle |

---

## YOLO → Raylib Pipeline

```
Dashcam video
     │
     ▼
detector.py (Python)
  - Reads frames (OpenCV)
  - Detects objects (YOLOv8)
  - Estimates approximate 3D position
  - Serialises to JSON
     │
     ▼  UDP port 5005
SceneReceiver.cpp (C++)
  - Receives UDP packets
  - Parses JSON → DetectedObject[]
  - Updates TrafficAgent[]
     │
     ▼
Raylib (rendering)
  - Displays detected cars/pedestrians on the map
```

### Socket JSON format

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

## Tech Stack

| Component | Technology |
|---|---|
| 3D interface (prototype) | Raylib 5.5 + C++17 |
| 3D interface (production) | Qt 6 / QML / Qt Quick3D |
| AI detection | YOLOv8 (Ultralytics) |
| Computer vision | OpenCV 4.13 |
| Communication | UDP socket (JSON) |
| 3D meshes | Blender → glTF/glb |
| CAN bus | SocketCAN + Qt SerialBus |
| Target platform | Raspberry Pi 5 (Ubuntu 24.04 arm64) |

---

## Roadmap

- [x] Raylib 3D interface with Polo glb model
- [x] Procedural road with Bezier curves
- [x] Day/night cycle
- [x] Debug Panel (F1)
- [x] YOLO + OpenCV pipeline installed
- [x] detector.py → SceneReceiver UDP
- [ ] TrafficAgent (AI vehicles)
- [ ] Pedestrians
- [ ] Road signs and traffic lights
- [ ] Door/boot animations (Blender armature)
- [ ] Qt 6 / QML merge
- [ ] CAN bus integration (RPM, speed, doors)
- [ ] Raspberry Pi 5 deployment
