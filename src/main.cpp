#include <iostream>
#include <string>

#include "antlr4-runtime.h"
#include "ADLLexer.h"
#include "ADLParser.h"

int main()
{
    std::string source = R"(
        architecture SimpleCPU {
            registers 8
            instruction ADD {
                opcode 1
                format R
            }
        }
    )";

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
    return 0;
}