#include "pch.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <fcntl.h>
#include <io.h>

/*Example of function you can make Reloaded use from C++ such as printing*/



extern "C"
{
	__declspec(dllexport) void InitializeOutput() {
		// Get the handle to the current console output
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		// Redirect stdout to the console handle
		int fd = _open_osfhandle((intptr_t)hConsole, _O_TEXT);
		FILE* file = _fdopen(fd, "w");
		*stdout = *file;
		setvbuf(stdout, NULL, _IONBF, 0);

		// Also redirect std::cout to the console
		std::ios::sync_with_stdio();
		std::cout.clear();
	}

	__declspec(dllexport) void PrintMessage(const char* message)
	{
		std::cout << message << "\n" << std::endl;
	}

	__declspec(dllexport) void PrintVar(const char* varName, int varValue)
	{
		std::cout << varName << " = " << varValue << "\n" << std::endl;
	}

	__declspec(dllexport) void ReloadedStart()
	{
		PrintMessage("Hello from C++\n");
	}
}