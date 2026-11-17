#pragma once

#include <string>

struct Instruction {
	std::string name;
	unsigned int opcode;
	std::string format;
};