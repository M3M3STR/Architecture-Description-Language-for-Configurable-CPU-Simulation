# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.


file(GLOB COMMON_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_library(Common STATIC
        ${COMMON_SOURCES}
)

target_include_directories(Common PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(Common PUBLIC
        antlr4_static
)

target_compile_definitions(Common PUBLIC
        ANTLR4CPP_STATIC
)