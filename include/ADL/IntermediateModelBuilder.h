#pragma once

#include <string>
#include <vector>
#include <stdio.h>
#include "ADLBaseVisitor.h"
#include "Common/IntermediateModel.h"


class IntermediateModelBuilder : public ADLBaseVisitor {
public:
	std::any visitArchitecture(ADLParser::ArchitectureContext* ctx) override;
	std::any visitDecl_list(ADLParser::Decl_listContext* ctx) override;
	std::any visitRegister_decl(ADLParser::Register_declContext* ctx) override;
	std::any visitMemory_decl(ADLParser::Memory_declContext* ctx) override;
	std::any visitInstruction_decl(ADLParser::Instruction_declContext* ctx) override;
	void printIntermediateModel(const IntermediateModel& model);
};