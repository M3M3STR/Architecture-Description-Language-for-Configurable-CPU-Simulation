# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.


add_executable(parserassemblertester
        ParserAssemblerTestbench.cpp
)

## TODO add 'ASM' back after it has been implemented
target_link_libraries(parserassemblertester PRIVATE
        ADL
)