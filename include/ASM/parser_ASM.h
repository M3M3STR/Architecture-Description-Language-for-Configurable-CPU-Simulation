#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "antlr4-runtime.h"
#include "ASMLexer.h"
#include "ASMParser.h"

class parser_ASM {
public:
    ASMParser::ProgramContext* parseFromString(std::string sourceString);
    ASMParser::ProgramContext* parseFromFilePath(std::string filePath);
};