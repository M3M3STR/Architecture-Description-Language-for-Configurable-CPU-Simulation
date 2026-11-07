#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "AssemblerVisitor.h"

class parser_ASM {
public:
    // takes text and returns a list of clean instructions
    std::vector<ParsedInstruction> parseFromString(std::string sourceString);
    std::vector<ParsedInstruction> parseFromFilePath(std::string filePath);
};  
