#!/usr/bin/env bash
# ─────────────────────────────────────────────────────────────────────────────
# PoloOS — unified dependency installer
#
# Usage:
#   ./requirements/install.sh [OPTIONS]
#
# Options:
#   --raylib      Also install Raylib (for raylib-proto branch)
#   --no-build    Skip the CMake build step
#   --no-python   Skip Python venv setup
#   -h, --help    Show this help
#
# Supported platforms:
#   macOS  (Apple Silicon M1/M2/M3, x86_64)
#   Linux  x86_64  — Ubuntu / ThinkPad
#   Linux  aarch64 — Raspberry Pi 5 (Ubuntu 24.04)
# ─────────────────────────────────────────────────────────────────────────────
set -euo pipefail

# ── CLI flags ─────────────────────────────────────────────────────────────────
WITH_RAYLIB=false
SKIP_BUILD=false
SKIP_PYTHON=false

for arg in "$@"; do
    case "$arg" in
        --raylib)    WITH_RAYLIB=true ;;
        --no-build)  SKIP_BUILD=true ;;
        --no-python) SKIP_PYTHON=true ;;
        -h|--help)
            sed -n '2,20p' "$0" | sed 's/^# \{0,1\}//'
            exit 0
            ;;
    esac
done

# ── Paths ─────────────────────────────────────────────────────────────────────
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"

# ── Platform detection ────────────────────────────────────────────────────────
OS="$(uname -s)"
ARCH="$(uname -m)"

case "$OS/$ARCH" in
    Darwin/arm64|Darwin/x86_64) PLATFORM="macos";  BUILD_DIR="build-mac"   ;;
    Linux/x86_64)               PLATFORM="ubuntu"; BUILD_DIR="build-linux" ;;
    Linux/aarch64)              PLATFORM="pi";     BUILD_DIR="build-pi"    ;;
    *)
        echo "Unsupported platform: $OS / $ARCH"
        exit 1
        ;;
esac

# ── Colors (TTY-safe) ─────────────────────────────────────────────────────────
if [[ -t 1 ]]; then
    C_RESET="\033[0m"; C_BOLD="\033[1m"; C_DIM="\033[2m"
    C_GREEN="\033[32m"; C_YELLOW="\033[33m"; C_RED="\033[31m"; C_CYAN="\033[36m"
else
    C_RESET=""; C_BOLD=""; C_DIM=""; C_GREEN=""; C_YELLOW=""; C_RED=""; C_CYAN=""
fi

# ── Logging helpers ───────────────────────────────────────────────────────────
log()  { printf "${C_CYAN}${C_BOLD}▶${C_RESET} %s\n" "$*"; }
ok()   { printf "${C_GREEN}✓${C_RESET} %s\n" "$*"; }
warn() { printf "${C_YELLOW}⚠${C_RESET} %s\n" "$*"; }
fail() { printf "${C_RED}✗${C_RESET} %s\n" "$*"; }
hr()   { printf "${C_DIM}%s${C_RESET}\n" "────────────────────────────────────────────────────────────"; }

# ── Summary tracking (bash 3.2-compatible indexed arrays) ─────────────────────
SUM_OK=()
SUM_SKIP=()
SUM_FAIL=()
sum_ok()   { SUM_OK+=("$1");   }
sum_skip() { SUM_SKIP+=("$1"); }
sum_fail() { SUM_FAIL+=("$1"); }

# ═════════════════════════════════════════════════════════════════════════════
# macOS
# ═════════════════════════════════════════════════════════════════════════════
install_homebrew() {
    if command -v brew &>/dev/null; then
        ok "Homebrew $(brew --version | head -1)"
        sum_ok "Homebrew"
        return
    fi
    log "Installing Homebrew..."
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    # Apple Silicon: brew lands in /opt/homebrew, not in PATH by default
    if [[ "$ARCH" == "arm64" && -x /opt/homebrew/bin/brew ]]; then
        eval "$(/opt/homebrew/bin/brew shellenv)"
    fi
    ok "Homebrew installed"
    sum_ok "Homebrew"
}

install_brew_tools() {
    log "brew install cmake git doxygen graphviz ..."
    brew install cmake git doxygen graphviz
    ok "cmake / git / doxygen / graphviz"
    sum_ok "cmake / git / doxygen / graphviz"
}

