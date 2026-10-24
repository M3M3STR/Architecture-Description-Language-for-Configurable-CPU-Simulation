#include "ADLBaseVisitor.h"
#include "CPUDefinitionVisitor.h"
#include <stdio.h>

class CPUDefinitionVisitor : public ADLBaseVisitor {

public:
	CPU cpu;

	std::any visitArchitecture(ADLParser::ArchitectureContext* ctx) override {
		cpu.name = ctx->ID()->getText();
		visitChildren(ctx);
		return cpu;
	}

	std::any visitDecl_list(ADLParser::Decl_listContext* ctx) override {
		visitChildren(ctx);
		return cpu;
	}

	std::any visitRegister_decl(ADLParser::Register_declContext* ctx) override {
		cpu.register_count = std::stoi(ctx->NUM()->getText());
		return cpu;
	}

	std::any visitMemory_decl(ADLParser::Memory_declContext* ctx) override {
		cpu.memory_size = std::stoi(ctx->NUM()->getText());
		return cpu;
	}

	std::any visitInstruction_decl(ADLParser::Instruction_declContext* ctx) override {
		Instruction instr;
		instr.name = ctx->ID()->getText();
		instr.opcode = std::stoi(ctx->opcode_decl()->opcode_value()->getText());
		instr.format = ctx->format_decl()->ID()->getText();
		cpu.instructions.push_back(instr);
		return cpu;
	}

};




