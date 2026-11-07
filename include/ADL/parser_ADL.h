#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <expected>

#include "antlr4-runtime.h"
#include "ADLLexer.h"
#include "ADLParser.h"
#include "Common/IntermediateModel.h"
#include "Common/SyntaxErrorListener.h"
#include "IntermediateModelBuilder.h"

class parser_ADL {
private:
	IntermediateModel convertParseTreeToIntermediateModel(ADLParser::ArchitectureContext* tree);

public:
	std::expected<IntermediateModel, std::vector<SyntaxError>> parseFromString(std::string sourceString);
	std::expected<IntermediateModel, std::vector<SyntaxError>> parseFromFilePath(std::string filePath);


	
};


