# PoloOS — Embedded Instrument Cluster

> Tesla-style dashboard OS for the Volkswagen Polo IV (9N3), running on Raspberry Pi 5.

[![Docs — Qt](https://github.com/NikNoe/PoloOS/actions/workflows/docs-main.yml/badge.svg)](https://github.com/NikNoe/PoloOS/actions/workflows/docs-main.yml)
[![Docs — Raylib](https://github.com/NikNoe/PoloOS/actions/workflows/docs-raylib.yml/badge.svg)](https://github.com/NikNoe/PoloOS/actions/workflows/docs-raylib.yml)
[![Qt HTML Docs](https://img.shields.io/badge/docs-Qt%20IHM-blue)](https://niknoe.github.io/PoloOS/qt/)
[![Raylib HTML Docs](https://img.shields.io/badge/docs-Raylib%203D-blue)](https://niknoe.github.io/PoloOS/raylib/)
[![PoloOS-Qt.pdf](https://img.shields.io/badge/PDF-PoloOS--Qt-red)](https://github.com/NikNoe/PoloOS/raw/main/docs/PoloOS-Qt.pdf)
[![PoloOS-Raylib.pdf](https://img.shields.io/badge/PDF-PoloOS--Raylib-red)](https://github.com/NikNoe/PoloOS/raw/raylib-proto/docs/PoloOS-Raylib.pdf)

---

## Overview

PoloOS replaces the factory instrument cluster of a 2006 Volkswagen Polo IV (9N3) with a fully custom, touch-capable dashboard running on a Raspberry Pi 5. The interface decodes live CAN bus data (VAG PQ24 protocol) and presents it through a Qt 6 / QML UI designed around Tesla's minimalist aesthetic — dark theme, smooth 60 FPS animations, and context-aware 3D vehicle visualisation.

<img width="1276" height="720" alt="PoloOS dashboard overview" src="https://github.com/user-attachments/assets/4db662ac-0abb-4c48-9115-0f30fe962cd3" />

---

## Architecture

```
┌─────────────────────────────────────────────────────────┐
│                    Volkswagen Polo 9N3                  │
│   Traction CAN 500 kbps ──┬── Comfort CAN 100 kbps     │
│                           │                             │
│              32-pin Tyco MQS connector                  │
└───────────────────────────┼─────────────────────────────┘
                            │
                    USB2CAN (SLCAN)
                            │
┌───────────────────────────▼─────────────────────────────┐
│                   Raspberry Pi 5                        │
│                                                         │
│  SocketCAN (can0 / slcan0)                              │
│       │                                                 │
│  ┌────▼────────────────────────────────────┐            │
│  │  C++ backend  (CanReader + CanHandler)  │            │
│  │  • Frame decode — VAG PQ24 IDs          │            │
│  │  • QObject properties exposed to QML    │            │
│  └────────────────────┬────────────────────┘            │
│                       │  Qt bindings                    │
│  ┌────────────────────▼────────────────────┐            │
│  │  QML frontend  (Qt 6.10 / Quick3D)      │            │
│  │  • Main.qml — root window               │            │
│  │  • pages/   — 8 instrument pages        │            │
│  │  • vehicle/ — 3D Polo model (GLB)       │            │
│  │  • components/ — reusable widgets       │            │
│  └─────────────────────────────────────────┘            │
│                                                         │
│  14" touchscreen (target)                               │
└─────────────────────────────────────────────────────────┘
```

---

## Features

### 1 — Engine & Propulsion
Real-time RPM (CAN ID `0x280`) and engine load used to compute instantaneous power output. Multiple engine-state indicators with animated transitions.

<img width="1276" height="716" alt="Engine page" src="https://github.com/user-attachments/assets/7edc4973-7d8d-45d9-8a0d-64da8c0ca145" />

### 2 — Chassis & Dynamics
Live steering angle animation (`0x0C2`), individual ABS wheel-speed monitoring (`0x4A0`), and critical-warning blink effects for ABS / ESP / traction-control events.

<img width="1273" height="717" alt="Chassis page" src="https://github.com/user-attachments/assets/648809aa-f6b0-42b1-9cfd-dfe882ce7420" />

### 3 — Energy & Thermal
Range estimation from the remaining fuel level. Advanced thermal monitoring for coolant, oil, ambient and intake temperatures — threshold alerts styled after Tesla's battery thermal system.

<img width="1277" height="718" alt="Energy page" src="https://github.com/user-attachments/assets/13dca677-7d28-49d9-ba16-900345d1400a" />

### 4 — Body Control
A/C state, electric window opening percentage, interactive door / bonnet / boot status, passive safety (seat-presence sensors, seatbelt locks), and real-time central-locking pulse animation.

<img width="1275" height="717" alt="Body control page" src="https://github.com/user-attachments/assets/4fe7ebe9-a1a4-484c-8f62-018eafa45aeb" />

### 5 — Diagnostics
CAN bus health indicators, ECU online/offline status (Engine ECU, ABS, BCM, Instrument), and build metadata (Git hash, build date, VIN).

<img width="1273" height="719" alt="Diagnostics page" src="https://github.com/user-attachments/assets/946652de-5c18-4506-a3ee-1ae33a3d1806" />

---

## Tech Stack

| Component | Technology |
|-----------|-----------|
| UI framework | Qt 6.10 — C++ / QML / Quick3D |
| CAN interface | SocketCAN (`can0`) — SLCAN protocol |
| 3D assets | Custom GLB mesh (Polo 9N3 body) |
| Target OS | Ubuntu 24.04 with SocketCAN kernel module |
| Dev tooling | CMake 3.16+, Qt Creator, SavvyCAN, Wireshark |
| YOLO pipeline | Python 3 — Ultralytics, OpenCV (`raylib-proto`) |
| Documentation | Doxygen 1.12 + Sphinx / Furo |

---

## Hardware

| Component | Detail |
|-----------|--------|
| Vehicle | Volkswagen Polo IV 9N3 — VAG PQ24 platform |
| Compute | Raspberry Pi 5 (embedded target) |
| Dev machines | ThinkPad T450 (Ubuntu x86_64), MacBook Air M2 (macOS) |
| CAN adapter | USB2CAN — SLCAN protocol |
| Connector | 32-pin Tyco MQS (instrument cluster harness) |
| CAN buses | Traction 500 kbps · Comfort 100 kbps |
| Display (target) | 14" touchscreen |

---

## Documentation

| Branch | HTML | PDF |
|--------|------|-----|
| `main` — Qt IHM | [niknoe.github.io/PoloOS/qt](https://niknoe.github.io/PoloOS/qt/) | [PoloOS-Qt.pdf](https://github.com/NikNoe/PoloOS/raw/main/docs/PoloOS-Qt.pdf) |
| `raylib-proto` — 3D engine | [niknoe.github.io/PoloOS/raylib](https://niknoe.github.io/PoloOS/raylib/) | [PoloOS-Raylib.pdf](https://github.com/NikNoe/PoloOS/raw/raylib-proto/docs/PoloOS-Raylib.pdf) |

Docs are regenerated automatically on every push by the CI workflows.

---

## Getting Started

Clone the repository and run the unified installer:

```bash
git clone https://github.com/NikNoe/PoloOS.git
cd PoloOS
```

| Platform | Method | Qt Version |
|----------|--------|------------|
| macOS M1/M2/M3 | qt-cmake + terminal or Qt Creator | 6.10.1 |
| Ubuntu / ThinkPad | Qt Creator (recommended) or qt-cmake | 6.10.2 |
| Raspberry Pi 5 | qt-cmake terminal | 6.10.x |

The script auto-detects the platform, installs Qt6 dependencies, sets up the Python venv, and builds `appPoloOS` into `build-mac/`, `build-linux/`, or `build-pi/` respectively.

> **macOS note:** Qt 6 must be installed first via the [Qt online installer](https://www.qt.io/download-open-source). The script locates `qt-cmake` automatically.

### Qt Creator (recommended)

1. Open Qt Creator
2. **File → Open File or Project** → select `CMakeLists.txt`
3. Qt Creator auto-detects Qt 6.10.x and configures the project
4. Click **Build** (hammer icon)

To include Raylib support (`raylib-proto` branch):

```bash
./requirements/install.sh --raylib
```

---

## Known Limitations

- **SocketCAN not available on macOS** — CAN bus is disabled; the app runs in UI-only mode
- **Qt 6.4.2 (Ubuntu `apt`) is broken for Quick3DHelpers** — use the [Qt Online Installer](https://www.qt.io/download-open-source) to get Qt 6.10.x
- **Qt6Location not available on Pi via `apt`** — MapPage is disabled on Raspberry Pi builds

---

## Roadmap

- CAN frame analysis, filtering and proprietary ID decoding (reverse engineering ongoing)
- Port to 14" touchscreen via Raspberry Pi and physical dashboard integration
- YOLO real-time traffic detection overlaid on the 3D scene (`raylib-proto`)
- OBD-II / UDS diagnostic session support

---

## Author

**Ian Kenny** — Embedded Systems & Intelligent Transport Engineer
