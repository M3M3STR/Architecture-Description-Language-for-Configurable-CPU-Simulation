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
	return 0;
}

// Visit the register declaration and set the register count and groups in the IntermediateModel
std::any IntermediateModelBuilder::visitRegister_decl(ADLParser::Register_declContext* ctx) {
	//cpu.setRegisterCount(std::stoi(ctx->NUM()->getText()));

	for (auto* group : ctx->reg_group()) {
		visitReg_group(group);
	}
	return 0;
}

// Visit the register group, create and store each Register object
std::any IntermediateModelBuilder::visitReg_group(ADLParser::Reg_groupContext* ctx) {

	int width = std::stoi(ctx->NUM()->getText());

	for (auto* reg : ctx->ID()) {
		Register r;
		r.name = reg->getText();
		r.bit_width = width;
		r.number = cpu.registers.size();
		cpu.addRegister(r);
		cpu.register_count++;
	}

	return 0;
}

// Visit the memory declaration and set the memory size in the IntermediateModel
std::any IntermediateModelBuilder::visitMemory_decl(ADLParser::Memory_declContext* ctx) {
	cpu.setMemorySize(std::stoi(ctx->NUM()->getText()));
	return 0;
}

std::any IntermediateModelBuilder::visitFormat_list(ADLParser::Format_listContext* ctx) {
	
	for (auto* format : ctx->format_decl()) {
		InstructionFormat f = std::any_cast<InstructionFormat>(visitFormat_decl(format));
		cpu.addInstructionFormat(f);
	}
	return 0;
}

std::any IntermediateModelBuilder::visitFormat_decl(ADLParser::Format_declContext* ctx) {
	InstructionFormat format;
	format.name = ctx->ID()->getText();
	for (auto* field : ctx->field_decl()) {
		format.fields.push_back(std::any_cast<Field>(visitField_decl(field)));
	}
	return format;
}

std::any IntermediateModelBuilder::visitField_decl(ADLParser::Field_declContext* ctx) {
	Field f;

	std::string type = ctx->field_type()->getText();

	if (type == "OPCODE") {
		f.type = FieldType::OPCODE;
	} else if (type == "REG_DEST") {
		f.type = FieldType::DESTINATION_REGISTER;
	}
	else if (type == "REG_SRC") {
		f.type = FieldType::SOURCE_REGISTER;
	}
	else if (type == "IMM_UNSIGNED") {
		f.type = FieldType::IMMEDIATE_UNSIGNED;
	}

	f.range.start = std::stoi(ctx->bit_range()->NUM(0)->getText());
	f.range.end = std::stoi(ctx->bit_range()->NUM(1)->getText());

	return f;
}

// Visit the instruction declaration and add the instruction to the IntermediateModel
std::any IntermediateModelBuilder::visitInstruction_decl(ADLParser::Instruction_declContext* ctx) {
	Instruction instr;
	instr.name = ctx->ID(0)->getText();
	instr.opcode = std::stoi(ctx->opcode_decl()->opcode_value()->getText());
	instr.format = ctx->ID(1)->getText();
	cpu.addInstruction(instr);
	return 0;
}

