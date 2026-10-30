#include "parser_ASM.h"
#include "ASMLexer.h"   
#include "ASMParser.h"  

std::vector<ParsedInstruction> parser_ASM::parseFromString(std::string sourceString) {
    antlr4::ANTLRInputStream input(sourceString);
    ASMLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    ASMParser parser(&tokens);
    
    auto* tree = parser.program(); // build the parse tree

    if (parser.getNumberOfSyntaxErrors() != 0) {
        std::cerr << "ASM parsing failed.\n";
        return {};
    }

    AssemblerVisitor visitor;
    visitor.visit(tree);  // walk the tree and extract the data

    std::cout << "ASM parsing succeeded!\n";
    return visitor.instructions;  // return the clean list
}

std::vector<ParsedInstruction> parser_ASM::parseFromFilePath(std::string filePath) {
    std::ifstream stream(filePath);
    antlr4::ANTLRInputStream input(stream);
    ASMLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    ASMParser parser(&tokens);
    
    auto* tree = parser.program();

    if (parser.getNumberOfSyntaxErrors() != 0) {
        std::cerr << "ASM parsing failed.\n";
        return {};
    }

    AssemblerVisitor visitor;
    visitor.visit(tree); 

    std::cout << "ASM parsing succeeded!\n";
    return visitor.instructions;
}
