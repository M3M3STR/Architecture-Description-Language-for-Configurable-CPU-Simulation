#pragma once
#include <vector>
#include <string>
#include "AssemblerVisitor.h" 
#include "CPUDefinitionVisitor.h" 

class Assembler {
public:
    // takes the clean list and the cpu to make machine code
    static std::vector<uint64_t> assemble(const std::vector<ParsedInstruction>& instructions, const CPU& cpu);
};
