#pragma once

#include <string>
#include <vector>

enum class FieldType {
	OPCODE,
	DESTINATION_REGISTER,
	SOURCE_REGISTER,
	IMMEDIATE_UNSIGNED,
	
};

struct BitRange {
	int start;
	int end;
};

struct Field {
	FieldType type;
	BitRange range;
};



struct InstructionFormat {
	std::string name;
	std::vector<Field> fields;
};
