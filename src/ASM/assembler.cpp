#include "ASM/assembler.h"
#include <iostream>

std::vector<uint64_t> Assembler::assemble(const std::vector<ParsedInstruction>& instructions, const IntermediateModel& model) {
    std::vector<uint64_t> machine_code;

    for (const auto& inst : instructions) {
        // find the instruction in model
        Instruction ir_inst;
        bool found = false;
        for (const auto& m_inst : model.getInstructions()) {
            if (m_inst.name == inst.mnemonic) {
                ir_inst = m_inst;
                found = true;
                break;
            }
        }
        if (!found) continue; // skip if not found

        // find the format for this instruction
        InstructionFormat format;
        for (const auto& f : model.instruction_formats) {
            if (f.name == ir_inst.format) {
                format = f;
                break;
            }
        }

        // pack the bits using the format fields
        uint64_t machine_word = 0;
        int reg_index = 0; // keep track of which register we are on
        int imm_index = 0; // keep track of which immediate we are on

        for (const auto& field : format.fields) {
            // range.start is MSB and range.end is LSB
            int width = field.range.start - field.range.end + 1; 
            uint64_t value = 0;

            if (field.type == FieldType::OPCODE) {
                value = ir_inst.opcode;
            } 
            else if (field.type == FieldType::DESTINATION_REGISTER) {
                value = inst.operands[0].value; // assume operand 0 is dest
            }
            else if (field.type == FieldType::SOURCE_REGISTER) {
                reg_index++;
                value = inst.operands[reg_index].value;
            }
            else if (field.type == FieldType::IMMEDIATE_UNSIGNED) {
                // find the immediate operand
                for (const auto& op : inst.operands) {
                    if (op.type == OperandType::IMMEDIATE) {
                        value = op.value;
                        break;
                    }
                }
            }

            // shift it to the correct position
            machine_word |= (value << field.range.end);
        }

        std::cout << "Packed '" << inst.mnemonic << "' -> 0x" << std::hex << machine_word << std::dec << " | Binary: ";
        // print the upper 16 bits with a space every 4 bits
        for (int b = 15; b >= 0; b--) {
            std::cout << ((machine_word >> b) & 1);
            if (b % 4 == 0 && b != 0) {
                std::cout << " ";
            }
        }
        std::cout << "\n";
        machine_code.push_back(machine_word);
    }

    return machine_code;
}