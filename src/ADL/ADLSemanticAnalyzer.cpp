#include "ADL/ADLSemanticAnalyzer.h"

std::expected<bool, std::vector<std::string>> ADLSemanticAnalyzer::analyze() {
	checkInstructionFormats();
	checkInstructions();
	checkRegisters();

	if (semantic_errors.empty()) {
		return true;
	}
	else {
		return std::unexpected(semantic_errors);
	}
}

void  ADLSemanticAnalyzer::checkRegisters() {

	// Check for duplicate register names

	for (const auto& reg : model.getRegisters()) {
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
	if (model.getMemorySize() <= 0) {
		semantic_errors.push_back("Memory size must be positive, found: " + std::to_string(model.getMemorySize()));
	}

}

void ADLSemanticAnalyzer::checkInstructions() {
	
	for (const auto& instr : model.getInstructions()) {

		// Check for duplicate opcodes
		if (opcodes.find(instr.opcode) != opcodes.end()) {
			semantic_errors.push_back("Duplicate opcode found for instruction: " + instr.name + " with opcode: " + std::to_string(instr.opcode));
		}
		else {
			opcodes.insert(instr.opcode);
		}

		// Check for duplicate instruction names
		if (instructionNames.find(instr.name) != instructionNames.end()) {
			semantic_errors.push_back("Duplicate instruction name found: " + instr.name);
		}
		else {
			instructionNames.insert(instr.name);
		}

		// Check if the instruction format exists in the model
		if (instr.format.empty()) {
			semantic_errors.push_back("Instruction " + instr.name + " has no format specified.");
		}
		else if (model.getInstructionFormatByName(instr.format).name.empty()) {
			semantic_errors.push_back("Instruction " + instr.name + " references unknown format: " + instr.format);
		}
		

	}
}

void ADLSemanticAnalyzer::checkInstructionFormats() {
	for (const auto& format : model.getInstructionFormats()) {
		// Check for duplicate instruction format names
		if (instructionFormatNames.find(format.name) != instructionFormatNames.end()) {
			semantic_errors.push_back("Duplicate instruction format name found: " + format.name);
		}
		else {
			instructionFormatNames.insert(format.name);
		}
		// Check if the bit fields are valid (e.g., non-overlapping, within bounds)
		std::unordered_set<int> usedBits;
		for (const auto& field : format.fields) {
			if (field.range.start < 0 || field.range.end < 0 || field.range.start < field.range.end) {
				semantic_errors.push_back("Invalid bit range for field " + fieldTypeToString(field.type) + " in format " + format.name);
			}
			for (int bit = field.range.start; bit <= field.range.end; ++bit) {
				if (usedBits.find(bit) != usedBits.end()) {
					semantic_errors.push_back("Overlapping bit range for field " + fieldTypeToString(field.type) + " in format " + format.name);
				}
				else {
					usedBits.insert(bit);
				}
			}
		}
	}
}