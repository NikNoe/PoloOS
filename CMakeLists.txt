cmake_minimum_required(VERSION 3.16)
project(PoloOS VERSION 0.1 LANGUAGES CXX)

# --- 1. FIND QT + 3D MODULES ---
# Added Quick3D and Quick3DHelpers for the Tesla-style view
find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Qml Quick3D Quick3DHelpers SerialBus SerialPort Location Positioning)

# --- 2. SETUP THE PROJECT ---
qt_standard_project_setup(REQUIRES 6.5)

# --- 3. AUTOMATION ---
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# --- 4. CREATE THE EXECUTABLE ---
qt_add_executable(appPoloOS
    main.cpp
)

# --- 5. THE QML MODULE (ONE CALL ONLY) ---
# We list ALL .qml files here in a single list
qt_add_qml_module(appPoloOS
    URI PoloOS
    VERSION 1.0
    QML_FILES
        Main.qml
        Polo.qml
        RESOURCES
                # This tells CMake to include every .mesh file in the meshes folder
                meshes/chassis_mesh.mesh
                meshes/imvlm_lighting_mesh.mesh
                meshes/interior_And_engine_mesh.mesh
                meshes/glass_interior_001_mesh.mesh
                meshes/taillight_red_glass_001_mesh.mesh
                meshes/bonnet_ok_001_mesh.mesh
                meshes/boot_ok_mesh.mesh
                meshes/boot_ok_003_mesh.mesh
                meshes/bumper_front_ok_mesh.mesh
                meshes/bump_rear_ok_mesh.mesh
                meshes/door_lr_ok_mesh.mesh
                meshes/door_lf_ok_mesh.mesh
                meshes/door_lf_ok_003_mesh.mesh
                meshes/wing_lf_ok_001_mesh.mesh
                meshes/wing_rf_ok_001_mesh.mesh
                meshes/door_rf_ok_mesh.mesh
                meshes/door_rf_ok_003_mesh.mesh
                meshes/door_rr_ok_mesh.mesh
                meshes/windscreen_ok_001_mesh.mesh
                meshes/steering_ok_mesh.mesh
                meshes/speedook_mesh.mesh
                meshes/tahook_mesh.mesh
                meshes/vent_001_mesh.mesh
                meshes/chassis_003_mesh.mesh
                meshes/wheel_mesh.mesh
                meshes/wheel_001_mesh.mesh
                meshes/wheel_002_mesh.mesh
                meshes/wheel_003_mesh.mesh
                SOURCES canhandler.h
                QML_FILES CockpitWindow.qml
                QML_FILES DashboardIcon.qml
 QML_FILES VitalsItem.qml
 QML_FILES
 QML_FILES EnginePage.qml
 QML_FILES EngineLive.qml
 QML_FILES EnergyPage.qml
 QML_FILES AboutPage.qml
 QML_FILES BodyPage.qml
 QML_FILES DiagnosticsPage.qml
 QML_FILES SettingsPage.qml
 QML_FILES ChassisPage.qml
 QML_FILES MapPage.qml
 QML_FILES TempCard.qml
 QML_FILES BusStatusCard.qml
 QML_FILES EcuTag.qml
 QML_FILES EngineerRow.qml
 RESOURCES icons.qrc
                # Add all other .mesh files here, or use a wildcard if using CMake 3.20+
)

# --- 6. LINK EVERYTHING ---
# Make sure to link the 3D libraries here
target_link_libraries(appPoloOS PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::Qml
    Qt6::Quick3D
    Qt6::Quick3DHelpers
    Qt6::Location
    Qt6::Positioning
)

# Add SerialBus to the link list
target_link_libraries(appPoloOS PRIVATE
    Qt6::Core Qt6::Gui Qt6::Quick Qt6::Qml Qt6::Quick3D Qt6::Quick3DHelpers Qt6::SerialBus Qt6::SerialPort
)

# Get the Git Hash
execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the Build Date
string(TIMESTAMP BUILD_DATE "%Y-%m-%d")

# Pass these to your C++ code
add_definitions(-DGIT_COMMIT_HASH="${GIT_HASH}")
add_definitions(-DBUILD_DATE="${BUILD_DATE}")
