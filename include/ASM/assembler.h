#pragma once
#include <vector>
#include <string>
#include "ASM/AssemblerVisitor.h"
#include "Common/IntermediateModel.h"

class Assembler {
public:
    static std::vector<uint64_t> assemble( const std::vector<ParsedInstruction>& instructions, const IntermediateModel& model);
};