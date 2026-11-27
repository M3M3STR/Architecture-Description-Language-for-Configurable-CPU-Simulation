#pragma once

#include <string>

enum class OperandType {
	NONE = -1,
	REGISTER,
	IMMEDIATE,
	MEMORY
};

enum class AccessType {
	NONE = -1,
	INPUT,
	OUTPUT,
	INPUT_OUTPUT
};


struct Operand {
	std::string name = "";
	OperandType type = OperandType::NONE;
	AccessType access = AccessType::INPUT;
	bool implicit = false;
};

struct Instruction {
	std::string name = "";
	unsigned int opcode = -1;
	std::string format = "";
	std::vector<Operand> operands = {};
};

inline  std::string operandTypeToString(OperandType type) {
	switch (type) {
	case OperandType::REGISTER:
		return "REGISTER";
	case OperandType::IMMEDIATE:
		return "IMMEDIATE";
	case OperandType::MEMORY:
		return "MEMORY";
	default:
		return "NONE";
	}
}

inline std::string accessTypeToString(AccessType type) {
	switch (type) {
	case AccessType::INPUT:
		return "INPUT";
	case AccessType::OUTPUT:
		return "OUTPUT";
	case AccessType::INPUT_OUTPUT:
		return "INPUT_OUTPUT";
	default:
		return "NONE";
	}
}