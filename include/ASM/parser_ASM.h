#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <expected>
#include "ASM/AssemblerVisitor.h"
#include "Common/SyntaxError.h" 

class parser_ASM {
public:
    std::expected<std::vector<ParsedInstruction>, std::vector<SyntaxError>> 
    parseFromString(std::string sourceString);

    std::expected<std::vector<ParsedInstruction>, std::vector<SyntaxError>> 
    parseFromFilePath(std::string filePath);
};