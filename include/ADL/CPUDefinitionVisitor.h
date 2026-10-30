#pragma once

#include <string>
#include <vector>
#include <stdio.h>
#include "ADLBaseVisitor.h"

struct Instruction {
	std::string name;
	int opcode;
	std::string format;
} typedef Instruction;

struct CPU {
	std::string name;
	int register_count;
	int memory_size;
	int word_size;
	std::vector<Instruction> instructions;
} typedef CPU;

class CPUDefinitionVisitor : public ADLBaseVisitor {
public:
	std::any visitArchitecture(ADLParser::ArchitectureContext* ctx) override;
	std::any visitDecl_list(ADLParser::Decl_listContext* ctx) override;
	std::any visitRegister_decl(ADLParser::Register_declContext* ctx) override;
	std::any visitMemory_decl(ADLParser::Memory_declContext* ctx) override;
	std::any visitInstruction_decl(ADLParser::Instruction_declContext* ctx) override;
	void printCPU(const CPU& cpu);
};