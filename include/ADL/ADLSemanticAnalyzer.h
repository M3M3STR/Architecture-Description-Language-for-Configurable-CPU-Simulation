#pragma once

#include <string>
#include <vector>
#include <expected>
#include <unordered_set>

#include "Common/IntermediateModel.h"

class ADLSemanticAnalyzer {

private:
	const IntermediateModel& model;
	std::unordered_set<std::string> registerNames;

public:

	std::vector<std::string> semantic_errors;
	std::vector<std::string> analyze(const IntermediateModel& model);
	void checkRegisters();
	void checkMemory();

	void checkInstructions();
};