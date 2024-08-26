#pragma once

const uint8_t PMax = 8;

extern "C"
{
	__declspec(dllexport) void PrintMessage(const char* message);
	__declspec(dllexport) void PrintVar(const char* varName, int varValue);
	__declspec(dllexport) void PrintVarF(const char* varName, float varValue);
	__declspec(dllexport) void PrintVarHex(const char* varName, int varValue);

}