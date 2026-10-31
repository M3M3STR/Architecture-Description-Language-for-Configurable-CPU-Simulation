#include "assembler.h"
#include <iostream>
#include <cmath>

std::vector<uint64_t> Assembler::assemble(const std::vector<ParsedInstruction>& instructions, const CPU& cpu) {
    std::vector<uint64_t> machine_code;

    std::cout << "CPU Name: " << cpu.name << "\n";
    
    // calculate how many bits the opcode needs based on total instructions
    int opcode_bits = 1;
    if (cpu.instructions.size() > 1) {
        opcode_bits = std::ceil(std::log2(cpu.instructions.size()));
    }

    // calculate how many bits a register needs based on total registers
    int reg_bits = 1;
    if (cpu.register_count > 1) {
        reg_bits = std::ceil(std::log2(cpu.register_count));
    }

    // print for testing
    std::cout << "Word Size: " << cpu.word_size << " | Opcode Bits: " << opcode_bits << " | Reg Bits: " << reg_bits << "\n\n";

    for (int i = 0; i < instructions.size(); i++) {
        std::string mnemonic = instructions[i].mnemonic;
        std::vector<Operand> resolved_operands = instructions[i].operands;

        bool found = false;
        
        for (int j = 0; j < cpu.instructions.size(); j++){ 
            Instruction inst = cpu.instructions[j];
            
            if (inst.name == mnemonic) { 
                int opcode = inst.opcode;
                uint64_t machine_word = 0;
                
                // start the shift at the msb
                int current_shift = cpu.word_size - opcode_bits;
                
                // put the opcode at the far left
                machine_word = machine_word | (opcode << current_shift);

                // loop through operands and pack them
                for (int k = 0; k < resolved_operands.size(); k++) {
                    int val = resolved_operands[k].value;
                    
                    if (resolved_operands[k].type == OperandType::REGISTER) {
                        current_shift = current_shift - reg_bits;
                        machine_word = machine_word | (val << current_shift);
                    } 
                    else if (resolved_operands[k].type == OperandType::IMMEDIATE) {
                        // assuming immediate takes whatever bits are left
                        int imm_bits = cpu.word_size - opcode_bits - (2 * reg_bits); 
                        current_shift = current_shift - imm_bits;
                        machine_word = machine_word | (val << current_shift);
                    }
                }

                // Print the Hex and the binary representation
                std::cout << "Found '" << mnemonic << "' -> Hex: 0x" << std::hex << machine_word << std::dec << " | Binary: ";
                for (int b = cpu.word_size - 1; b >= 0; b--) {
                    std::cout << ((machine_word >> b) & 1);
                    if (b % 4 == 0 && b != 0){
                        std::cout << " ";
                    }
                }
                std::cout << "\n";

                machine_code.push_back(machine_word);
                found = true;
                break; 
            }
        }
        
        if (!found) {
            std::cout << "ERROR: Instruction '" << mnemonic << "' not found.\n";
        }
    }
    return machine_code;
}
