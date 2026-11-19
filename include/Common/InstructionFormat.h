#pragma once

#include <string>
#include <vector>

enum class FieldType {
	NONE = -1,
	OPCODE,
	DESTINATION_REGISTER,
	SOURCE_REGISTER,
	IMMEDIATE_UNSIGNED,
	
};

const std::string fieldTypeNames[] = {
	"NONE",
	"OPCODE",
	"DESTINATION_REGISTER",
	"SOURCE_REGISTER",
	"IMMEDIATE_UNSIGNED"
};

inline std::string fieldTypeToString(FieldType type) {
	return fieldTypeNames[static_cast<int>(type) + 1]; // +1 to account for NONE being -1
}

struct BitRange {
	int start = -1;
	int end = -1;
};

struct Field {
	std::string name = "";
	FieldType type = FieldType::NONE;
	BitRange range = BitRange();
};



struct InstructionFormat {
	std::string name = "";
	std::vector<Field> fields = {};
};
