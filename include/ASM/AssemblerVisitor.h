#pragma once
#include <string>
#include <vector>
#include "ASMBaseVisitor.h"

struct ParsedInstruction {  // hold instruction data
    std::string mnemonic;
    std::vector<int> operands;
};

class AssemblerVisitor : public ASMBaseVisitor { // walks the tree and grabs the data
public:
    std::vector<ParsedInstruction> instructions; // store every instruction it finds

    std::any visitInstruction(ASMParser::InstructionContext* ctx) override; // runs every time it finds an instruction in the tree
};
