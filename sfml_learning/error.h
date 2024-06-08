#pragma once
#include <string>

struct ConsoleError
{
	static void throwError(std::string msg);
	static void throwError(const char* msg);
	static void throwError(int value);
};
