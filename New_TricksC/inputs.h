#pragma once

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

enum ButtonFlags
{
    Jump = 0x00000001,
    FormationR = 0x00000002,
    Action = 0x00000004,
    FormationL = 0x00000008,

    DpadUp = 0x00000010,
    DpadDown = 0x00000020,
    DpadLeft = 0x00000040,
    DpadRight = 0x00000080,

    CameraR = 0x00000100,
    CameraL = 0x00000200,
    Start = 0x00004000,

    TeamBlast = 0x00030000
};

int IsButtonPressed(uint32_t buttonMask, int port);
void Init_InputHooks();

;

extern "C" {
    DLL_EXPORT void UpdateInputState(uint32_t buttonFlags, uint32_t oneFramePressFlags, int port);
}
