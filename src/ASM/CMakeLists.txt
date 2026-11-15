# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.

file(GLOB ASM_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_library(ASM STATIC
        ${ASM_SOURCES}

        ${ASM_GENERATED_SOURCES}
        ${ASM_GENERATED_HEADERS}
)

target_include_directories(ASM PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/include/ASM"
        "${ASM_GENERATED_DIR}"
)

target_link_libraries(ASM PUBLIC
        Common
        antlr4_static
)

target_compile_definitions(ASM PUBLIC
        ANTLR4CPP_STATIC
)