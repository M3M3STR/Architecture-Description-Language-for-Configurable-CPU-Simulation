#include <iostream>
#include <string>
#include <print>
#include "ADL/ParserADL.h"
#include "ADL/ADLSemanticAnalyzer.h"
//#include "ASM/parser_ASM.h"

int main()
{
    
    std::string sourceADL = R"(
        architecture MyCPU {
            registers {
                16 { r0 r1 r2 r3 r4 r5 r6 r7 }
                32 { r8 r9 r10 r11 r12 r13 r14 r15 }
            }
            memory 1024
            format RRR {
                op opcode [1:0]
                rd reg_dest [4:2]
                rs1 reg_src [7:5]
                rs2 reg_src [10:8]
            }
            instruction add {
                opcode 1
                format RRR
                operands {
                    rd register output
                    rs1 register input
                    rs2 register input
                }
                behavior{
                    rd = rs1;
                }
            }
            instruction sub {
                opcode 2
                format RRR
                operands {
                    rd register output
                    rs1 register input
                    rs2 register input
                }
                behavior{
                    rd = rs1;
                }
            }
            instruction abc {
                opcode 3
                format RRR
                operands {
                    rd register output
                    rs1 register input
                    rs2 register input
                }
                behavior{
                    rd = rs1;
                }
            }
            instruction xyz {
                opcode 4
                format RRR
                operands {
                    rd register output
                    rs1 register input
                    rs2 register input
                }
                behavior{
                    rd = rs1;
                }
            }
        }
    )";

    std::string sourceASM = R"(
        add r1, r2, r3
        sub r4, r5, r6
        # this is a comment
        add r7, r1, r4   # inline comment
    )";


    ParserADL parserADL;
	
    std::expected<IntermediateModel, std::vector<SyntaxError>> adlResult = parserADL.parseFromString(sourceADL);
    if (!adlResult)
    {
        std::cerr << "Failed to parse ADL: " << std::endl;

        for (const auto& error : adlResult.error())
        {
            std::cerr
                << "Line " << error.line
                << ", Column " << error.column
                << ": " << error.msg << '\n';
        }

        return 1;
    }
    IntermediateModel cpu = adlResult.value();
    cpu.printIntermediateModel();


    ADLSemanticAnalyzer adl_analyzer(cpu);
    
	std::expected<bool, std::vector<std::string>> semanticResult = adl_analyzer.analyze();

	if (!semanticResult) {
		std::cerr << "Semantic analysis failed with the following errors:\n";
		for (const auto& error : semanticResult.error()) {
			std::cerr << "  - " << error << '\n';
		}
		return 1;
	}
	else {
		std::cout << "Semantic analysis passed successfully.\n";
	}

    Register test = Register();

	std::cout << "Test Register Name: " << test.name << ", Bit Width: " << test.bit_width << ", Number: " << test.number << std::endl;


    //parser_ASM parserASM;
    //std::expected<ASMDefinition, std::vector<SyntaxError>> asmResult = parserASM.parseFromString(sourceASM);
    //if (!asmResult)
    //{
    //    std::cerr << "Failed to parse ASM: " << asmResult.error() << '\n';
    //    return 1;
    //}
    //ASMDefinition asmDef = asmResult.value();

    return 0;
}