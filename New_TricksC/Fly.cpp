#include "pch.h"
#include "Chocola.h"

namespace FlyChars
{

	void  TObjMilesExecMove_r(TObjPlayer* p);
	FastUsercallHook<void, TObjPlayer*> TObjMilesExecMove_h(0x5C3B30);

	intptr_t flyVSpdCapAdd = 0x789FA4;

	static const int flyByteNew[] = { 0x0, 0xC0, 0x79, 0x44 };
	static const int flyByteOrigin[] = { 0x0, 0x0, 0x34, 0x43 };
	static const int flyVSpdCapNew[] = { 0x0, 0x0, 0x87, 0x43 };
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

	void TObjMilesExecMove_r(TObjPlayer* p)
	{
		bool vSpeed = true; /** ConfigV._modConfig.IncreaseSpeedCap;*/
		bool flightT = true;  /**ConfigV._modConfig.FlightTweaks;*/
		bool isCpu = isCPU(p);

		if (vSpeed && !isCpu)
		{
			WriteDataArray(flyVSpdCapAdd, (int*)flyVSpdCapNew, 4); 
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
						p->spd.x += 0.04f;
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
			if (1 /*ConfigV._modConfig.CheeseTweaks*/)
			{
				PGetAcceleration(p);
			}
			break;
		}

		TObjMilesExecMove_h.Original(p);

		if (vSpeed && !isCPU(p))
		{
			WriteDataArray(flyVSpdCapAdd, (int*)flyVSpdCapOrigin, 4);
		}
	}

	void Init()
	{

		TObjMilesExecMove_h.Hook(TObjMilesExecMove_r, noret, rEAX);

		if (1/**ConfigV._modConfig.FlightTweaks*/)
		{
			WriteNop(0x5C5743, 21);
			// Util.WriteNop(0x5C5741, 32);   //remove clear speed once fly is over
			WriteNop(0x5C571D, 0x6); //remove flight timer we will manually update it for convenience due to how it works originally.
		}

		if (1/**ConfigV._modConfig.CheeseTweaks*/)
		{
			WriteData<5>((int*)0x5C3C71, 0x90); //remove PGetBreak so Cream doesn't slow down when using Cheese

			auto anim = &cream_motions[90];

			if (anim->speed < 2.5f)
			{
				anim->speed = 2.5f;
			}
		}

		InitChocola();
	}


}