#!/usr/bin/env bash
# =============================================================================
# setup.sh — PoloOS raylib-proto
# Installe les dépendances et compile sur Ubuntu / macOS / Raspberry Pi
# Usage : chmod +x setup.sh && ./setup.sh
# =============================================================================

set -e  # arrête si une commande échoue

OS="$(uname -s)"
ARCH="$(uname -m)"
RAYLIB_VERSION="5.5"
BUILD_DIR="build-raylib"

echo ""
echo "======================================"
echo "  PoloOS raylib-proto — setup"
echo "  OS: $OS  ARCH: $ARCH"
echo "======================================"
echo ""

# ── 1. Dépendances système ────────────────────────────────────────────────────

if [ "$OS" = "Linux" ]; then
    echo "[1/3] Installation des dépendances Linux..."
    sudo apt-get update -qq
    sudo apt-get install -y \
        cmake build-essential git \
        libgl1-mesa-dev \
        libx11-dev libxrandr-dev libxi-dev \
        libxcursor-dev libxinerama-dev \
        libwayland-dev libxkbcommon-dev \
        pkg-config

    # Raspberry Pi : dépendances GPU supplémentaires
    if [ "$ARCH" = "aarch64" ] || [ "$ARCH" = "armv7l" ]; then
        echo "[1/3] Raspberry Pi détecté — dépendances GPU..."
        sudo apt-get install -y \
            libgles2-mesa-dev libegl1-mesa-dev
    fi

elif [ "$OS" = "Darwin" ]; then
    echo "[1/3] Installation des dépendances macOS..."
    # Vérifie que Homebrew est présent
    if ! command -v brew &>/dev/null; then
        echo "Homebrew non trouvé — installation..."
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    fi
    brew install cmake git pkg-config
    # Sur macOS les frameworks OpenGL/Cocoa sont natifs, rien d'autre à installer
else
    echo "OS non supporté : $OS"
    exit 1
fi

echo ""
echo "[1/3] Dépendances OK"

# ── 2. Compilation de Raylib depuis les sources ───────────────────────────────

echo ""
echo "[2/3] Compilation de Raylib $RAYLIB_VERSION..."

if pkg-config --modversion raylib &>/dev/null; then
    INSTALLED=$(pkg-config --modversion raylib)
    echo "      Raylib $INSTALLED déjà installé — skip"
else
    RAYLIB_DIR="/tmp/raylib-$RAYLIB_VERSION"

    if [ ! -d "$RAYLIB_DIR" ]; then
        git clone --depth 1 --branch "$RAYLIB_VERSION" \
            https://github.com/raysan5/raylib.git "$RAYLIB_DIR"
    fi

    mkdir -p "$RAYLIB_DIR/build"
    cd "$RAYLIB_DIR/build"

    if [ "$OS" = "Darwin" ]; then
        cmake .. -DBUILD_SHARED_LIBS=OFF \
                 -DPLATFORM=Desktop \
                 -DCMAKE_BUILD_TYPE=Release
    elif [ "$ARCH" = "aarch64" ] || [ "$ARCH" = "armv7l" ]; then
        cmake .. -DBUILD_SHARED_LIBS=OFF \
                 -DPLATFORM=Desktop \
                 -DUSE_WAYLAND=OFF \
                 -DCMAKE_BUILD_TYPE=Release
    else
        cmake .. -DBUILD_SHARED_LIBS=OFF \
                 -DPLATFORM=Desktop \
                 -DCMAKE_BUILD_TYPE=Release
    fi

    make -j"$(nproc 2>/dev/null || sysctl -n hw.logicalcpu)"
    sudo make install

    if [ "$OS" = "Linux" ]; then
        sudo ldconfig
    fi

    cd - > /dev/null
    echo "      Raylib $RAYLIB_VERSION installé"
fi

# ── 3. Build du projet ────────────────────────────────────────────────────────

echo ""
echo "[3/3] Build de PoloRaylib..."

# Revenir à la racine du projet (au cas où on a navigué)
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake .. -DCMAKE_BUILD_TYPE=Release
make -j"$(nproc 2>/dev/null || sysctl -n hw.logicalcpu)"

echo ""
echo "======================================"
echo "  Build terminé !"
echo "  Lancer : cd $BUILD_DIR && ./PoloRaylib"
echo "======================================"
echo ""