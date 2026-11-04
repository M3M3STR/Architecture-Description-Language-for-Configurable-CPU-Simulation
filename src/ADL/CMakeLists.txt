# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.


file(GLOB ADL_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_library(ADL STATIC
        ${ADL_SOURCES}

        ${ADL_GENERATED_SOURCES}
        ${ADL_GENERATED_HEADERS}
)

target_include_directories(ADL PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/include/ADL"
        "${ADL_GENERATED_DIR}"
)

target_link_libraries(ADL PUBLIC
        Common
        antlr4_static
)

target_compile_definitions(ADL PUBLIC
        ANTLR4CPP_STATIC
)