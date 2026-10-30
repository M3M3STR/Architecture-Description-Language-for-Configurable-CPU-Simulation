#include <iostream>
#include <string>

#include "parser_ADL.h"
#include "parser_ASM.h"

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
                opcode 1
                format RRR
            }
            instruction sub {
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


    ADLParser::ArchitectureContext* adlTree = parserADL.parseFromString(sourceADL);
	CPU cpu = parserADL.convertParseTreeToCPUDefinition(adlTree);

	ASMParser::ProgramContext* asmTree = parserASM.parseFromString(sourceASM);

    return 0;
}