#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <memory>

#include "antlr4-runtime.h"
#include "ADLLexer.h"
#include "ADLParser.h"
#include "CPUDefinitionVisitor.h"

class parser_ADL {
private:
	std::unique_ptr<antlr4::ANTLRInputStream> input;
	std::unique_ptr<ADLLexer> lexer;
	std::unique_ptr<antlr4::CommonTokenStream> tokens;
	std::unique_ptr<ADLParser> parser;

public:
	ADLParser::ArchitectureContext* parseFromString(std::string sourceString);
	ADLParser::ArchitectureContext* parseFromFilePath(std::string filePath);
	CPU convertParseTreeToCPUDefinition(ADLParser::ArchitectureContext* tree);
};



