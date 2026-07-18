#include "pch.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include "speed.h"
#include "Fly.h"
#include "Power.h"
#include "config.h"
#include <inputs.h>

bool isExpandedActLoaded = false;


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

		HMODULE newActApi = GetModuleHandleW(L"SH-Action-Expander.dll");

		if (!newActApi)
		{
			printf("Couldn't find dependency Sonic Heroes Action Expander, some custom moves won't work\n");
		}
		else
		{
			isExpandedActLoaded = true;
		}
		

		SpeedChars::Init();
		FlyChars::Init();
		PowerChars::Init();
		Init_InputHooks();
	}
}