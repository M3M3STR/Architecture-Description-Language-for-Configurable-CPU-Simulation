#include "parser_ASM.h"


ASMParser::ProgramContext* parser_ASM::parseFromString(std::string sourceString) {
	antlr4::ANTLRInputStream input(sourceString);
	ASMLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	ASMParser parser(&tokens);
	auto* tree = parser.program();

	std::cout << tree->toStringTree(&parser) << '\n';

	if (parser.getNumberOfSyntaxErrors() != 0)
	{
		std::cerr << "ASM parsing failed.\n";
		return nullptr;
	}

	std::cout << "ASM parsing succeeded!\n";

	return tree;
}

ASMParser::ProgramContext* parser_ASM::parseFromFilePath(std::string filePath) {
	std::ifstream stream;
	stream.open(filePath);
	antlr4::ANTLRInputStream input(stream);
	ASMLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	ASMParser parser(&tokens);
	auto* tree = parser.program();

	std::cout << tree->toStringTree(&parser) << '\n';

	if (parser.getNumberOfSyntaxErrors() != 0)
	{
		std::cerr << "ASM parsing failed.\n";
		return nullptr;
	}

	std::cout << "ASM parsing succeeded!\n";

	return tree;
}
