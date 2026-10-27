#include "parser_ADL.h"

ADLParser::ArchitectureContext* parser_ADL::parseFromString(std::string sourceString) {
	// Reset old states if they exist
	parser.reset();
	tokens.reset();
	lexer.reset();
	input.reset();

	input = std::make_unique<antlr4::ANTLRInputStream>(sourceString);
	lexer = std::make_unique<ADLLexer>(input.get());
	tokens = std::make_unique<antlr4::CommonTokenStream>(lexer.get());
	parser = std::make_unique<ADLParser>(tokens.get());
	auto* tree = parser->architecture();

	std::cout << tree->toStringTree(parser.get()) << '\n';

	if (parser->getNumberOfSyntaxErrors() != 0)
	{
		std::cerr << "ADL parsing failed.\n";
		return nullptr;
	}

	std::cout << "ADL parsing succeeded!\n";

	return tree;
}

ADLParser::ArchitectureContext* parser_ADL::parseFromFilePath(std::string filePath) {

	std::ifstream stream;
	stream.open(filePath);
	input = std::make_unique<antlr4::ANTLRInputStream>(stream);
	lexer = std::make_unique<ADLLexer>(input.get());
	tokens = std::make_unique<antlr4::CommonTokenStream>(lexer.get());
	parser = std::make_unique<ADLParser>(tokens.get());
	auto* tree = parser->architecture();

	std::cout << tree->toStringTree(parser.get()) << '\n';

	if (parser->getNumberOfSyntaxErrors() != 0)
	{
		std::cerr << "ADL parsing failed.\n";
		return nullptr;
	}

	std::cout << "ADL parsing succeeded!\n";

	return tree;
}

CPU parser_ADL::convertParseTreeToCPUDefinition(ADLParser::ArchitectureContext* tree) {
	CPUDefinitionVisitor visitor;
	std::any result = visitor.visitArchitecture(tree);
	CPU cpu = std::any_cast<CPU>(result);
	return cpu;
}
