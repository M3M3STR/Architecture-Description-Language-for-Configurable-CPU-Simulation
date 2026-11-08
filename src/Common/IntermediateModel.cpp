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

void IntermediateModel::addRegister(const Register& reg) {
	this->registers.push_back(reg);
}

void IntermediateModel::addInstructionFormat(const InstructionFormat& format) {
	this->instruction_formats.push_back(format);
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

const std::vector<Register>& IntermediateModel::getRegisters() const {
	return this->registers;
}

// Instructions
void IntermediateModel::addInstruction(const Instruction& instruction) {
    this->instructions.push_back(instruction);
}
const std::vector<Instruction>& IntermediateModel::getInstructions() const {
    return this->instructions;
}

// Print the contents of the IntermediateModel for debugging purposes
void IntermediateModel::printIntermediateModel() {
	std::cout << "CPU Name: " << this->getName() << '\n';
	std::cout << "Register Count: " << this->getRegisterCount() << '\n';
	std::cout << "Registers:\nName\tBit Width\tNumber\n";

	for (const Register& reg : this->getRegisters()) {
			std::cout << "  " << reg.name << "\t" << reg.bit_width << "\t" << reg.number << '\n';
	}

	std::cout << "Memory Size: " << this->getMemorySize() << '\n';

	std::cout << "\nInstructions (" << this->getInstructions().size() << "):\n";

	for (const Instruction& instruction : this->getInstructions()) {
		std::cout << "  Name: " << instruction.name << '\n';
		std::cout << "  Opcode: " << instruction.opcode << '\n';
		std::cout << "  Format: " << instruction.format << "\n\n";
	}
}