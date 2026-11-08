#include <iostream>
#include <string>

#include "ADL/parser_ADL.h"
#include "ASM/parser_ASM.h"

int main()
{
    
    std::string sourceADL = R"(
        architecture MyCPU {
            registers {
                16 { r0 r1 r2 r3 r4 r5 r6 r7 }
            }
            memory 1024
            format RRR {
                opcode [0:1]
                reg_dest [2:4]
                reg_src [5:7]
                reg_src [8:10]
            }
            instruction add {
                opcode 1
                format RRR
            }
            instruction sub {
                opcode 2
                format RRR
            }
            instruction abc {
                opcode 1
                format RRR
            }
            instruction xyz {
                opcode 2
                format RRR
            }
        }
    )";

    std::string sourceASM = R"(
        add r1, r2, r3
        sub r4, r5, r6
        # this is a comment
        add r7, r1, r4   # inline comment
    )";


    parser_ADL parserADL;
    parser_ASM parserASM;


    std::expected<IntermediateModel, std::vector<SyntaxError>> adlResult = parserADL.parseFromString(sourceADL);
    if (!adlResult)
    {
        std::cerr << "Failed to parse ADL: " << std::endl;

        for (const auto& error : adlResult.error())
        {
            std::cerr
                << "Line " << error.line
                << ", Column " << error.column
                << ": " << error.msg << '\n';
        }

        return 1;
    }
    IntermediateModel cpu = adlResult.value();
    
    cpu.printIntermediateModel();

    //std::expected<ASMDefinition, std::vector<SyntaxError>> asmResult = parserASM.parseFromString(sourceASM);
    //if (!asmResult)
    //{
    //    std::cerr << "Failed to parse ASM: " << asmResult.error() << '\n';
    //    return 1;
    //}
    //ASMDefinition asmDef = asmResult.value();

    return 0;
}