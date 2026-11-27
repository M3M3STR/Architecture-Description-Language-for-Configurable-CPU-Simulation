#include "ASM/assembler.h"
#include <iostream>

std::vector<uint64_t> Assembler::assemble(const std::vector<ParsedInstruction>& instructions, const IntermediateModel& model) {
    std::vector<uint64_t> machine_code;

    std::unordered_map<std::string, int> reg_lookup;
    for (const auto& reg : model.getRegisters()) {
        reg_lookup[reg.name] = reg.number;
    }

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
        for (const auto& f : model.getInstructionFormats()) {
            if (f.name == ir_inst.format) {
                format = f;
                break;
            }
        }

        // pack the bits using the format fields
        uint64_t machine_word = 0;
        
        int reg_index = 0; // keep track of which register we are on

        for (const auto& field : format.fields) {

            uint64_t value = 0;

            if (field.type == FieldType::OPCODE) {
                value = ir_inst.opcode;
            } 
            else if (field.type == FieldType::DESTINATION_REGISTER) {
                std::string regName = inst.operands[0].text;
            
                if (reg_lookup.find(regName) != reg_lookup.end()) {
                    value = reg_lookup[regName];
                }
            }
            else if (field.type == FieldType::SOURCE_REGISTER) {
                reg_index++;
                std::string regName = inst.operands[reg_index].text;
                
                if (reg_lookup.find(regName) != reg_lookup.end()) {
                    value = reg_lookup[regName];
                }
            }
            else if (field.type == FieldType::IMMEDIATE_UNSIGNED) {
                for (const auto& op : inst.operands) {
                    if (op.type == ParsedOperandType::IMMEDIATE) {
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