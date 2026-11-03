#include "Common/IntermediateModel.h"

// Setters
void IntermediateModel::setName(const std::string& name) {
    this->name = name;
}

void IntermediateModel::setRegisterCount(int count) {
    this->register_count = count;
}

void IntermediateModel::setMemorySize(int size) {
    this->memory_size = size;
}

// Getters
const std::string& IntermediateModel::getName() const {
    return this->name;
}
int IntermediateModel::getRegisterCount() const {
    return this->register_count;
}
int IntermediateModel::getMemorySize() const {
    return this->memory_size;
}

// Instructions
void IntermediateModel::addInstruction(const Instruction& instruction) {
    this->instructions.push_back(instruction);
}
const std::vector<Instruction>& IntermediateModel::getInstructions() const {
    return this->instructions;
}

// Print the contents of the IntermediateModel for debugging purposes
void IntermediateModel::printIntermediateModel(const IntermediateModel& cpu) {
	std::cout << "CPU Name: " << cpu.getName() << '\n';
	std::cout << "Register Count: " << cpu.getRegisterCount() << '\n';
	std::cout << "Memory Size: " << cpu.getMemorySize() << '\n';

	std::cout << "\nInstructions (" << cpu.getInstructions().size() << "):\n";

	for (const Instruction& instruction : cpu.getInstructions()) {
		std::cout << "  Name: " << instruction.name << '\n';
		std::cout << "  Opcode: " << instruction.opcode << '\n';
		std::cout << "  Format: " << instruction.format << "\n\n";
	}
}