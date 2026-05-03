# PoloOS — raylib-proto

Prototype 3D isolé sur branche orpheline `raylib-proto`.
Objectif : valider les animations, la physique et le rendu avant fusion dans Qt.

## Build

```bash
mkdir build && cd build
cmake ..
make -j$(nproc)
./PoloRaylib
```

## Contrôles

| Touche | Action |
|--------|--------|
| ↑ / ↓ | Accélérer / Freiner |
| ← / → | Direction |
| `1` `2` `3` `4` | Portes FL FR RL RR |
| `T` | Coffre |
| `O` | Capot |
| `L` | Feux de croisement |
| `H` | Feux de route |
| `Z` / `X` | Cligno gauche / droite |
| `ESPACE` | Frein à main |
| `C` | Changer mode caméra (Follow / Orbit / Hood) |
| `Q` / `E` | Rotation orbite |

## Structure

```
src/
  car/
    PoloCar.h/.cpp       ← état pur (réutilisable dans Qt)
    CarRenderer.h/.cpp   ← rendu Raylib (sera remplacé par mesh .glb)
  scene/
    RoadMap.h/.cpp       ← route + environnement
  ui/
    HUD.h/.cpp           ← overlay 2D
  main.cpp
```

## Fusion Qt prévue

`PoloCar.h` sera porté tel quel dans PoloOS comme `QObject` avec `Q_PROPERTY`.
`CarRenderer` sera remplacé par `Polo.qml` + `View3D`.