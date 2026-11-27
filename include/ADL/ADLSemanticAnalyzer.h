#pragma once

#include <string>
#include <vector>
#include <expected>
#include <unordered_set>

#include "Common/IntermediateModel.h"

class ADLSemanticAnalyzer {

private:
	IntermediateModel& model;
	
	std::vector<std::string> semantic_errors;

	std::unordered_set<std::string> registerNames;
	std::unordered_set<std::string> instructionNames;
	std::unordered_set<std::string> instructionFormatNames;
	std::unordered_set<unsigned int> opcodes;

public:

	ADLSemanticAnalyzer(IntermediateModel& model) : model(model) {}

	

	std::expected<bool, std::vector<std::string>> analyze();
	void checkRegisters();
	void checkMemory();
	void checkInstructions();
	void checkInstructionFormats();
};