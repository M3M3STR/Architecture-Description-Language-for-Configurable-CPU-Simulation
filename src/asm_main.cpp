#include <iostream>
#include <string>

#include "antlr4-runtime.h"
#include "ASMLexer.h"
#include "ASMParser.h"


struct Instruction {
    std::string name;
    int opcode;
    std::string format;
};

struct CPU {
    std::string name;
    int register_count;
    int memory_size;
    std::vector<Instruction> instructions;
};


int main()
{
    // fake cpu data example
    CPU my_cpu;
    my_cpu.name = "RISC32";
    my_cpu.instructions.push_back({"add", 0x01, "RR"});
    my_cpu.instructions.push_back({"sub", 0x02, "RR"});
    my_cpu.instructions.push_back({"bloop", 0x99, "RR"});


    // fake assembly file
    std::string source = R"(
        add r1, r2, r3
        sub r4, r5, r6
        bloop r1, r2
    )";

    // antlr setup
    antlr4::ANTLRInputStream input(source);
    ASMLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    ASMParser parser(&tokens);
    auto* tree = parser.program();

    // assembler loop: nextline -> fetch instruction -> encode bits ->nextline....
    // first store every line the parser found in a vector to iterate over
    std::vector<ASMParser::LineContext*> all_lines = tree->line();

    for (int i = 0; i < all_lines.size(); i++){

        // take the line at this position
        ASMParser::LineContext* line = all_lines[i];

        // does instrucion exist on this line? (could be commment or newline)
        if (line->instruction() != nullptr){
            std::string mnemonic = line->instruction()->ID()->getText();
           
            /*  find which instruction inside my_cpu's instruction vector matches the mnemonic
                once found, we grab the opcode and move on to the next line
                if not found then flag it with found and after the loop use it to print error
            */
            bool found = false;
            for (int j = 0; j < my_cpu.instructions.size(); j++){ // iterate over my_cpu's instruction vector

                // take the instruction at this position
                Instruction inst = my_cpu.instructions[j];
                if (inst.name == mnemonic) { // does the mnemonic match this instruction's name?

                    
                    int opcode = inst.opcode;
                    
                    // store the resolved operands in an int vector
                    std::vector<int> resolved_operands;
                    if (line->instruction()->operand_list() != nullptr) { // does operand list exist?
                        
                        // get vector of operands
                        std::vector<ASMParser::OperandContext*> operands = line->instruction()->operand_list()->operand();
                        for (int k = 0; k < operands.size(); k++){ // iterate over the list of operands
                            ASMParser::OperandContext* op = operands[k];

                            if(op->REG() != nullptr) { // is the operand a register?
                                std::string regText = op->REG()->getText();
                                int regNum = std::stoi(regText.substr(1)); // 'r15' -> int 15
                                resolved_operands.push_back(regNum);
                            }

                            else if (op->NUM() != nullptr) { // or is the operand a number?
                                std::string numText = op->NUM()->getText();
                                int num = std::stoi(numText);
                                resolved_operands.push_back(num);
                            } 
                        }
                    }
                    // print
                    std::cout << "Found '" << mnemonic << "' -> Opcode: 0x" << std::hex << opcode << " | Operands: ";

                    for (int k = 0; k < resolved_operands.size(); k++) {
                        std::cout << resolved_operands[k] << " ";
                    }
                    std::cout << "\n";

                    found = true;
                    break; // no need to continue searching
                }
            }
            
            if (!found) {
                std::cout << "ERROR: Instruction '" << mnemonic << "' not found.\n";
            }
        }
    }
    return 0;
}