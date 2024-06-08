#include <iostream>
#include "error.h"
#include <string>

void ConsoleError::throwError(std::string msg)
{
	std::cout << " -[ERROR] " << msg << "\n";
}

void ConsoleError::throwError(const char* msg)
{
	std::cout << " -[ERROR] " << msg << "\n";
}

void ConsoleError::throwError(int value)
{
	std::cout << " -[ERROR-Value] Value: " << value << "\n";
}


