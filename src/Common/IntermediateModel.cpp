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
	this->register_count++;
}

void IntermediateModel::addInstructionFormat(const InstructionFormat& format) {
	this->instruction_formats.push_back(format);
	this->instruction_count++;
}

// Lookup

const InstructionFormat& IntermediateModel::getInstructionFormatByName(const std::string& formatName) const {
	for (const auto& format : this->instruction_formats) {
		if (format.name == formatName) {
			return format;
		}
	}
	return InstructionFormat();
}

const std::vector<InstructionFormat>& IntermediateModel::getInstructionFormats() const {
	return this->instruction_formats;
}

const Instruction& IntermediateModel::getInstructionByName(const std::string& instructionName) const {
	for (const auto& instruction : this->instructions) {
		if (instruction.name == instructionName) {
			return instruction;
		}
	}
	return Instruction();
}

const Instruction& IntermediateModel::getInstructionByOpcode(unsigned int opcode) const {
	for (const auto& instruction : this->instructions) {
		if (instruction.opcode == opcode) {
			return instruction;
		}
	}
	return Instruction();
}

const Register& IntermediateModel::getRegisterByName(const std::string& registerName) const {
	for (const auto& reg : this->registers) {
		if (reg.name == registerName) {
			return reg;
		}
	}
	return Register();
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
void IntermediateModel::printIntermediateModel() const {
	std::cout << "CPU Name: " << this->getName() << '\n';
	std::cout << "Register Count: " << this->getRegisterCount() << '\n';
	std::cout << "Registers:\nName\tBit Width\tNumber\n";

	for (const Register& reg : this->getRegisters()) {
			std::cout << "  " << reg.name << "\t\t" << reg.bit_width << "\t\t" << reg.number << '\n';
	}

	std::cout << "Memory Size: " << this->getMemorySize() << '\n';

	std::cout << "\nInstruction Formats (" << this->getInstructionFormats().size() << "):\n";
	std::cout << "  Name:\tOperands:\t\n";
	for (const InstructionFormat& format : this->getInstructionFormats()) {
		std::cout << "  " << format.name << "\t";
		for (const Field& field : format.fields) {
			std::cout << field.name << ": " << fieldTypeToString(field.type) << "[" << field.range.start << ":" << field.range.end << "] ";
		}
		std::cout << '\n';
	}

	std::cout << "\nInstructions (" << this->getInstructions().size() << "):\n";

	for (const Instruction& instruction : this->getInstructions()) {
		std::cout << "  Name: " << instruction.name << '\n';
		std::cout << "  Opcode: " << instruction.opcode << '\n';
		std::cout << "  Format: " << instruction.format << "\n";
		std::cout << "  Operands: ";
		for (const Operand& operand : instruction.operands) {
			std::cout << operand.name << ":( type: " << operandTypeToString(operand.type) << " access: " << accessTypeToString(operand.access) << ") ";
		}
		std::cout << '\n';
	}
}