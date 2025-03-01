#include "pch.h"

namespace PowerChars
{
	enum
	{
		BellyAttackMode = 78,
		BellyHitGround
	};

	FastStdcallHook<void, TObjPlayer*> TObjKnuxChkMode_h(0x5BA2F0);
	FastStdcallHook<void, TObjPlayer*> TObjKnuxExecMode_h(0x5B9BE0);

	//unused for now as I got feedback that it wasn't great
	float GetTriangleDiveMaxSpd(TObjTeam* t)
	{
		switch (t->level[2])
		{
		case 1:
			return 2.6f;
		case 2:
			return 2.8f;
		case 3:
			return 3.0f;
		}

		return 2.5f;
	}

	float GetBellyBounceMaxSpd(TObjTeam* t)
	{
		switch (t->level[2])
		{
		case 1:
			return 2.0f;
		case 2:
			return 3.5f;
		case 3:
			return 5.0f;
		}

		return 1.0f;
	}

	void __stdcall TObjKnuxChkMode_r(TObjPlayer* p)
	{
		if (!ChkInputLight(p))
		{
			switch (p->mode)
			{
			case BellyAttackMode:

				if (p->characterKind == Char_Vector && p->mm.action == 100 || p->characterKind == Char_Big && p->mm.action == 100)
				{
					p->mode = BellyHitGround;
					p->spd.y = -8.0f - GetBellyBounceMaxSpd(p->pTObjTeam);
					p->spd.z = 0.0f;

					p->lightDashRingCount_HHC = 0;
				}
				else if (p->mm.action != 99)
				{
					p->mm.reqaction = 99;
				}

				return;
			case BellyHitGround:
				if (p->mm.action == 101 && (p->mm.flag & 3) != 0)
				{
					p->mode = 2;
					p->flag = p->flag & 0xFFFFDEFD | 0x400;
					p->spd.y = 3.7f + GetBellyBounceMaxSpd(p->pTObjTeam);
					p->spd.z = 0.0f;
					p->jumpBallTime = p->p.jump2_timer;
					return;
				}
				break;

			}
		}

		TObjKnuxChkMode_h.Original(p);
	}

	void __stdcall TObjKnuxExecMode_r(TObjPlayer* p)
	{

		switch (p->mode)
		{
		case 58:
			PGetAcceleration(p);
			break;
		case BellyAttackMode:
			PGetAccelerationAir(p);
			PGetSpeed(p);
			break;
		}

		TObjKnuxExecMode_h.Original(p);
	}

	void Init()
	{
		auto config = GetConfig();
		TObjKnuxExecMode_h.Hook(TObjKnuxExecMode_r);
		TObjKnuxChkMode_h.Hook(TObjKnuxChkMode_r);

		if (config.WidePowerTweaks)
		{
			WriteNop(0x5B9FE5, 5); //nope PGetBreak so characters don't slow down
		}

		if (config.TriangleDiveTweaks)
			WriteNop(0x5AECFC, 0x2); //remove anim fan check so Triangle Dive can be used when falling.

		if (1)
		{

		}
	}
}