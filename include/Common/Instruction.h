#pragma once

#include <string>

struct Instruction {
	std::string name;
	int opcode;
	std::string format;
} typedef Instruction;