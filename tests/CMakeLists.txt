# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.


add_executable(parser_assembler_tester
        parser_assembler_testbench.cpp
)

target_link_libraries(parser_assembler_tester PRIVATE
        ADL
        ASM
)