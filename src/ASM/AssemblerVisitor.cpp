#include "ASMVisitor.h"
#include "AssemblerVisitor.h"
#include <iostream>

std::any AssemblerVisitor::visitInstruction(ASMParser::InstructionContext* ctx) {
    ParsedInstruction inst;
    
    inst.mnemonic = ctx->ID()->getText();  // "[add] r1, r2, 3"

    // does operand list exist? 
    if (ctx->operand_list() != nullptr) {
        std::vector<ASMParser::OperandContext*> operands = ctx->operand_list()->operand(); // get the list of operands from the tree "add [r1, r2, 3]"
        
        for (int i = 0; i < operands.size(); i++) { 
            ASMParser::OperandContext* op = operands[i];  
            Operand my_op;

            if (op->REG() != nullptr) { // is the operand a register?
                std::string regText = op->REG()->getText();     // gets 'r1'
                my_op.type = OperandType::REGISTER;             // set the type to register
                my_op.value = std::stoi(regText.substr(1));     // from 'r1' to value = 1
                inst.operands.push_back(my_op);                 // goes into ParsedInstruction's <Operand> vector
            } 
            else if (op->NUM() != nullptr) { // or is the operand a number?
                my_op.type = OperandType::IMMEDIATE;            // set the type to immediate
                my_op.value = std::stoi(op->NUM()->getText());  // from '3' to value = 3
                inst.operands.push_back(my_op);                 // goes into <Operand> vector
            }
        }
    }

    instructions.push_back(inst); // save this finished instruction
    
    return {};
}
