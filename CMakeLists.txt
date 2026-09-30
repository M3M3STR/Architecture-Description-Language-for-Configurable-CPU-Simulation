cmake_minimum_required(VERSION 3.20)

project(CPUSimulator
        VERSION 0.1.0
        DESCRIPTION "Architecture Description Language for Configurable CPU Simulation"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(cpu_simulator
        src/main.cpp
)

target_include_directories(cpu_simulator
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)