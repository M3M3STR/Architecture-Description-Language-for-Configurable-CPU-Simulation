#include "ADL/ADLSemanticAnalyzer.h"

std::vector<std::string> ADLSemanticAnalyzer::analyze(const IntermediateModel& model) {
	// if all good return true, 
	// else return false and the list of errors
	return {""};
}

void  ADLSemanticAnalyzer::checkRegisters() {

	// Check for duplicate register names

	for (const auto& reg : model.registers) {
		if (registerNames.find(reg.name) != registerNames.end()) {
			semantic_errors.push_back("Duplicate register name found: " + reg.name);
		}
		else {
			registerNames.insert(reg.name);
		}

		if (reg.bit_width <= 0) {
			semantic_errors.push_back("Register " + reg.name + " has non-positive bit width: " + std::to_string(reg.bit_width));
		}
	}


}

void ADLSemanticAnalyzer::checkMemory() {
	if (model.memory_size <= 0) {
		semantic_errors.push_back("Memory size must be positive, found: " + std::to_string(model.memory_size));
	}

}

void ADLSemanticAnalyzer::checkInstructions() {
	std::unordered_set<unsigned int> opcodes;
	for (const auto& instr : model.instructions) {
		if (opcodes.find(instr.opcode) != opcodes.end()) {
			semantic_errors.push_back("Duplicate opcode found for instruction: " + instr.name + " with opcode: " + std::to_string(instr.opcode));
		}
		else {
			opcodes.insert(instr.opcode);
		}
		if (instr.format.empty()) {
			semantic_errors.push_back("Instruction " + instr.name + " has no format specified.");
		}
	}
}