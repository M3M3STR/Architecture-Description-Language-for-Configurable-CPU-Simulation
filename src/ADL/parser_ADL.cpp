#include "ADL/parser_ADL.h"

std::expected<IntermediateModel, std::vector<SyntaxError>> parser_ADL::parseFromString(std::string sourceString) {

	// Create a vector to hold syntax errors and a listener to populate it
	std::vector<SyntaxError> errorsList;
	SyntaxErrorListener errorListener(errorsList);

	// Set up ANTLR input stream, lexer, token stream, and parser
	antlr4::ANTLRInputStream input(sourceString);
	ADLLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	ADLParser parser(&tokens);

	// Attach the error listener to the parser
	parser.removeErrorListeners(); // Remove default error listeners
	parser.addErrorListener(&errorListener);

	// Parse the input and build the parse tree
	auto* tree = parser.architecture();

	std::cout << tree->toStringTree(&parser) << '\n';

	if (parser.getNumberOfSyntaxErrors() != 0)
	{
		std::cerr << "ADL parsing failed.\n";
		return std::unexpected(errorsList);
	}

	std::cout << "ADL parsing succeeded!\n";
	
	return convertParseTreeToIntermediateModel(tree);
}

std::expected<IntermediateModel, std::vector<SyntaxError>> parser_ADL::parseFromFilePath(std::string filePath) {

	// Create a vector to hold syntax errors and a listener to populate it
	std::vector<SyntaxError> errorsList;
	SyntaxErrorListener errorListener(errorsList);

	// Set up ANTLR input stream, lexer, token stream, and parser
	std::ifstream stream;
	stream.open(filePath);

	antlr4::ANTLRInputStream input(stream);
	ADLLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	ADLParser parser(&tokens);

	// Attach the error listener to the parser
	parser.removeErrorListeners(); // Remove default error listeners
	parser.addErrorListener(&errorListener);

	auto* tree = parser.architecture();

	std::cout << tree->toStringTree(&parser) << '\n';

	if (parser.getNumberOfSyntaxErrors() != 0)
	{
		std::cerr << "ADL parsing failed.\n";
		return std::unexpected(errorsList);
	}

	std::cout << "ADL parsing succeeded!\n";

	return convertParseTreeToIntermediateModel(tree);
}

IntermediateModel parser_ADL::convertParseTreeToIntermediateModel(ADLParser::ArchitectureContext* tree) {

	// Use the IntermediateModelBuilder to visit the parse tree and build the IntermediateModel
	IntermediateModelBuilder builder;
	std::any result = builder.visitArchitecture(tree);
	IntermediateModel model = std::any_cast<IntermediateModel>(result);
	return model;
}
