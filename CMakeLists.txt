cmake_minimum_required(VERSION 3.16)
project(PoloRaylib VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Raylib : cherche d'abord en système (Option A), sinon FetchContent ─────────
find_package(raylib 5.0 QUIET)

if (NOT raylib_FOUND)
    message(STATUS "raylib non trouvé en système — FetchContent activé")
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        5.5
        GIT_SHALLOW    TRUE
    )
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(raylib)
endif()

# ── Sources ────────────────────────────────────────────────────────────────────
set(SOURCES
    src/main.cpp
    src/car/PoloCar.cpp
    src/car/CarRenderer.cpp
    src/scene/RoadMap.cpp
    src/scene/Camera.cpp
    src/ui/HUD.cpp
)

add_executable(PoloRaylib ${SOURCES})

target_include_directories(PoloRaylib PRIVATE src)

target_link_libraries(PoloRaylib PRIVATE raylib)

add_custom_command(TARGET PoloRaylib POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:PoloRaylib>/assets
)

# ── Pi 5 : math + pthreads ────────────────────────────────────────────────────
if(UNIX AND NOT APPLE)
    target_link_libraries(PoloRaylib PRIVATE m pthread)
endif()

# ── macOS : frameworks nécessaires ───────────────────────────────────────────
if(APPLE)
    target_link_libraries(PoloRaylib PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
endif()