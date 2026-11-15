# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

file(GLOB SCREEN_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Screens/*.cpp"
)
file(GLOB UI_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_library(SimulatorUI STATIC
        ${UI_SOURCES}
        ${SCREEN_SOURCES}
        ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp

)

target_include_directories(SimulatorUI PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
)

# TODO uncomment out ASM when asm has been updated
target_link_libraries(SimulatorUI PUBLIC
        ADL
        #ASM
        imgui
        ImGuiColorTextEdit
        SDL3::SDL3
        OpenGL::GL
)