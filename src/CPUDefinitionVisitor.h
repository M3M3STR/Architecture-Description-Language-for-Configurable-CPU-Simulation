#pragma once

#include <string>
#include <vector>

struct Instruction {
	std::string name;
	int opcode;
	std::string format;
} typedef Instruction;

struct CPU {
	std::string name;
	int register_count;
	int memory_size;
	std::vector<Instruction> instructions;
} typedef CPU;

void printCPU(const CPU& cpu) {
    std::cout << "CPU Name: " << cpu.name << '\n';
    std::cout << "Register Count: " << cpu.register_count << '\n';
    std::cout << "Memory Size: " << cpu.memory_size << '\n';

    std::cout << "\nInstructions (" << cpu.instructions.size() << "):\n";

    for (const Instruction& instruction : cpu.instructions) {
        std::cout << "  Name: " << instruction.name << '\n';
        std::cout << "  Opcode: " << instruction.opcode << '\n';
        std::cout << "  Format: " << instruction.format << "\n\n";
    }
}