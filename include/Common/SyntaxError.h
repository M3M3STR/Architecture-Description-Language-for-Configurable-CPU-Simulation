#pragma once

#include <string>

struct SyntaxError {
	size_t line;
	size_t column;
	std::string msg;
} typedef SyntaxError;