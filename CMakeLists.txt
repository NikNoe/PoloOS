cmake_minimum_required(VERSION 3.16)

project(PoloOS VERSION 0.1 LANGUAGES CXX)

# 1. Essential: Qt 6 requires C++17 or higher
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

# 2. Setup standard paths and layout (Required for 6.8)
qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appPoloOS
    main.cpp
)

# 3. Add QML Module - Note: URI should usually be lowercase or CamelCase
# matching your folder structure (e.g., "PoloOS.Main")
qt_add_qml_module(appPoloOS
    URI PoloOS
    VERSION 1.0
    QML_FILES
        Main.qml
)

set_target_properties(appPoloOS PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appPoloOS
    PRIVATE Qt6::Quick
)

# 4. Deployment/Installation
include(GNUInstallDirs)
install(TARGETS appPoloOS
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
