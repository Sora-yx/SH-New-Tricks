#include "pch.h"
#include "Amy.h"

namespace Amy
{
	enum
	{
		Animation_Trick = 62,
	};

	enum
	{
		HammerFloat = 77
	};

	bool usedHover = false;

	uint8_t bytesHoverDuration[4] = { 0xF0, 0x0, 0x0, 0x0 };
	intptr_t hoverTimeAddr = 0x5D139E;

	int HoldHammerAnims[] = {  PlayerAnim::Animation_JumpRoll, PlayerAnim::Animation_JumpDash, PlayerAnim::Animation_BackFlip, PlayerAnim::Animation_BackFlip2, PlayerAnim::Animation_SideFlip, 51 };

	FastFastcallHook<void, TObjPlayer*> TriggerAmyHammer_h(0x5CCDD0);

	short GetHammerAnims(PlayerAnim mtn)
	{
		for (size_t i = 0; i < LengthOfArray(HoldHammerAnims); i++)
		{

			if (HoldHammerAnims[i] == mtn)
			{
				return (short)HoldHammerAnims[i];
			}
		}

		return -1;
	}

	float GetPropSpd(TObjTeam* t)
	{
		switch (t->level[0]) //0 is spd formation
		{
		case 1:
			return 0.1f;
		case 2:
			return 0.2f;
		case 3:
			return 0.3f;
		}

		return 0.05f;
	}

	float GetPropMaxSpd(TObjTeam* t)
	{
		switch (t->level[0]) //0 is spd formation
		{
		case 1:
			return 5.0f;
		case 2:
			return 6.0f;
		case 3:
			return 7.0f;
		}

		return 4.0f;
	}

	void GetPropTimer(TObjTeam* t)
	{
		//240 frames (level 0)
		bytesHoverDuration[0] = 0xF0;
		bytesHoverDuration[1] = 0x0;
		bytesHoverDuration[2] = 0x0;
		bytesHoverDuration[3] = 0x0;

		switch (t->level[0]) //0 is spd formation
		{
		case 1:
			bytesHoverDuration[0] = 0x2C; //swap to 300 frames
			bytesHoverDuration[1] = 0x1;
			bytesHoverDuration[2] = 0x0;
			bytesHoverDuration[3] = 0x0;
			break;
		case 2:
			bytesHoverDuration[0] = 0x68; //swap to 360 frames
			bytesHoverDuration[1] = 0x1;
			bytesHoverDuration[2] = 0x0;
			bytesHoverDuration[3] = 0x0;
			break;
		case 3:
			bytesHoverDuration[0] = 0xA4; //swap to 420 frames
			bytesHoverDuration[1] = 0x01;
			bytesHoverDuration[2] = 0x0;
			bytesHoverDuration[3] = 0x0;
			break;
		}
	}


	bool CheckHammerFloatInput(TObjPlayer* p)
	{
		if (usedHover)
			return false;

		if (player_input[p->teamNo_HHC].jump.status & isOn)
		{
			if (p->mm.reqaction != Animation_Trick && p->spd.y <= 0.0f)
			{
				p->mode = (short)HammerFloat; // start hammer float check
				p->mm.reqaction = Animation_HammerFloat;
				//p->flag &= 0xFFFFAF;
				p->spd.y = 0.0f;
				p->lightDashCountSinceLastRing_HHC = 0;
				p->grindTimer = 0;
				return true;
			}
		}

		return false;
	}

	void UpdateHoverMaxTimer(TObjTeam* t)
	{

		GetPropTimer(t);
		for (size_t i = 0; i < 4; i++)
		{
			intptr_t addr = hoverTimeAddr + i;
			uint8_t value = (uint8_t)bytesHoverDuration[i];
			WriteData<1>((void*)addr, value);
		}
	}