# Locate qt-cmake, trying in order:
#   1. Existing build cache (fastest, exact match)
#   2. ~/Qt   (Qt online installer default)
#   3. /Volumes/*/...  (external drives — matches this project's setup)
#   4. /opt/Qt
find_qt_macos() {
    # 1 ── build cache
    local cache="$REPO_ROOT/build-mac/CMakeCache.txt"
    if [[ -f "$cache" ]]; then
        local qt6dir
        qt6dir="$(grep '^Qt6_DIR:PATH=' "$cache" 2>/dev/null | cut -d= -f2 || true)"
        if [[ -n "$qt6dir" ]]; then
            local candidate="${qt6dir%/lib/cmake/Qt6}/bin/qt-cmake"
            if [[ -x "$candidate" ]]; then
                echo "$candidate"
                return 0
            fi
        fi
    fi

    # 2-4 ── filesystem search (newest version wins)
    # Sort numerically on the version segment (field that looks like 6.x.x)
    local found
    found="$(find "$HOME/Qt" /Volumes /opt/Qt \
                  -maxdepth 8 -name "qt-cmake" -type f 2>/dev/null \
              | awk -F/ '{
                    ver=0
                    for(i=1;i<=NF;i++)
                        if($i ~ /^[0-9]+\.[0-9]+\.[0-9]+$/) {
                            n=split($i,v,".")
                            ver=v[1]*100000+v[2]*1000+v[3]
                        }
                    print ver, $0
                }' \
              | sort -n | tail -1 | cut -d' ' -f2- || true)"
    echo "$found"
}

install_macos() {
    log "Platform: macOS ($ARCH)"
    install_homebrew
    install_brew_tools

    log "Locating Qt6 (online installer) ..."
    QT_CMAKE="$(find_qt_macos || true)"

    if [[ -z "$QT_CMAKE" ]]; then
        warn "qt-cmake not found under ~/Qt, /Volumes, or /opt/Qt"
        warn "Install Qt 6 via https://www.qt.io/download-open-source and re-run"
        sum_skip "Qt6 (not found — install via Qt online installer)"
        SKIP_BUILD=true
    else
        local qt_ver
        qt_ver="$(echo "$QT_CMAKE" | grep -oE '[0-9]+\.[0-9]+\.[0-9]+' | head -1 || echo "?")"
        ok "Qt $qt_ver → $QT_CMAKE"
        QT_CMAKE_PREFIX="$(dirname "$(dirname "$QT_CMAKE")")"
        export QT_CMAKE_PREFIX
        sum_ok "Qt $qt_ver"
    fi
}

# ═════════════════════════════════════════════════════════════════════════════
# Shared apt package list (Ubuntu x86_64 and Pi)
# ═════════════════════════════════════════════════════════════════════════════
APT_COMMON=(
    cmake
    build-essential
    git
    doxygen
    graphviz
    qt6-base-dev
    qt6-declarative-dev
    libqt6serialbus6-dev
    libqt6serialport6-dev
    qt6-quick3d-dev
    libqt6shadertools6-dev
    qt6-l10n-tools
    libqt6quickcontrols2-6
    can-utils
)

# ═════════════════════════════════════════════════════════════════════════════
# Ubuntu x86_64 (ThinkPad)
# ═════════════════════════════════════════════════════════════════════════════
install_ubuntu_x86() {
    log "Platform: Ubuntu x86_64"
    sudo apt-get update -qq
    sudo apt-get install -y "${APT_COMMON[@]}"
    ok "All apt packages installed"
    sum_ok "cmake / git / doxygen / graphviz"
    sum_ok "Qt6 (system)"
}

# ═════════════════════════════════════════════════════════════════════════════
# Raspberry Pi 5 — aarch64 Ubuntu 24.04
# ═════════════════════════════════════════════════════════════════════════════
install_pi() {
    log "Platform: Raspberry Pi 5 (aarch64)"
    sudo apt-get update -qq
    sudo apt-get install -y \
        "${APT_COMMON[@]}" \
        libgles2-mesa-dev \
        libegl1-mesa-dev

    sum_ok "cmake / git / doxygen / graphviz"
    sum_ok "Qt6 core (system)"

    # Qt6Location is absent from Ubuntu 24.04 arm64 apt repos
    if apt-cache show qt6-location-dev &>/dev/null 2>&1; then
        sudo apt-get install -y qt6-location-dev
        ok "Qt6Location installed"
        sum_ok "Qt6Location (MapPage enabled)"
    else
        warn "qt6-location-dev absent from apt — MapPage disabled (expected on Pi)"
        sum_skip "Qt6Location (MapPage disabled)"
    fi

    ok "All apt packages installed"
}

