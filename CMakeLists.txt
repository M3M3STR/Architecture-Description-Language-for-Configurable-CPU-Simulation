cmake_minimum_required(VERSION 3.20)

project(ADL
        VERSION 0.1.0
        DESCRIPTION "Architecture Description Language for Configurable CPU Simulation"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ============================================================
# Dependencies
# ============================================================

include(FetchContent)

# ----------------------------
# SDL3
# ----------------------------

FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.4.16
)

FetchContent_MakeAvailable(SDL3)


# ----------------------------
# Dear ImGui
# ----------------------------

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.92.2b
)

FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp

        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui
        PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(imgui
        PUBLIC
        SDL3::SDL3
)

# ----------------------------
# OpenGL
# ----------------------------

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/UI/Application.cpp
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        imgui
        SDL3::SDL3
        OpenGL::GL
)
