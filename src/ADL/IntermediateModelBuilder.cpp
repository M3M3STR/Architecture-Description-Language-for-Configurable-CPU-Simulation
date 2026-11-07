#include "ADL/IntermediateModelBuilder.h"


IntermediateModel cpu;

// Visit the architecture node and set the name of the IntermediateModel
std::any IntermediateModelBuilder::visitArchitecture(ADLParser::ArchitectureContext* ctx) {
	cpu.setName(ctx->ID()->getText());
	visitChildren(ctx);
	return cpu;
}

// Visit the declaration list and process each declaration
std::any IntermediateModelBuilder::visitDecl_list(ADLParser::Decl_listContext* ctx) {
	visitChildren(ctx);
	return cpu;
}

// Visit the register declaration and set the register count in the IntermediateModel
std::any IntermediateModelBuilder::visitRegister_decl(ADLParser::Register_declContext* ctx) {
	cpu.setRegisterCount(std::stoi(ctx->NUM()->getText()));
	return cpu;
}

// Visit the memory declaration and set the memory size in the IntermediateModel
std::any IntermediateModelBuilder::visitMemory_decl(ADLParser::Memory_declContext* ctx) {
	cpu.setMemorySize(std::stoi(ctx->NUM()->getText()));
	return cpu;
}

// Visit the instruction declaration and add the instruction to the IntermediateModel
std::any IntermediateModelBuilder::visitInstruction_decl(ADLParser::Instruction_declContext* ctx) {
	Instruction instr;
	instr.name = ctx->ID()->getText();
	instr.opcode = std::stoi(ctx->opcode_decl()->opcode_value()->getText());
	instr.format = ctx->format_decl()->ID()->getText();
	cpu.addInstruction(instr);
	return cpu;
}

