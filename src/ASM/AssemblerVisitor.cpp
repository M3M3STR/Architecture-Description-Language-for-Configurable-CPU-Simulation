#include "ASMVisitor.h"
#include "AssemblerVisitor.h"
#include <iostream>

std::any AssemblerVisitor::visitInstruction(ASMParser::InstructionContext* ctx) {
    ParsedInstruction inst;
    
    inst.mnemonic = ctx->ID()->getText();

    // does operand list exist? 
    if (ctx->operand_list() != nullptr) {
        std::vector<ASMParser::OperandContext*> operands = ctx->operand_list()->operand(); // get the list of operands from the tree
        
        for (int i = 0; i < operands.size(); i++) { 
            ASMParser::OperandContext* op = operands[i];  
            
            if (op->REG() != nullptr) { // is the operand a register?
                std::string regText = op->REG()->getText();
                inst.operands.push_back(std::stoi(regText.substr(1))); // 'r15' -> int 15
            } 
            else if (op->NUM() != nullptr) { // or is the operand a number?
                inst.operands.push_back(std::stoi(op->NUM()->getText()));
            }
        }
    }

    instructions.push_back(inst); // save this finished instruction
    
    return {};
}
