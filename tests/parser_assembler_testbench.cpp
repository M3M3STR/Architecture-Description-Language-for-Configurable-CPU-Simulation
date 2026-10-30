#include <iostream>
#include <string>

#include "parser_ADL.h"
#include "parser_ASM.h"
#include "assembler.h"

int main()
{
    /*
    CPUDefinitionVisitor visitor;
    antlr4::ANTLRInputStream input(source);
    ADLLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    ADLParser parser(&tokens);

    auto* tree = parser.architecture();

    std::cout << tree->toStringTree(&parser) << '\n';

    if (parser.getNumberOfSyntaxErrors() != 0)
    {
        std::cerr << "ADL parsing failed.\n";
        return 1;
    }

    std::cout << "ADL parsing succeeded!\n";

	std::any result = visitor.visitArchitecture(tree);
	CPU cpu = std::any_cast<CPU>(result);
    printCPU(cpu);
    */
    std::string sourceADL = R"(
        architecture MyCPU {
            registers 16
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

    // give asm instructions and cpu struct from adl to the assembler
    std::vector<uint64_t> machine_code = Assembler::assemble(asmInstructions, cpu);
    std::cout << "Machine Code size: " << machine_code.size() << "\n";
    return 0;
}
