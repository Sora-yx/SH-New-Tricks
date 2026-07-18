
#include "pch.h"
#include "acts_api.h"

namespace Bounce
{
	short Act = 91;
	short ActRebound = 92;


	float getBounceSpd(TObjPlayer* p)
	{
		if (p->pTObjTeam != nullptr)
		{

			switch ((int)p->pTObjTeam->level[0])
			{
			case 1:
				return -5.3f;
			case 2:
				return -5.6f;
			case 3:
				return -5.9f;
			}
		}

		return -5.0f;
	}

	bool CheckInputPress(TObjPlayer* p)
	{
		if (isDPadUsedForFormSwap() == false || isExpandedActLoaded == false)
			return false;

		if (!p || (player_input[p->playerNo].change_leaderR.status & isPress) == 0)
		{
			return false;
		}

		p->mm.reqaction = 55;
		p->mode = Act;
		p->flag |= 0x1000;
		p->spd.y = getBounceSpd(p);
		return true;
	}



	float getReBounceSpd(TObjPlayer* p)
	{
		if (p->pTObjTeam != nullptr)
		{

			switch ((int)p->pTObjTeam->level[0])
			{
			case 1:
				return -7.3f;
			case 2:
				return -7.6f;
			case 3:
				return -7.9f;
			}
		}

		return -7.0f;
	}

	bool CheckInputPressRebounce(TObjPlayer* p)
	{
		if (isDPadUsedForFormSwap() == false || isExpandedActLoaded == false)
			return false;

		if (!p || (player_input[p->playerNo].change_leaderR.status & isPress) == 0)
		{
			return false;
		}

		p->mm.reqaction = 55;
		p->mode = Act;
		p->flag |= 0x1000;
		p->spd.y = getReBounceSpd(p);
		return true;
	}



	void RunPhysics(TObjPlayer* p)
	{

		if (p->spd.x > 4.0f) // heroes physics allow player to move super fast with bounce so we do a small hack to make it a bit slower
			p->spd.x -= 0.2f;

		PResetAngle(p);
		PGetAccelerationAir(p);
		PGetSpeed(p);
		PSetPosition(p);
		PResetPosition(p);


	}

	void RunChkMode(TObjPlayer* p)
	{

		if (ChkInputLight(p) > 0)
		{
			return;
		}



		if ((p->flag & 3) != 0)
		{
			p->mode = Bounce::ActRebound;
			p->ang.x = p->mwp.ang_aim.x;
			p->ang.z = p->mwp.ang_aim.z;
			p->spd.y = 3.60f;
			VibeShot(0, p->controllerNo, 7, 15);

			return;
		}

		if ((p->flag & 0x4000) != 0)
		{
			return;
		}


		if ((player_input[p->playerNo].jump.status & isPress) != 0)
		{
			p->mode = PlayerMode::ModeJumpDash;
			p->spd.x += 3.0f;
			p->mm.reqaction = 69;

			if (SndSE)
				IsndSEPlay(8292, &p->position, SndSE, 0, 0);

			SetEffectDash(p->playerNo);
			if (p->pTObjTeam->level[0] >= 3)
				SetEffectRocketJump(p->playerNo);
		}

	}

	void RunChkModeRebounce(TObjPlayer* p)
	{
		if (ChkInputLight(p) > 0)
		{
			return;
		}

		if ((p->flag & 3) != 0)
		{
			p->ang.x = p->mwp.ang_aim.x;
			p->ang.z = p->mwp.ang_aim.z;
			p->flag &= 0xFFFFAFFF;

			if (PCheckStop(p) == 0)
			{
				p->mm.reqaction = 1;
				p->mode = PlayerMode::ModeRunning;
			}
			else
			{
				p->mode = PlayerMode::ModeWait;
				p->idleTime = 0;
				p->mm.reqaction = 0;

			}

			return;
		}

		if ((p->flag & 0x4000) != 0 || CheckInputPressRebounce(p))
		{
			return;
		}


		if ((player_input[p->playerNo].jump.status & isPress) != 0)
		{
			p->mode = PlayerMode::ModeJumpDash;
			p->spd.x += 3.0f;
			p->mm.reqaction = 69;

			if (SndSE)
				IsndSEPlay(8292, &p->position, SndSE, 0, 0);

			SetEffectDash(p->playerNo);
			if (p->pTObjTeam->level[0] >= 3)
				SetEffectRocketJump(p->playerNo);
		}

	}

	void Init()
	{
		if (isDPadUsedForFormSwap() == false || isExpandedActLoaded == false)
			return;


		Act = ActExp_RegisterNewCharacterMode(charaType::speedType);

		if (Act < 85)
		{
			return;
		}

		ActRebound = ActExp_RegisterNewCharacterMode(charaType::speedType);

		if (ActRebound < 85)
		{
			return;
		}


	}

}
