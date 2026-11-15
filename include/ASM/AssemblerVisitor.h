#pragma once
#include <string>
#include <vector>
#include "ASMBaseVisitor.h"

enum class OperandType { // holds whether the operand is a register or number
    REGISTER,
    IMMEDIATE
};

struct Operand { // hold both the type and the value
    OperandType type;
    int value;
};

struct ParsedInstruction {  // hold both the mnemonic and operands
    std::string mnemonic;
    std::vector<Operand> operands;
};

class AssemblerVisitor : public ASMBaseVisitor { // walks the tree and grabs the data
public:
    std::vector<ParsedInstruction> instructions; // store every instruction it finds
    std::any visitInstruction(ASMParser::InstructionContext* ctx) override; // runs every time it finds an instruction in the tree
};
