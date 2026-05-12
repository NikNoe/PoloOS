#!/usr/bin/env bash
# Install build dependencies for PoloOS on macOS, Ubuntu x86_64, and Pi 5 (aarch64).
set -euo pipefail

OS="$(uname -s)"
ARCH="$(uname -m)"

install_macos() {
    echo "[macOS] Installing via Homebrew..."
    brew update
    brew install qt@6 cmake ninja
    echo "export PATH=\"\$(brew --prefix qt@6)/bin:\$PATH\"" >> ~/.zprofile
    echo "[macOS] Done. Reload your shell or run: source ~/.zprofile"
}

install_ubuntu() {
    echo "[Ubuntu/Pi] Installing via apt..."
    sudo apt-get update
    sudo apt-get install -y \
        cmake ninja-build \
        qt6-base-dev qt6-declarative-dev qt6-quick3d-dev \
        qml6-module-qtquick qml6-module-qtquick-controls \
        qt6-serialbus-dev qt6-serialport-dev \
        libqt6shadertools6-dev \
        can-utils
    echo "[Ubuntu/Pi] Done."
}

case "$OS" in
    Darwin)  install_macos ;;
    Linux)   install_ubuntu ;;
    *)       echo "Unsupported OS: $OS"; exit 1 ;;
esac
