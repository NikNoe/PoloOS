cmake_minimum_required(VERSION 3.16)
project(PoloOS VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# ── Aide CMake à trouver Qt sur Pi 5 (ignoré si le chemin n'existe pas)
if(EXISTS "/usr/lib/aarch64-linux-gnu/cmake")
    list(APPEND CMAKE_PREFIX_PATH "/usr/lib/aarch64-linux-gnu/cmake")
endif()

# ── Git hash & build date ────────────────────────────────────────────────────
execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)
string(TIMESTAMP BUILD_DATE "%Y-%m-%d")
add_definitions(-DGIT_COMMIT_HASH="${GIT_HASH}" -DBUILD_DATE="${BUILD_DATE}")

# ── qt_standard_project_setup() n'existe qu'en Qt >= 6.5 — équivalent manuel :
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(QT_QML_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/qml")
set(QML_IMPORT_PATH "${CMAKE_BINARY_DIR}/qml" CACHE STRING "QML import path" FORCE)

# ── Modules Qt obligatoires ───────────────────────────────────────────────────
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Quick
    Qml
    Quick3D
    Quick3DHelpers
    SerialBus
    SerialPort
    QuickControls2
    ShaderTools
)


# ── Policy QTP0001 : accepte :/qt/qml/ comme préfixe par défaut (Qt 6.5+)
# Sans ça, Qt 6.10 ignore RESOURCE_PREFIX et affiche un warning
if(Qt6_VERSION VERSION_GREATER_EQUAL "6.5.0")
    qt_policy(SET QTP0001 NEW)
endif()

# ── Modules optionnels : absents sur Pi (pas dans les dépôts Ubuntu 24.04 arm64)
find_package(Qt6 OPTIONAL_COMPONENTS Location Positioning)

if(Qt6Location_FOUND)
    message(STATUS "Qt6Location trouvé — MapPage activée")
else()
    message(WARNING "Qt6Location absent — MapPage désactivée (Pi / Ubuntu 24.04 arm64)")
endif()


# ── Exécutable unique ─────────────────────────────────────────────────────────
qt_add_executable(appPoloOS
    src/main.cpp
    src/can/canhandler.h
    src/can/CanReader.h
    src/can/CanReader.cpp
)

# ── src/can/ headers must be on the include path for main.cpp and moc
target_include_directories(appPoloOS PRIVATE src/can)

# ── Module QML ────────────────────────────────────────────────────────────────
qt_add_qml_module(appPoloOS
    URI PoloOS
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/vehicle/Polo.qml
        qml/vehicle/CockpitWindow.qml
        qml/components/DashboardIcon.qml
        qml/components/VitalsItem.qml
        qml/pages/EnginePage.qml
        qml/components/EngineLive.qml
        qml/pages/EnergyPage.qml
        qml/pages/AboutPage.qml
        qml/pages/BodyPage.qml
        qml/pages/DiagnosticsPage.qml
        qml/pages/SettingsPage.qml
        qml/pages/ChassisPage.qml
        qml/pages/MapPage.qml
        qml/components/TempCard.qml
        qml/components/BusStatusCard.qml
        qml/components/EcuTag.qml
        qml/components/EngineerRow.qml
    RESOURCES
        assets/icons/icons.qrc
        assets/meshes/chassis_mesh.mesh
        assets/meshes/imvlm_lighting_mesh.mesh
        assets/meshes/interior_And_engine_mesh.mesh
        assets/meshes/glass_interior_001_mesh.mesh
        assets/meshes/taillight_red_glass_001_mesh.mesh
        assets/meshes/bonnet_ok_001_mesh.mesh
        assets/meshes/boot_ok_mesh.mesh
        assets/meshes/boot_ok_003_mesh.mesh
        assets/meshes/bumper_front_ok_mesh.mesh
        assets/meshes/bump_rear_ok_mesh.mesh
        assets/meshes/door_lr_ok_mesh.mesh
        assets/meshes/door_lf_ok_mesh.mesh
        assets/meshes/door_lf_ok_003_mesh.mesh
        assets/meshes/wing_lf_ok_001_mesh.mesh
        assets/meshes/wing_rf_ok_001_mesh.mesh
        assets/meshes/door_rf_ok_mesh.mesh
        assets/meshes/door_rf_ok_003_mesh.mesh
        assets/meshes/door_rr_ok_mesh.mesh
        assets/meshes/windscreen_ok_001_mesh.mesh
        assets/meshes/steering_ok_mesh.mesh
        assets/meshes/speedook_mesh.mesh
        assets/meshes/tahook_mesh.mesh
        assets/meshes/vent_001_mesh.mesh
        assets/meshes/chassis_003_mesh.mesh
        assets/meshes/wheel_mesh.mesh
        assets/meshes/wheel_001_mesh.mesh
        assets/meshes/wheel_002_mesh.mesh
        assets/meshes/wheel_003_mesh.mesh
        SOURCES src/can/CanReader.cpp
        QML_FILES
)

# ── NO_CACHEGEN : uniquement sur Qt < 6.5 (Pi avec Qt 6.4 apt)
# Sur Qt 6.5+ le cachegen fonctionne correctement et est nécessaire
if(Qt6_VERSION VERSION_LESS "6.5.0")
    message(STATUS "Qt ${Qt6_VERSION} détecté — désactivation du QML cachegen (Pi mode)")
    set_target_properties(appPoloOS PROPERTIES
        QT_QML_MODULE_NO_CACHEGEN TRUE
    )
endif()

# ── Liens — modules obligatoires ─────────────────────────────────────────────
target_link_libraries(appPoloOS PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::Qml
    Qt6::Quick3D
    Qt6::Quick3DHelpers
    Qt6::SerialBus
    Qt6::SerialPort
    Qt6::QuickControls2
    Qt6::ShaderTools
)

# ── Liens — modules optionnels ────────────────────────────────────────────────
if(Qt6Location_FOUND)
    target_link_libraries(appPoloOS PRIVATE Qt6::Location Qt6::Positioning)
    target_compile_definitions(appPoloOS PRIVATE HAS_QT_LOCATION)
endif()
