#include "pch.h"
#include "config.h"

static ConfigData config{ false };

void SetConfigData(ConfigData data) 
{
	config = data; 
}

ConfigData GetConfig() 
{
	return config; 
}

bool isSpinDashEnabledForAtLeastOneCharacter()
{
	ConfigData config = GetConfig();

	return config.AmySpinDash || config.SonkSpinDash || config.ShadowSpinDash || config.EspioSpinDash;
}

bool isDPadUsedForFormSwap()
{
	return config.UseDPadForFormSwap;
}

bool isSpinDashAllowed(Character chara)
{
	switch (chara)
	{
	case Char_Sonic:
		return config.SonkSpinDash;
	case Char_Shadow:
		return config.ShadowSpinDash;
	case Char_Amy:
		return config.AmySpinDash;
	case Char_Espio:
		return config.EspioSpinDash;
	}

	return false;
}