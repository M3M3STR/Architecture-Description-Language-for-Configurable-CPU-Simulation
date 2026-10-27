#include "CPUDefinitionVisitor.h"


CPU cpu;

std::any CPUDefinitionVisitor::visitArchitecture(ADLParser::ArchitectureContext* ctx) {
	cpu.name = ctx->ID()->getText();
	visitChildren(ctx);
	return cpu;
}

std::any CPUDefinitionVisitor::visitDecl_list(ADLParser::Decl_listContext* ctx) {
	visitChildren(ctx);
	return cpu;
}

std::any CPUDefinitionVisitor::visitRegister_decl(ADLParser::Register_declContext* ctx) {
	cpu.register_count = std::stoi(ctx->NUM()->getText());
	return cpu;
}

std::any CPUDefinitionVisitor::visitMemory_decl(ADLParser::Memory_declContext* ctx) {
	cpu.memory_size = std::stoi(ctx->NUM()->getText());
	return cpu;
}

std::any CPUDefinitionVisitor::visitInstruction_decl(ADLParser::Instruction_declContext* ctx) {
	Instruction instr;
	instr.name = ctx->ID()->getText();
	instr.opcode = std::stoi(ctx->opcode_decl()->opcode_value()->getText());
	instr.format = ctx->format_decl()->ID()->getText();
	cpu.instructions.push_back(instr);
	return cpu;
}

void CPUDefinitionVisitor::printCPU(const CPU& cpu) {
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

