cmake_minimum_required(VERSION 3.16)
project(PoloOS VERSION 0.1 LANGUAGES CXX)

# --- 1. FIND QT FIRST ---
# This "loads" the commands like qt_standard_project_setup
find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Qml)

# --- 2. SETUP THE PROJECT ---
# Now CMake knows what this command is.
qt_standard_project_setup(REQUIRES 6.5)

# --- 3. AUTOMATION ---
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# --- 4. BUILD THE APP ---
qt_add_executable(appPoloOS
    main.cpp
)

# --- 5. ADD QML MODULE ---
qt_add_qml_module(appPoloOS
    URI PoloOS
    VERSION 1.0
    QML_FILES Main.qml
)

target_link_libraries(appPoloOS PRIVATE Qt6::Core Qt6::Gui Qt6::Quick Qt6::Qml)
