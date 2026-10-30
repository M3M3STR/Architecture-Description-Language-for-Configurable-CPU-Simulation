cmake_minimum_required(VERSION 3.20)

project(CPUSimulator
    VERSION 0.1.0
    DESCRIPTION "Architecture Description Language for Configurable CPU Simulation"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
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
        src/UI/ScreenManager.cpp
        src/UI/Screens/StartScreen.cpp
        src/UI/Screens/LoadingScreen.cpp
        src/UI/Screens/SimulatorScreen.cpp
        ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)


# --------------------------------------------------
# Java: required for the ANTLR grammar generator
# --------------------------------------------------

find_package(Java REQUIRED COMPONENTS Runtime)

set(ANTLR_JAR
    "${PROJECT_SOURCE_DIR}/tools/antlr-4.13.2-complete.jar"
)

if(NOT EXISTS "${ANTLR_JAR}")
    message(FATAL_ERROR "ANTLR JAR not found: ${ANTLR_JAR}")
endif()

# --------------------------------------------------
# Fetch and build the ANTLR C++ runtime
# --------------------------------------------------

include(FetchContent)

# Disable ANTLR's own tests so GoogleTest isn't fetched.
set(ANTLR_BUILD_CPP_TESTS OFF CACHE BOOL
   "Disable ANTLR C++ runtime tests" FORCE)

# Build only the static runtime.
#set(ANTLR_BUILD_SHARED OFF CACHE BOOL
   # "Disable ANTLR shared runtime" FORCE)
set(ANTLR_BUILD_STATIC ON CACHE BOOL
    "Build ANTLR static runtime" FORCE)

# Match the MSVC CRT used by the application.
set(WITH_STATIC_CRT OFF CACHE BOOL
    "Use dynamic MSVC CRT" FORCE)

FetchContent_Declare(
    antlr4
    GIT_REPOSITORY https://github.com/antlr/antlr4.git
    GIT_TAG 4.13.2
    GIT_SHALLOW TRUE
    SOURCE_SUBDIR runtime/Cpp
)

FetchContent_MakeAvailable(antlr4)

if(TARGET antlr4_static)
    set_property(TARGET antlr4_static
        PROPERTY CXX_STANDARD 17)
    set_property(TARGET antlr4_static
        PROPERTY CXX_STANDARD_REQUIRED ON)
endif()

# --------------------------------------------------
# Generate C++ files from the ADL grammar
# --------------------------------------------------

set(ADL_GRAMMAR
    "${PROJECT_SOURCE_DIR}/grammar/ADL.g4"
)

set(ADL_GENERATED_DIR
    "${PROJECT_BINARY_DIR}/generated/ADL"
)

set(ADL_GENERATED_SOURCES
    "${ADL_GENERATED_DIR}/ADLLexer.cpp"
    "${ADL_GENERATED_DIR}/ADLParser.cpp"
    "${ADL_GENERATED_DIR}/ADLBaseVisitor.cpp"
    "${ADL_GENERATED_DIR}/ADLVisitor.cpp"
)

set(ADL_GENERATED_HEADERS
    "${ADL_GENERATED_DIR}/ADLLexer.h"
    "${ADL_GENERATED_DIR}/ADLParser.h"
    "${ADL_GENERATED_DIR}/ADLBaseVisitor.h"
    "${ADL_GENERATED_DIR}/ADLVisitor.h"
)

add_custom_command(
    OUTPUT
        ${ADL_GENERATED_SOURCES}
        ${ADL_GENERATED_HEADERS}

    COMMAND
        "${CMAKE_COMMAND}" -E make_directory
        "${ADL_GENERATED_DIR}"

    COMMAND
        "${Java_JAVA_EXECUTABLE}" -jar "${ANTLR_JAR}"
        -Dlanguage=Cpp
        -no-listener
        -visitor
        -Xexact-output-dir
        -o "${ADL_GENERATED_DIR}"
        "${ADL_GRAMMAR}"

    DEPENDS
        "${ADL_GRAMMAR}"
        "${ANTLR_JAR}"

    COMMENT "Generating C++ parser from ADL.g4"
    VERBATIM
)

# --------------------------------------------------
# Generate C++ files from the ASM grammar
# --------------------------------------------------

set(ASM_GRAMMAR
    "${PROJECT_SOURCE_DIR}/grammar/ASM.g4"
)

set(ASM_GENERATED_DIR
    "${PROJECT_BINARY_DIR}/generated/ASM"
)

set(ASM_GENERATED_SOURCES
    "${ASM_GENERATED_DIR}/ASMLexer.cpp"
    "${ASM_GENERATED_DIR}/ASMParser.cpp"
    "${ASM_GENERATED_DIR}/ASMBaseVisitor.cpp"
    "${ASM_GENERATED_DIR}/ASMVisitor.cpp"
)

set(ASM_GENERATED_HEADERS
    "${ASM_GENERATED_DIR}/ASMLexer.h"
    "${ASM_GENERATED_DIR}/ASMParser.h"
    "${ASM_GENERATED_DIR}/ASMBaseVisitor.h"
    "${ASM_GENERATED_DIR}/ASMVisitor.h"
)

add_custom_command(
    OUTPUT
        ${ASM_GENERATED_SOURCES}
        ${ASM_GENERATED_HEADERS}

    COMMAND
        "${CMAKE_COMMAND}" -E make_directory
        "${ASM_GENERATED_DIR}"

    COMMAND
        "${Java_JAVA_EXECUTABLE}" -jar "${ANTLR_JAR}"
        -Dlanguage=Cpp
        -no-listener
        -visitor
        -Xexact-output-dir
        -o "${ASM_GENERATED_DIR}"
        "${ASM_GRAMMAR}"

    DEPENDS
        "${ASM_GRAMMAR}"
        "${ANTLR_JAR}"

    COMMENT "Generating C++ parser from ASM.g4"
    VERBATIM
)

# --------------------------------------------------
# Application
# --------------------------------------------------

add_executable(parser_assembler_tester
    tests/parser_assembler_testbench.cpp
    src/ADL/parser_ADL.cpp
    src/ADL/CPUDefinitionVisitor.cpp
    src/ASM/parser_ASM.cpp
    ${ADL_GENERATED_SOURCES}
    ${ADL_GENERATED_HEADERS}
    ${ASM_GENERATED_SOURCES}
    ${ASM_GENERATED_HEADERS}
)

target_include_directories(parser_assembler_tester PRIVATE
    "${PROJECT_SOURCE_DIR}/include/ADL"
    "${PROJECT_SOURCE_DIR}/include/ASM"
    "${ADL_GENERATED_DIR}"
    "${ASM_GENERATED_DIR}"
)

target_link_libraries(parser_assembler_tester PRIVATE
    antlr4_static
)

target_compile_definitions(parser_assembler_tester PRIVATE
    ANTLR4CPP_STATIC
)
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        imgui
        SDL3::SDL3
        OpenGL::GL
)
