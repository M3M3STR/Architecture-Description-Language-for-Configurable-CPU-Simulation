#include <iostream>
#include <string>

#include "antlr4-runtime.h"
#include "ASMLexer.h"
#include "ASMParser.h"

int main()
{
    std::string source = R"(
            add r1, r2, r3
            sub r4, r5, r6
            # this is a comment
            add r7, r1, r4   # inline comment
        )";

    antlr4::ANTLRInputStream input(source);
    ASMLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    ASMParser parser(&tokens);

    auto* tree = parser.program();

    std::cout << tree->toStringTree(&parser) << '\n';

    if (parser.getNumberOfSyntaxErrors() != 0)
    {
        std::cerr << "ASM parsing failed.\n";
        return 1;
    }

    std::cout << "ASM parsing succeeded!\n";
    return 0;
}