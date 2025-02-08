#include "pch.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include "Chocola.h"
#include "Amy.h"
#include "speed.h"


extern "C"
{
	__declspec(dllexport) void InitializeOutput() {

	}

	__declspec(dllexport) void PrintMessage(const char* message)
	{
		std::cout << message << "\n" << std::endl;
	}

	__declspec(dllexport) void PrintVar(const char* varName, int varValue)
	{
		std::cout << varName << " = " << varValue << "\n" << std::endl;
	}

	__declspec(dllexport) void PrintVarF(const char* varName, float varValue)
	{
		std::cout << varName << " = " << varValue << "\n" << std::endl;
	}

	__declspec(dllexport) void PrintVarHex(const char* varName, int varValue)
	{
		std::cout << varName << " = " << std::hex << varValue << "\n" << std::endl;
	}

	__declspec(dllexport) void ReloadedStart()
	{

		PrintMessage("New Tricks says Hello from C++\n");
		SpeedChars::Init();
		InitChocola();
		initBird();
	}
}