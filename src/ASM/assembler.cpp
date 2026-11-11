#include "ASM/assembler.h"
#include <iostream>

std::vector<uint64_t> Assembler::assemble(const std::vector<ParsedInstruction>& instructions, const IntermediateModel& model) {
    std::vector<uint64_t> machine_code;

    for (const auto& inst : instructions) {
        // 1. Find the instruction in Ricky's IR
        Instruction ir_inst;
        bool found = false;
        for (const auto& m_inst : model.getInstructions()) {
            if (m_inst.name == inst.mnemonic) {
                ir_inst = m_inst;
                found = true;
                break;
            }
        }
        if (!found) continue; // Skip if not found

        // 2. Find the format for this instruction
        InstructionFormat format;
        for (const auto& f : model.getInstructionFormats()) {
            if (f.name == ir_inst.format) {
                format = f;
                break;
            }
        }

        // 3. Pack the bits using the format's fields
        uint64_t machine_word = 0;
        int reg_index = 0; // Keep track of which register we are on
        int imm_index = 0; // Keep track of which immediate we are on

        for (const auto& field : format.fields) {
            // In Ricky's code, range.start is MSB, range.end is LSB
            int width = field.range.start - field.range.end + 1; 
            uint64_t value = 0;

            if (field.type == FieldType::OPCODE) {
                value = ir_inst.opcode;
            } 
            else if (field.type == FieldType::DESTINATION_REGISTER) {
                value = inst.operands[0].value; // Assume operand 0 is dest
            }
            else if (field.type == FieldType::SOURCE_REGISTER) {
                reg_index++;
                value = inst.operands[reg_index].value;
            }
            else if (field.type == FieldType::IMMEDIATE_UNSIGNED) {
                // Find the immediate operand
                for (const auto& op : inst.operands) {
                    if (op.type == OperandType::IMMEDIATE) {
                        value = op.value;
                        break;
                    }
                }
            }

            // Shift it to the correct position (range.end is the LSB position)
            machine_word |= (value << field.range.end);
        }

        std::cout << "Packed '" << inst.mnemonic << "' -> 0x" << std::hex << machine_word << std::dec << "\n";
        machine_code.push_back(machine_word);
    }

    return machine_code;
}