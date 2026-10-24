#include <iostream>
#include <string>

#include "antlr4-runtime.h"
#include "ADLLexer.h"
#include "ADLParser.h"
#include "CPUDefinitionVisitor.cpp"

int main()
{
    std::string source = R"(
        architecture SimpleCPU {
            registers 8
            memory 1024
            instruction ADD {
                opcode 1
                format R
            }
            instruction SUB {
                opcode 2
                format A
            }
            instruction MULT {
                opcode 3
                format B
            }
        }
    )";
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

    return 0;
}