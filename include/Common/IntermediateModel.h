#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Instruction.h"

class IntermediateModel
{
private:
    std::string name;
    int register_count = 0;
    int memory_size = 0;
    std::vector<Instruction> instructions;

public:

    // Setters
    void setName(const std::string& name);
    void setRegisterCount(int count);
    void setMemorySize(int size);

    // Getters
    const std::string& getName() const;
    int getRegisterCount() const;
    int getMemorySize() const;

    // Instructions
    void addInstruction(const Instruction& instruction);
    const std::vector<Instruction>& getInstructions() const;

    //Debug
    void printIntermediateModel(const IntermediateModel& cpu);
};