	int prevAction = -1;
	bool RunAmyChkMode(TObjPlayer* p)
	{

		if (p->characterKind != Char_Amy)
			return false;

		if (prevAction != p->mode) //prevent to spam amy hover infinitely 
		{
			if (p->mode == ModeHammerFloat)
			{
				if (usedHover)
				{
					p->mode = ModeFall;
					p->mm.reqaction = Animation_Falling;
				}
				else
				{
					usedHover = true;
				}
			}
			prevAction = p->mode;
		}

		if ((p->flag & 3) != 0)
		{
			usedHover = false;
		}

		auto t = p->pTObjTeam;

		auto config = GetConfig();
		switch (p->mode)
		{

		case (short)ModeRunning:


			if (p->spd.x > 4.0f && (player_input[p->teamNo_HHC].change_leader.status & isPress) != 0)
			{
				p->mode = HammerJump::Act;
				p->mm.reqaction = HammerJump::Mtn;
			}
			break;
		case (short)ModeHammerFloat:
			if (config.BetterProp)
			{
				usedHover = true;

				if (ChkInputLight(p))
					break;
			
				UpdateHoverMaxTimer(t);
	

				if (p->spd.x < GetPropMaxSpd(t) && PCheckPower(0, 0, p) != 0)
					p->spd.x += GetPropSpd(t);
			}
			break;
		case PlayerMode::ModeFall:
			if (config.BetterProp)
			{
				if (ChkInputLight(p))
					break;

				CheckHammerFloatInput(p);
			}
			break;
		default:
			if (p->mode == HammerJump::Act)
			{
				HammerJump::RunChkMode(p);
			}
			//
			break;
		}

		return false;
	}

	void RunAmyExecMode(TObjPlayer* p)
	{
		if (!p || p->characterKind != Char_Amy)
			return;

	
		switch (p->mode)
		{
		case (short)ModeAmy_Tornado:
			if (1 /**ConfigV._modConfig.AmyTornadoTweaks*/)
			{
				if (p->spd.y <= 0.0f)
					p->spd.y = 0.0f;

				PGetAccelerationAir(p);
				PGetSpeed(p);
			}
			break;

		case ModeHammerFloat:

			break;

		default:
			if (p->mode == HammerJump::Act)
			{
				HammerJump::RunPhysics(p);
			}
			
			break;
		}

	}

	//hacky way to make Amy's hammer show up on different action because I'm too lazy to rewrite the function
	void __fastcall TriggerAmyHammerHook(TObjPlayer* p)
	{
		char mode = (char)p->mode;
		bool triggered = false;


		if (p->mode < INT8_MAX && (mode == (char)ModeJumping || mode == ModeJumpDash || mode == HammerJump::Act || mode == ModeRunning && p->spd.x > 4.0f))
		{
			USHORT mtn = (USHORT)p->mm.reqaction;
			short hamMtn = GetHammerAnims((PlayerAnim)p->mm.reqaction);

			if (hamMtn > -1 && mtn == hamMtn || mode == ModeRunning && p->spd.x > 4.0f)
			{
				triggered = true;
				WriteData<1>((void*)0x5CCDEA, (uint8_t)mode); //change the action check 
			}
		}

		TriggerAmyHammer_h.Original(p);

		if (triggered)
			WriteData<1>((int*)0x5CCDEA, 0x48); //restore original action check
	}

	void Init()
	{

		HammerJump::Init();
		TriggerAmyHammer_h.Hook(TriggerAmyHammerHook);
		initBird();

		ConfigData config = GetConfig();

		if (config.BetterProp)
		{
			//prop
			WriteNop(0x5CEFC1, 2); //remove anim check for prop
		}

		if (config.AmyTornadoTweaks)
		{
			WriteData<5>((int*)0x5D13CF, 0x90); //remove clear speed
			WriteData<5>((int*)0x5D114F, 0x90); //remove clear speed for Hammer mov
			WriteData<1>((int*)0x5D1101, 0x3C); //reduce delay to start tornado move
			WriteData<1>((int*)0x5D1160, 0x19); //reduce delay to finish tornado move
		}
	}

}