# ═════════════════════════════════════════════════════════════════════════════
# Python venv
# ═════════════════════════════════════════════════════════════════════════════
setup_python_venv() {
    local req_file="$SCRIPT_DIR/requirements.txt"

    if [[ ! -f "$req_file" ]]; then
        warn "requirements/requirements.txt not found — skipping Python venv"
        sum_skip "Python venv (requirements.txt missing)"
        return
    fi

    log "Setting up Python virtual environment (.venv) ..."
    cd "$REPO_ROOT"
    python3 -m venv .venv
    .venv/bin/pip install --upgrade pip -q
    .venv/bin/pip install -r "$req_file"

    ok "Python venv ready — activate with: source .venv/bin/activate"
    sum_ok "Python venv (.venv/)"

    # PyTorch hint
    if ! .venv/bin/python -c "import torch" &>/dev/null; then
        warn "PyTorch not installed — see requirements/requirements.txt for instructions"
        sum_skip "PyTorch (install manually — platform-specific wheel)"
    else
        local torch_ver
        torch_ver="$(.venv/bin/python -c "import torch; print(torch.__version__)" 2>/dev/null || echo "?")"
        ok "PyTorch $torch_ver"
        sum_ok "PyTorch $torch_ver"
    fi
}

# ═════════════════════════════════════════════════════════════════════════════
# CMake build
# ═════════════════════════════════════════════════════════════════════════════
build_app() {
    log "Building PoloOS → $BUILD_DIR/ ..."
    cd "$REPO_ROOT"

    local cores
    cores="$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 2)"

    if [[ "$PLATFORM" == "macos" ]]; then
        "$QT_CMAKE" -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release
    else
        cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release
    fi

    if cmake --build "$BUILD_DIR" --parallel "$cores"; then
        ok "Build complete → $BUILD_DIR/"
        sum_ok "Build ($BUILD_DIR/)"
    else
        fail "Build failed — check output above"
        sum_fail "Build ($BUILD_DIR/) — FAILED"
    fi
}

# ═════════════════════════════════════════════════════════════════════════════
# Post-install verification
# ═════════════════════════════════════════════════════════════════════════════
verify() {
    log "Verifying installation ..."

    # Qt binary
    local binary="$REPO_ROOT/$BUILD_DIR/appPoloOS"
    if [[ -f "$binary" ]]; then
        ok "Binary: $BUILD_DIR/appPoloOS"
        sum_ok "Binary: $BUILD_DIR/appPoloOS"
    else
        warn "Binary not found at $BUILD_DIR/appPoloOS (build may have failed or been skipped)"
        sum_skip "Binary (not built)"
    fi

    # YOLO import
    local venv_py="$REPO_ROOT/.venv/bin/python"
    if [[ -x "$venv_py" ]]; then
        if "$venv_py" -c "import ultralytics" &>/dev/null; then
            local ul_ver
            ul_ver="$("$venv_py" -c "import ultralytics; print(ultralytics.__version__)" 2>/dev/null || echo "?")"
            ok "YOLO (ultralytics $ul_ver) importable"
            sum_ok "YOLO (ultralytics $ul_ver)"
        else
            warn "ultralytics not importable — run: .venv/bin/pip install ultralytics"
            sum_fail "YOLO import — FAILED"
        fi
    else
        sum_skip "YOLO (Python venv not set up)"
    fi
}

