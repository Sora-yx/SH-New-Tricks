#include "pch.h"
#include "speed.h"

namespace SpeedChars
{
	FastStdcallHook<void, TObjPlayer*> TObjSonicExecMode_h(0x5CD670);
	FastStdcallHook<void, TObjPlayer*> TOBJSonicChkMode_h(0x5CE550);
	FastStdcallHook<signed int, TObjPlayer*> TObjSonicChkInput_h(0x5D35F0);
	FastFastcallHook<void, TObjPlayer*> TObjPModeChgReadyToRocketAccel_h(0x5A6E10);


	signed int __stdcall TobjSonkChkInput_r(TObjPlayer* p)
	{

		if ((p->flag & PL_FLAG_INPUT) == 0)
			return 0;

		int smode = p->smode - 2;

		bool isSpinDashAllowed = true; /** ConfigV.isSpinDashAllowed(p->characterKind);*/


		switch (smode)
		{
		case 14:
			if (isSpinDashAllowed)
			{
				p->flag &= ~0x100000;
				if (p->mode == SpinDash::ActRelease)
				{
					p->flag &= 0xFFFFDFFF;
					p->mode = PlayerMode::ModeRunning;
					//p->mm.reqaction = 19;
					PChangeRunningMotion(p);
				}
				else
				{
					SpinDash::SetDefaultChargeSpd(p);
					p->mm.reqaction = 10;
					p->mode = 1;
					p->flag |= 0x500;
					*(short*)p->gap988 = 60;

					if (SndSE)
						IsndSEPlay(8293, &p->position, SndSE, 0, 0);

				}
				return 1;
			}
			break;
		case 45:
			if (1/**ConfigV._modConfig.AmyTornadoTweaks*/)
			{
				if (p->characterKind == Char_Amy)
				{
					p->flag &= ~0x100000;
					p->mode = (short)PlayerMode::ModeAmy_Tornado;
					p->mm.reqaction = 100;
					p->flag &= 0xFFFFAFFF;
					return 1;
				}
			}
			break;
		case 50: //remove legacy dash with spin dash
			if (p->characterKind == Char_Amy && isSpinDashAllowed)
			{
				p->flag &= ~0x100000;
				return 0;
			}
			break;
		case 55:
			if (p->characterKind == Char_Espio && isSpinDashAllowed)
			{
				p->flag &= ~0x100000;

				if (p->field_395 > 0)
					break;

				return 0;
			}
			break;
		case 57: //see above
			if ((p->characterKind == Char_Sonic || p->characterKind == Char_Shadow) && isSpinDashAllowed)
			{
				p->flag &= ~0x100000;
				return 0;
			}
			break;
		}

		return TObjSonicChkInput_h.Original(p);
	}


	bool ChkModeSpdChars(TObjPlayer* p)
	{
		bool isSpinDash = true; /**ConfigV.isSpinDashAllowed(p->characterKind);*/

		switch ((PlayerMode)p->mode)
		{
		case PlayerMode::ModeRocketAccelCharge:
			if (isSpinDash)
			{
				return SpinDash::Charge(p);
			}
			break;
		case PlayerMode::ModeRocketAccelRelease:
		{
			if (isSpinDash)
			{
				return SpinDash::Release_(p);
			}
		}
		break;
		}

		return false;
	}

	//for actions >= 54 (see common.cpp for more info)
	bool ExecModeSpdChars(TObjPlayer* p)
	{
		auto charID = p->characterKind;
		bool isSpinDash = true; /** ConfigV.isSpinDashAllowed(charID)*/;

		switch (p->mode)
		{
		case SpinDash::ActRelease:
			if (isSpinDash)
			{
				SpinDash::RunReleasePhysics(p);
				return true;
			}
			break;
		case 71:
			if (isSpinDash && charID == Char_Espio && 1 /**ConfigV._modConfig.EspioTornadoTweaks*/)
			{
				PGetAccelerationAir(p);
				PGetSpeed(p);
			}
			break;
		}

		return false;
	}

	int prevAction = -1;
	//run actions (mode) >= 54
	void __stdcall TObjSonicExecMode_r(TObjPlayer* p)
	{
		
		//Console.WriteLine("Cur Mode " + p->mode);
		if (ExecModeSpdChars(p) /**|| Amy.RunAmyExecMode(p)*/)
			return;


		TObjSonicExecMode_h.Original(p);

		prevAction = p->mode;
	}

	void __stdcall TObjSonicChkMode_r(TObjPlayer* p)
	{

		if ((ChkModeSpdChars(p) /** || Amy.RunAmyChkMode(p)*/))
			return;


		TOBJSonicChkMode_h.Original(p);
	}


	void __fastcall TObjPModeChgReadyToRocketAccelHook(TObjPlayer* p)
	{
		TObjTeam* team = p->pTObjTeam;

		Character player = (Character)team->playerPtr[team->leaderPlayerNo]->characterKind;
		if (1 /**ConfigV.isSpinDashAllowed(player)*/)
		{
			return;
		}

		TObjPModeChgReadyToRocketAccel_h.Original(p);
	}

	void Init()
	{
		TObjSonicExecMode_h.Hook(TObjSonicExecMode_r);
		TOBJSonicChkMode_h.Hook(TObjSonicChkMode_r);
		TObjSonicChkInput_h.Hook(TobjSonkChkInput_r);


		if (1/**ConfigV._modConfig.EspioTornadoTweaks*/)
		{
			WriteNop(0x5D0F3A, 0x5);     //remove Clear Speed

		}

		if (1 /**ConfigV.isSpinDashEnabledForAtLeastAPlayer()*/)
		{
			TObjPModeChgReadyToRocketAccel_h.Hook(TObjPModeChgReadyToRocketAccelHook);
			SpinDash::Init();
			WriteData<6>((int*)0x5A70AC, 0x90);
		}
	}
}