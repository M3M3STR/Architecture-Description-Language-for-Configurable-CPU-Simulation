#pragma once

#include <string>
#include <vector>
#include <stdio.h>
#include <any>
#include "ADLBaseVisitor.h"
#include "Common/IntermediateModel.h"


class IntermediateModelBuilder : public ADLBaseVisitor {
public:
	std::any visitArchitecture(ADLParser::ArchitectureContext* ctx) override;
	std::any visitDecl_list(ADLParser::Decl_listContext* ctx) override;
	std::any visitRegister_decl(ADLParser::Register_declContext* ctx) override;
	std::any visitReg_group(ADLParser::Reg_groupContext* ctx) override;
	std::any visitMemory_decl(ADLParser::Memory_declContext* ctx) override;
	std::any visitFormat_list(ADLParser::Format_listContext* ctx) override;
	std::any visitFormat_decl(ADLParser::Format_declContext* ctx) override;
	std::any visitField_decl(ADLParser::Field_declContext* ctx) override;
	//std::any visitField_type(ADLParser::Field_typeContext* ctx) override;
	//std::any visitBit_range(ADLParser::Bit_rangeContext* ctx) override;
	std::any visitInstruction_decl(ADLParser::Instruction_declContext* ctx) override;
	void printIntermediateModel(const IntermediateModel& model);
};