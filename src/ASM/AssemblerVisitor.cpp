#include "ASM/AssemblerVisitor.h"

std::any AssemblerVisitor::visitOperand(ASMParser::OperandContext* ctx) {
    ParsedOperand my_op;
    
    if (ctx->ID() != nullptr) {
        my_op.type = ParsedOperandType::REGISTER;
        my_op.text = ctx->ID()->getText();
        my_op.value = 0; 
    } 
    else if (ctx->NUM() != nullptr) {
        my_op.type = ParsedOperandType::IMMEDIATE;
        my_op.text = ctx->NUM()->getText();
        my_op.value = std::stoi(my_op.text);
    }
    
    return my_op; // return the single operand up the tree
}

std::any AssemblerVisitor::visitOperand_list(ASMParser::Operand_listContext* ctx) {
    std::vector<ParsedOperand> ops;
    
    for (auto* child : ctx->operand()) {
        // visit each operand and cast the result back to an Operand
        ops.push_back(std::any_cast<ParsedOperand>(visit(child)));
    }
    
    return ops; // return the completed list of operands
}

std::any AssemblerVisitor::visitInstruction(ASMParser::InstructionContext* ctx) {
    ParsedInstruction inst;
    
    // get the mnemonic "[add] ..."
    inst.mnemonic = ctx->ID()->getText();  

    // if there are operands visit the list and grab the vector
    if (ctx->operand_list() != nullptr) {
        inst.operands = std::any_cast<std::vector<ParsedOperand>>(visit(ctx->operand_list()));
    }

    // save to main list
    instructions.push_back(inst); 
    
    return {};
}