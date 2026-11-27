#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "Register.h"
#include "Instruction.h"
#include "InstructionFormat.h"


class IntermediateModel
{

private:
    std::string name;
    int register_count = 0;
    std::vector<Register> registers;
    int memory_size = 0;
	int instruction_count = 0;
    std::vector<Instruction> instructions;
	std::vector<InstructionFormat> instruction_formats;

	friend class IntermediateModelBuilder;

    void setName(const std::string& name);
    void setRegisterCount(int count);
    void setMemorySize(int size);
    void addRegister(const Register& reg);
    void addInstructionFormat(const InstructionFormat& format);
    void addInstruction(const Instruction& instruction);

public:

    //Lookup
    const std::string& getName() const;

    int getRegisterCount() const;
    const std::vector<Register>& getRegisters() const;
    const Register& getRegisterByName(const std::string& registerName) const;

    
    const std::vector<Instruction>& getInstructions() const;
	const Instruction& getInstructionByName(const std::string& instructionName) const;
	const Instruction& getInstructionByOpcode(unsigned int opcode) const;

    const InstructionFormat& getInstructionFormatByName(const std::string& formatName) const;
    const std::vector<InstructionFormat>& getInstructionFormats() const;
    
    int getMemorySize() const;

    //Debug
    void printIntermediateModel() const;

};
