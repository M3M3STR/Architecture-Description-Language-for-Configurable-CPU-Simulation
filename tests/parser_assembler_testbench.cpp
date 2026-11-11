#include <iostream>
#include <string>

#include "ASM/assembler.h"
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
                opcode [15:14]
                reg_dest [13:11]
                reg_src [10:8]
                reg_src [7:5]
            }
            format RRI {
                opcode [15:14]
                reg_dest [13:11]
                reg_src [10:8]
                imm_unsigned [7:0]
            }
            instruction add {
                opcode 0
                format RRR
            }
            instruction sub {
                opcode 1
                format RRI
            }
        }
    )";

   std::string sourceASM = R"(
        add r1, r2, r3
        sub r4, r5, 6
        # this is a comment
        add r7, r1, r4   # inline comment
    )";

    parser_ADL parserADL;
    parser_ASM parserASM;

    // parse the ADL
    std::expected<IntermediateModel, std::vector<SyntaxError>> adlResult = parserADL.parseFromString(sourceADL);
    if (!adlResult)
    {
        std::cerr << "Failed to parse ADL: " << std::endl;
        for (const auto& error : adlResult.error())
        {
            std::cerr << "Line " << error.line 
                      << ", Column " << error.column 
                      << ": " << error.msg << '\n';
        }
        return 1;
    }

    IntermediateModel model = adlResult.value(); 
    model.printIntermediateModel();

    // parse the ASM 
    std::expected<std::vector<ParsedInstruction>, std::vector<SyntaxError>> asmResult = parserASM.parseFromString(sourceASM);
    if (!asmResult)
    {
        std::cerr << "Failed to parse ASM: " << std::endl;

        for (const auto& error : asmResult.error())
        {
            std::cerr << "Line " << error.line 
                    << ", Column " << error.column 
                    << ": " << error.msg << '\n';
        }

        return 1;
    }
    std::vector<ParsedInstruction> asmInstructions = asmResult.value();

    // run the assembler
    std::cout << "\nassembler test:\n";
    std::vector<uint64_t> machine_code = Assembler::assemble(asmInstructions, model);
    std::cout << "Machine Code size: " << machine_code.size() << "\n";

    return 0;
}