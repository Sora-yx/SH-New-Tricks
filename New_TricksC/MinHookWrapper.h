#pragma once
#include "MinHook.h"

template <typename T>
inline MH_STATUS MH_CreateHookEx(LPVOID pTarget, LPVOID pDetour, T** ppOriginal)
{
	return MH_CreateHook(pTarget, pDetour, reinterpret_cast<LPVOID*>(ppOriginal));
}

template <typename T>
MH_STATUS MH_CreateHookEx_r(intptr_t pTarget, LPVOID pDetour, T** ppOriginal)
{
	void* targetFunction = reinterpret_cast<void*>(pTarget);

	if (MH_CreateHookEx(targetFunction, pDetour, reinterpret_cast<LPVOID*>(ppOriginal)) == MH_OK)
	{
		return MH_EnableHook(targetFunction);
	}

	return MH_UNKNOWN;
}

template <typename RetType, typename ThisType, typename... Args>
class ThiscallMHook {
public:
    using FnType = RetType(__fastcall*)(ThisType* this_ptr, void* unused_ecx, Args...);

    intptr_t address;
    FnType originalFunc;

    ThiscallMHook(intptr_t addr) : address(addr), originalFunc(nullptr) {}

    void Hook(FnType detour) {
        MH_CreateHookEx_r(address, detour, &originalFunc);
    }

    RetType CallOriginal(ThisType* this_ptr, Args... args) {
        // Call the original function while passing this pointer as first argument and skipping unused ECX
        return originalFunc(this_ptr, nullptr, args...);
    }
};


template <typename RetType, typename... Args>
class FastcallMHook {
public:
    using FnType = RetType(__fastcall*)(Args...);

    intptr_t address;
    FnType originalFunc;

    FastcallMHook(intptr_t addr) : address(addr), originalFunc(nullptr) {}

    void Hook(FnType detour) {
        MH_CreateHookEx_r(address, detour, &originalFunc);
    }

    RetType CallOriginal(Args... args) {
        return originalFunc(args...);
    }
};

template <typename RetType, typename... Args>
class StdcallMHook {
public:
    using FnType = RetType(__stdcall*)(Args...);

    intptr_t address;
    FnType originalFunc;

    StdcallMHook(intptr_t addr) : address(addr), originalFunc(nullptr) {}

    void Hook(FnType detour) {
        MH_CreateHookEx_r(address, detour, &originalFunc);
    }

    RetType CallOriginal(Args... args) {
        return originalFunc(args...);
    }
};


template <typename RetType, typename... Args>
class MHook {
public:
    using FnType = RetType(__cdecl*)(Args...);

    intptr_t address;
    FnType originalFunc;

    MHook(intptr_t addr) : address(addr), originalFunc(nullptr) {}

    void Hook(FnType detour) {
        MH_CreateHookEx_r(address, detour, &originalFunc);
    }

    RetType CallOriginal(Args... args) {
        return originalFunc(args...);
    }
};