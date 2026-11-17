#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Register.h"
#include "Instruction.h"
#include "InstructionFormat.h"


class IntermediateModel
{
//private:

public:

    std::string name;
    int register_count = 0;
    std::vector<Register> registers;
    int memory_size = 0;
    std::vector<Instruction> instructions;
	std::vector<InstructionFormat> instruction_formats;

    // Setters
    void setName(const std::string& name);
    void setRegisterCount(int count);
    void setMemorySize(int size);
    void addRegister(const Register& reg);
    void addInstructionFormat(const InstructionFormat& format);

    // Getters
    const std::string& getName() const;
    int getRegisterCount() const;
    int getMemorySize() const;
    const std::vector<Register>& getRegisters() const;

    // Instructions
    void addInstruction(const Instruction& instruction);
    const std::vector<Instruction>& getInstructions() const;

    //Debug
    void printIntermediateModel();
};