#include "Common/SyntaxErrorListener.h"


SyntaxErrorListener::SyntaxErrorListener(std::vector<SyntaxError>& errorsList)
	: errorsList(errorsList)
{
}

// Catches syntax errors during parsing and adds them to the provided errorsList
void SyntaxErrorListener::syntaxError(
	antlr4::Recognizer* recognizer,
	antlr4::Token* offendingSymbol,
	size_t line,
	size_t charPositionInLine,
	const std::string& msg,
	std::exception_ptr e
)
{
	errorsList.push_back(SyntaxError(line, charPositionInLine, msg));
}