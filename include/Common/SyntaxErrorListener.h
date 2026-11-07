#pragma once

#include <vector>

#include "antlr4-runtime.h"
#include "Common/SyntaxError.h"

class SyntaxErrorListener : public antlr4::BaseErrorListener {
private:
	std::vector<SyntaxError>& errorsList;
public:

	SyntaxErrorListener(std::vector<SyntaxError>& errorsList);

	void syntaxError(
		antlr4::Recognizer* recognizer,
		antlr4::Token* offendingSymbol,
		size_t line,
		size_t charPositionInLine,
		const std::string& msg,
		std::exception_ptr e
	) override;

};