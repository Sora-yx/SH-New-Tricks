#pragma once


#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

#pragma pack(push, 1) // Ensure 1-byte packing
typedef struct ConfigData 
{
    bool UseDPadForFormSwap;
    bool SonkSpinDash;
    bool ShadowSpinDash;
    bool AmySpinDash;
    bool BetterProp;
    bool AmyTornadoTweaks;
    bool AmyBird;
    bool EspioSpinDash;
    bool EspioTornadoTweaks;
    bool FlightTweaks;
    bool IncreaseSpeedCap;
    bool CheeseTweaks;
    bool EnableChocola;
    bool WidePowerTweaks;
    bool TriangleDiveTweaks;

}ConfigData;
#pragma pack(pop)

bool isSpinDashEnabledForAtLeastOneCharacter();
bool isSpinDashAllowed(Character chara);
bool isDPadUsedForFormSwap();

extern "C" {
    DLL_EXPORT void SetConfigData(ConfigData data);
    DLL_EXPORT ConfigData GetConfig();
}

