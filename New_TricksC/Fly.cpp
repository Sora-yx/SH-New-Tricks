#include "pch.h"
#include "Chocola.h"

namespace FlyChars
{

	void  TObjMilesExecMove_r(TObjPlayer* p);
	FastUsercallHook<void, TObjPlayer*> TObjMilesExecMove_h(0x5C3B30);

	intptr_t flyVSpdCapAddr = 0x789FA4;

	static const int flyVSpdCapNew[] = { 0x0, 0x0, 0x5C, 0x43 };
	static const int flyVSpdCapOrigin[] = { 0x0, 0x0, 0xB4, 0x42 };

	float GetFlyTimerIncr(TObjTeam* t)
	{
		switch (t->level[1]) //1 is flying formation
		{
		case 1:
			return 1.2f;
		case 2:
			return 1.0f;
		case 3:
			return 0.8f;
		}

		return 1.4f;
	}

	float GetFlyMaxSpd(TObjTeam* t)
	{
		switch (t->level[1]) //1 is flying formation
		{
		case 1:
			return 3.0f;
		case 2:
			return 4.0f;
		case 3:
			return 5.0f;
		}

		return 2.0f;
	}

	void UpdateVerticalSpeedCap()
	{
		for (uint8_t i = 0; i < LengthOfArray(flyVSpdCapNew); i++)
		{
			intptr_t addr = flyVSpdCapAddr + i;
			uint8_t value = (uint8_t)flyVSpdCapNew[i];
			WriteData<1>((void*)addr, value);
		}
	}

	void ResetVerticalSpeedCap()
	{
		for (uint8_t i = 0; i < LengthOfArray(flyVSpdCapOrigin); i++)
		{
			intptr_t addr = flyVSpdCapAddr + i;
			uint8_t value = (uint8_t)flyVSpdCapOrigin[i];
			WriteData<1>((void*)addr, value);
		}
	}

	void TObjMilesExecMove_r(TObjPlayer* p)
	{
		auto config = GetConfig();
		bool vSpeed = config.IncreaseSpeedCap;
		bool flightT = config.FlightTweaks;
		bool isCpu = isCPU(p);

		if (vSpeed && !isCpu)
		{
			UpdateVerticalSpeedCap();
		}

		switch (p->mode)
		{
		case PlayerMode::ModeFly:
			if (flightT && !isCpu)
			{
				if (PCheckPower(0, 0, p) != 0)
				{
					if (p->lightDashLastRingPos_HHC.z < 180.0f)
						p->lightDashLastRingPos_HHC.z += GetFlyTimerIncr(p->pTObjTeam);

					if (p->spd.x < GetFlyMaxSpd(p->pTObjTeam))
					{
						p->spd.x += 0.03f;
					}
				}
			}
			break;
		case 53: //tired
			if (flightT && !isCpu)
			{
				if (PCheckPower(0, 0, p) > 0 && p->spd.x < 1.0f)
				{
					p->spd.x += 1.0f; //goofy hacky way to interrupt kill momentum (for now).
				}
			}
			break;
		case 73: //cheese attack
			if (config.CheeseTweaks)
			{
				PGetAcceleration(p);
			}
			break;
		case 80:
		
			if (p->mwp.spd.x <= 0.0f)
			{
				p->mwp.spd.x = 0.0f;
				p->mwp.spd.z = 0.0f;
			}
				

			p->mwp.spd.x += 0.5f;
			p->mwp.spd.z += 0.5f;
			p->spd = p->mwp.spd;

			break;
		}

		TObjMilesExecMove_h.Original(p);

		if (vSpeed && !isCPU(p))
		{
			ResetVerticalSpeedCap();
		}
	}

	void Init()
	{
		auto config = GetConfig();
		TObjMilesExecMove_h.Hook(TObjMilesExecMove_r, noret, rEAX);

		if (config.FlightTweaks)
		{
			WriteNop(0x5C5743, 21);
			// Util.WriteNop(0x5C5741, 32);   //remove clear speed once fly is over
			WriteNop(0x5C571D, 0x6); //remove flight timer we will manually update it for convenience due to how it works originally.
		}

		if (config.CheeseTweaks)
		{
			WriteData<5>((int*)0x5C3C71, 0x90); //remove PGetBreak so Cream doesn't slow down when using Cheese

			auto anim = &cream_motions[90];

			if (anim->speed < 2.5f)
			{
				anim->speed = 2.5f;
			}
		}

		if (1)
		{
			//WriteData<5>((int*)0x5C6054, 0x90); //remove PClearSpeed so Charmy doesn't stop when using his dart attack
		}

		InitChocola();
	}


}