#include "ASM/parser_ASM.h"
#include "ASMLexer.h"
#include "ASMParser.h"
#include "Common/SyntaxErrorListener.h"

std::expected<std::vector<ParsedInstruction>, std::vector<SyntaxError>> 
parser_ASM::parseFromString(std::string sourceString) {
    std::vector<SyntaxError> errorsList;
    SyntaxErrorListener errorListener(errorsList);

    antlr4::ANTLRInputStream input(sourceString);
    ASMLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    ASMParser parser(&tokens);

    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);

    auto* tree = parser.program();

    if (parser.getNumberOfSyntaxErrors() != 0) {
        std::cerr << "ASM parsing failed.\n";
        return std::unexpected(errorsList); // return the errors
    }

    AssemblerVisitor visitor;
    visitor.visit(tree);

    std::cout << "ASM parsing succeeded!\n";
    return visitor.instructions; // return the data
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