# ═════════════════════════════════════════════════════════════════════════════
# ─── Raylib section (raylib-proto branch) ────────────────────────────────────
# Invoked only when --raylib flag is passed.
# ═════════════════════════════════════════════════════════════════════════════
install_raylib_deps() {
    hr
    log "Raylib dependencies (--raylib)"

    case "$PLATFORM" in
        # ── macOS ─────────────────────────────────────────────────────────
        macos)
            brew install raylib
            ok "raylib installed via Homebrew"
            sum_ok "Raylib (Homebrew)"
            ;;

        # ── Ubuntu x86_64 ─────────────────────────────────────────────────
        ubuntu)
            if apt-cache show libraylib-dev &>/dev/null 2>&1; then
                sudo apt-get install -y libraylib-dev
                ok "libraylib-dev installed"
                sum_ok "Raylib (apt)"
            else
                log "Building Raylib 5.x from source (not in apt) ..."
                sudo apt-get install -y \
                    libgl1-mesa-dev libx11-dev libxrandr-dev \
                    libxi-dev libxcursor-dev libxinerama-dev
                local tmp
                tmp="$(mktemp -d)"
                git clone --depth 1 --branch 5.0 \
                    https://github.com/raysan5/raylib.git "$tmp/raylib"
                cmake -S "$tmp/raylib" -B "$tmp/raylib/build" \
                    -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF
                cmake --build "$tmp/raylib/build" --parallel "$(nproc)"
                sudo cmake --install "$tmp/raylib/build"
                rm -rf "$tmp"
                ok "Raylib 5 built and installed to /usr/local"
                sum_ok "Raylib 5 (built from source)"
            fi
            ;;

        # ── Raspberry Pi 5 — GLES2 / DRM ──────────────────────────────────
        pi)
            log "Building Raylib 5.x for Pi (GLES2/DRM) ..."
            sudo apt-get install -y \
                libgles2-mesa-dev libegl1-mesa-dev \
                libx11-dev libxrandr-dev libxi-dev \
                libxcursor-dev libxinerama-dev
            local tmp
            tmp="$(mktemp -d)"
            git clone --depth 1 --branch 5.0 \
                https://github.com/raysan5/raylib.git "$tmp/raylib"
            cmake -S "$tmp/raylib" -B "$tmp/raylib/build" \
                -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF \
                -DPLATFORM=DRM -DGRAPHICS=GRAPHICS_API_OPENGL_ES2
            cmake --build "$tmp/raylib/build" --parallel "$(nproc)"
            sudo cmake --install "$tmp/raylib/build"
            rm -rf "$tmp"
            ok "Raylib 5 built for Pi (GLES2)"
            sum_ok "Raylib 5 (Pi, GLES2)"
            ;;
    esac
}

# ═════════════════════════════════════════════════════════════════════════════
# Coloured summary table
# ═════════════════════════════════════════════════════════════════════════════
print_summary() {
    hr
    printf "${C_BOLD}  PoloOS install — %s (%s)${C_RESET}\n" "$PLATFORM" "$ARCH"
    hr

    local item
    for item in "${SUM_OK[@]+"${SUM_OK[@]}"}"; do
        printf "  ${C_GREEN}✓${C_RESET}  %s\n" "$item"
    done
    for item in "${SUM_SKIP[@]+"${SUM_SKIP[@]}"}"; do
        printf "  ${C_YELLOW}—${C_RESET}  ${C_DIM}%s${C_RESET}\n" "$item"
    done
    for item in "${SUM_FAIL[@]+"${SUM_FAIL[@]}"}"; do
        printf "  ${C_RED}✗${C_RESET}  ${C_RED}%s${C_RESET}\n" "$item"
    done
    hr

    if [[ ${#SUM_FAIL[@]} -gt 0 ]]; then
        printf "${C_RED}${C_BOLD}  %d item(s) failed — see output above.${C_RESET}\n" "${#SUM_FAIL[@]}"
    else
        printf "${C_GREEN}${C_BOLD}  All done.${C_RESET}\n"
    fi
    hr
}

# ═════════════════════════════════════════════════════════════════════════════
# Main
# ═════════════════════════════════════════════════════════════════════════════
main() {
    hr
    log "PoloOS installer   OS=$OS   ARCH=$ARCH   PLATFORM=$PLATFORM"
    hr

    # ── System dependencies ──────────────────────────────────────────────────
    case "$PLATFORM" in
        macos)  install_macos      ;;
        ubuntu) install_ubuntu_x86 ;;
        pi)     install_pi         ;;
    esac

    # ── Python venv ──────────────────────────────────────────────────────────
    if [[ "$SKIP_PYTHON" == false ]]; then
        setup_python_venv
    else
        sum_skip "Python venv (--no-python)"
    fi

    # ── Build ────────────────────────────────────────────────────────────────
    if [[ "$SKIP_BUILD" == false ]]; then
        build_app
    else
        sum_skip "Build (--no-build)"
    fi

    # ── Verify ───────────────────────────────────────────────────────────────
    verify

    # ── Raylib (optional) ────────────────────────────────────────────────────
    if [[ "$WITH_RAYLIB" == true ]]; then
        install_raylib_deps
    fi

    print_summary
}

main "$@"
