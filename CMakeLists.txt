cmake_minimum_required(VERSION 3.20)

project(CPUSimulator
    VERSION 0.1.0
    DESCRIPTION "Architecture Description Language for Configurable CPU Simulation"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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
    "${PROJECT_BINARY_DIR}/generated"
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

set(ASM_GENERATED_SOURCES
    "${ADL_GENERATED_DIR}/ASMLexer.cpp"
    "${ADL_GENERATED_DIR}/ASMParser.cpp"
    "${ADL_GENERATED_DIR}/ASMBaseVisitor.cpp"
    "${ADL_GENERATED_DIR}/ASMVisitor.cpp"
)

set(ASM_GENERATED_HEADERS
    "${ADL_GENERATED_DIR}/ASMLexer.h"
    "${ADL_GENERATED_DIR}/ASMParser.h"
    "${ADL_GENERATED_DIR}/ASMBaseVisitor.h"
    "${ADL_GENERATED_DIR}/ASMVisitor.h"
)

add_custom_command(
    OUTPUT
        ${ASM_GENERATED_SOURCES}
        ${ASM_GENERATED_HEADERS}

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

add_executable(cpu_simulator
    src/main.cpp
    ${ADL_GENERATED_SOURCES}
    ${ADL_GENERATED_HEADERS}
)

target_include_directories(cpu_simulator PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
    "${ADL_GENERATED_DIR}"
)

target_link_libraries(cpu_simulator PRIVATE
    antlr4_static
)

target_compile_definitions(cpu_simulator PRIVATE
    ANTLR4CPP_STATIC
)

add_executable(asm_parser
    src/asm_main.cpp
    ${ASM_GENERATED_SOURCES}
    ${ASM_GENERATED_HEADERS}
)

target_include_directories(asm_parser PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
    "${ADL_GENERATED_DIR}"
)

target_link_libraries(asm_parser PRIVATE
    antlr4_static
)

target_compile_definitions(asm_parser PRIVATE
    ANTLR4CPP_STATIC
)
