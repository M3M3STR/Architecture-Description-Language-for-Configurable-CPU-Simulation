#include "assembler.h"
#include <iostream>

std::vector<uint32_t> Assembler::assemble(const std::vector<ParsedInstruction>& instructions, const CPU& cpu) {
    std::vector<uint32_t> machine_code; // the final list of binary numbers

    std::cout << "CPU Name: " << cpu.name << "\n";
    
    // loop through every instruction from the visitor
    for (int i = 0; i < instructions.size(); i++) { 
        std::string mnemonic = instructions[i].mnemonic;
        std::vector<int> resolved_operands = instructions[i].operands; // grab the numbers

        bool found = false;
        // loop through cpu instruction list
        for (int j = 0; j < cpu.instructions.size(); j++){  
            Instruction inst = cpu.instructions[j];
            
            // check if the names match
            if (inst.name == mnemonic) { 

                // grab the opcode from the cpu
                int opcode = inst.opcode;
                
                // print for testing
                std::cout << "Found '" << mnemonic << "' -> Opcode: 0x" << std::hex << opcode << std::dec << " | Operands: ";

                for (int k = 0; k < resolved_operands.size(); k++) {
                    std::cout << resolved_operands[k] << " ";
                }
                std::cout << "\n";
                
                // mark it found so we stop searching and stop the inner loop
                found = true;
                break; 
            }
        }
        
        // if we checked every cpu instruction and found nothing
        if (!found) {
            std::cout << "ERROR: Instruction '" << mnemonic << "' not found.\n";
        }
    }
    // return the final list
    return machine_code;
}
