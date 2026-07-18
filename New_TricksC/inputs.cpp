#include "pch.h"
#include "inputs.h"

// in Heroes we lack buttons choice since B and Y are used for formation changes
// Bumpers also matches triggers which left us without much choices
// As a workaround, we can edit formation changes button to use the d-pad instead
// this give us free inputs for B and Y for custom actions!

static uint32_t g_currentButtonFlags[PMax] = { 0 };
static uint32_t g_oneFramePressFlags[PMax] = { 0 };

void UpdateInputState(uint32_t buttonFlags, uint32_t oneFramePressFlags, int port)
{
    if (port < 0 || port >= PMax)
        return;

    g_currentButtonFlags[port] = buttonFlags;
    g_oneFramePressFlags[port] = oneFramePressFlags;
}

static int GetRealPhysicalControllerID(int port)
{
	if (port < 0 || port >= PMax)
		return -1;

	return port /= 3;
}

int IsButtonHeld(uint32_t buttonMask, int port)
{
	port = GetRealPhysicalControllerID(port);

    if (port < 0)
        return -1;

    return (g_currentButtonFlags[port] & buttonMask) != 0 ? 1 : 0;
}

int IsButtonPressed(uint32_t buttonMask, int port)
{
	port = GetRealPhysicalControllerID(port);

	if (port < 0)
		return -1;

	return (g_oneFramePressFlags[port] & buttonMask) != 0 ? 1 : 0;
}


// the function TObjTeam::CheckChangeLeaderButton is pretty big, we can avoid rewriting entirely with mid asm hook
// the idea is calling our asm function just before the game check for Y button press
// then we backup registers to avoid corruption, call a custom function that check for d-pad left press instead
// then we restore registers and jump back to the original code

static uint32_t retAddrFormChange = 0x5AFA5E;
static uint32_t retAddrFormChange2 = 0x5AF9E3;

__declspec(naked) void FormChangeHookDPadLeftASM()
{
	__asm {

		mov eax, ecx
		shr eax, 4 // player index

		push eax
		push DpadLeft //arg 1 (button id / mask)
		call IsButtonPressed // cdecl: eax = 1 if pressed, 0 if not
		add esp, 8 //  caller cleans stack(cdecl)

		test eax, eax

		ret
	}
}


__declspec(naked) void FormChangeHookWrapper1()
{
	__asm {
		pushad //backup all regs first
		call FormChangeHookDPadLeftASM
		popad // restore all original regs
		jmp dword ptr[retAddrFormChange] // jump back 
	}
}

__declspec(naked) void FormChangeHookWrapper2()
{
	__asm {
		pushad //backup all regs first
		call FormChangeHookDPadLeftASM
		popad // restore all original regs
		jmp dword ptr[retAddrFormChange2] // jump back 
	}
}


// repeat but for d-pad right press instead (B originally)

__declspec(naked) void FormChangeHookDPadRightASM()
{
	__asm {

		mov eax, ecx
		shr eax, 4 // player index

		push eax
		push DpadRight //arg 1 (button id / mask)
		call IsButtonPressed // cdecl: eax = 1 if pressed, 0 if not
		add esp, 8 //  caller cleans stack(cdecl)

		test eax, eax

		ret
	}
}

static uint32_t retAddrFormChangeR = 0x5AFC4E;
static uint32_t retAddrFormChangeR2 = 0x5AFBD3;

__declspec(naked) void FormChangeRHookWrapper1()
{
	__asm {
		pushad //backup all regs first
		call FormChangeHookDPadRightASM
		popad // restore all original regs
		jmp dword ptr[retAddrFormChangeR] // jump back 
	}
}

__declspec(naked) void FormChangeRHookWrapper2()
{
	__asm {
		pushad //backup all regs first
		call FormChangeHookDPadRightASM
		popad // restore all original regs
		jmp dword ptr[retAddrFormChangeR2] // jump back 
	}
}

void Init_InputHooks()
{
	WriteJump((void*)0x05AFA57, FormChangeHookWrapper1);
	WriteData<2>((uint8_t*)0x5AFA5C, 0x90);

	WriteJump((void*)0x5AF9DC, FormChangeHookWrapper2);
	WriteData<2>((uint8_t*)0x5AF9E1, 0x90);

	WriteJump((void*)0x5AFC47, FormChangeRHookWrapper1);
	WriteData<2>((uint8_t*)0x5AFC4C, 0x90);

	WriteJump((void*)0x5AFBCC, FormChangeRHookWrapper2);
	WriteData<2>((uint8_t*)0x5AFBD1, 0x90);
}