#!/usr/bin/env bash
# =============================================================================
# PoloOS — install.sh
# Script maître multi-plateforme
# Ubuntu / Raspberry Pi 5 / macOS M1-M2-M3
# Usage : chmod +x requirements/install.sh && ./requirements/install.sh
# =============================================================================

set -e

OS="$(uname -s)"
ARCH="$(uname -m)"
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BUILD_DIR="$ROOT/build-raylib"
VENV_DIR="$ROOT/.venv"

echo ""
echo "======================================"
echo "  PoloOS — Installation complète"
echo "  OS: $OS  ARCH: $ARCH"
echo "  Root: $ROOT"
echo "======================================"
echo ""

# ── 1. Dépendances système ────────────────────────────────────────────────────
echo "[1/5] Dépendances système..."

if [ "$OS" = "Linux" ]; then
    sudo apt-get update -qq
    sudo apt-get install -y \
        cmake build-essential git pkg-config \
        libgl1-mesa-dev libx11-dev libxrandr-dev \
        libxi-dev libxcursor-dev libxinerama-dev \
        libwayland-dev libxkbcommon-dev \
        python3 python3-pip python3-venv

    if [ "$ARCH" = "aarch64" ]; then
        echo "  → Raspberry Pi détecté"
        sudo apt-get install -y libgles2-mesa-dev libegl1-mesa-dev
    fi

elif [ "$OS" = "Darwin" ]; then
    export PATH="/opt/homebrew/bin:$PATH"
    if ! command -v brew &>/dev/null; then
        echo "  → Homebrew non trouvé — installe-le depuis https://brew.sh"
        exit 1
    fi
    brew install cmake git pkg-config raylib python3
else
    echo "OS non supporté : $OS"
    exit 1
fi

echo "  ✓ Dépendances système OK"

# ── 2. Raylib (Linux/Pi seulement — macOS via brew) ───────────────────────────
echo ""
echo "[2/5] Raylib..."

if [ "$OS" = "Linux" ]; then
    if pkg-config --modversion raylib &>/dev/null; then
        echo "  ✓ Raylib déjà installé ($(pkg-config --modversion raylib))"
    else
        RAYLIB_DIR="/tmp/raylib-5.5"
        if [ ! -d "$RAYLIB_DIR" ]; then
            git clone --depth 1 --branch 5.5 \
                https://github.com/raysan5/raylib.git "$RAYLIB_DIR"
        fi
        mkdir -p "$RAYLIB_DIR/build" && cd "$RAYLIB_DIR/build"
        cmake .. -DBUILD_SHARED_LIBS=OFF \
                 -DPLATFORM=Desktop \
                 -DCMAKE_BUILD_TYPE=Release
        make -j"$(nproc)"
        sudo make install
        sudo ldconfig
        cd "$ROOT"
        echo "  ✓ Raylib 5.5 installé"
    fi
else
    echo "  ✓ Raylib via Homebrew (déjà fait étape 1)"
fi

# ── 4. Python venv + dépendances YOLO ────────────────────────────────────────
echo ""
echo "[4/5] Python / YOLO / OpenCV..."

# Cherche Python 3.13 dans l'ordre de priorité
find_python() {
    for cmd in python3.13 \
               /Library/Frameworks/Python.framework/Versions/3.13/bin/python3 \
               /opt/homebrew/bin/python3.13 \
               /usr/bin/python3.13; do
        if command -v "$cmd" &>/dev/null; then
            echo "$cmd"
            return 0
        fi
    done
    return 1
}

PYTHON=$(find_python) || {
    echo "  ✗ Python 3.13 non trouvé"
    echo "    Installe-le depuis https://python.org ou via brew install python@3.13"
    exit 1
}

echo "  → Python trouvé : $PYTHON ($($PYTHON --version))"

# Crée le venv seulement si absent
if [ ! -d "$VENV_DIR" ]; then
    $PYTHON -m venv "$VENV_DIR"
    echo "  → venv créé : $VENV_DIR"
else
    echo "  → venv existant réutilisé"
fi

source "$VENV_DIR/bin/activate"
pip install --upgrade pip -q
pip install -r "$ROOT/requirements/requirements.txt" -q
deactivate

echo "  ✓ Python venv OK"

# ── 5. Vérification finale ────────────────────────────────────────────────────
echo ""
echo "[5/5] Vérification..."

# C++
if [ -f "$BUILD_DIR/PoloRaylib" ]; then
    echo "  ✓ PoloRaylib binary OK"
else
    echo "  ✗ PoloRaylib binary manquant"
    exit 1
fi

# Python
source "$VENV_DIR/bin/activate"
python3 -c "import ultralytics; print('  ✓ YOLO', ultralytics.__version__)" 2>/dev/null \
    || echo "  ✗ YOLO non disponible"
python3 -c "import cv2; print('  ✓ OpenCV', cv2.__version__)" 2>/dev/null \
    || echo "  ✗ OpenCV non disponible"
deactivate

echo ""
echo "======================================"
echo "  Installation terminée !"
echo ""
echo "  Lancer PoloOS :"
echo "    cd $BUILD_DIR && ./PoloRaylib"
echo ""
echo "  Lancer YOLO detector :"
echo "    source .venv/bin/activate"
echo "    python3 yolo/detector.py"
echo "======================================"
echo ""