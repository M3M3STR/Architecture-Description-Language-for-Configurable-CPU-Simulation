#pragma once
#include <string>
#include <vector>
#include "ASMBaseVisitor.h"

enum class ParsedOperandType { // holds whether the operand is a register or number
    REGISTER,
    IMMEDIATE
};

struct ParsedOperand { // hold the type, value, and str
    ParsedOperandType type;
    int value;
    std::string text;
};

struct ParsedInstruction {  // hold both the mnemonic and operands
    std::string mnemonic;
    std::vector<ParsedOperand> operands;
};

class AssemblerVisitor : public ASMBaseVisitor { // walks the tree and grabs the data
public:
    std::vector<ParsedInstruction> instructions; // store every instruction it finds
    
    // override the functions to build the data 
    std::any visitInstruction(ASMParser::InstructionContext* ctx) override;
    std::any visitOperand_list(ASMParser::Operand_listContext* ctx) override;
    std::any visitOperand(ASMParser::OperandContext* ctx) override;
};