#include <iostream>
#include <string>

#include "parser_ADL.h"
#include "parser_ASM.h"
#include "assembler.h"
#include "ADL/parser_ADL.h"
#include "ASM/parser_ASM.h"

int main()
{
    
    std::string sourceADL = R"(
        architecture MyCPU {
            registers 16
            hi
            memory 1024
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


    ADLParser::ArchitectureContext* adlTree = parserADL.parseFromString(sourceADL); // parses raw text into antlr tree
	CPU cpu = parserADL.convertParseTreeToCPUDefinition(adlTree); // visitor walks the tree and extracts the clean CPU struct
    cpu.word_size = 16; 

    // parse asm and get the clean instructions
    std::vector<ParsedInstruction> asmInstructions = parserASM.parseFromString(sourceASM);
    std::cout << "\nassembler test:\n";
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
    

    //std::expected<ASMDefinition, std::vector<SyntaxError>> asmResult = parserASM.parseFromString(sourceASM);
    //if (!asmResult)
    //{
    //    std::cerr << "Failed to parse ASM: " << asmResult.error() << '\n';
    //    return 1;
    //}
    //ASMDefinition asmDef = asmResult.value();

    // give asm instructions and cpu struct from adl to the assembler
    std::vector<uint64_t> machine_code = Assembler::assemble(asmInstructions, cpu);
    std::cout << "Machine Code size: " << machine_code.size() << "\n";
    return 0;
}
