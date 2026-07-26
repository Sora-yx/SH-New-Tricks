#include "pch.h"
#include "Amy.h"
#include "acts_api.h"

namespace HammerJump
{

	bool assetsLoaded = false;
	const uint8_t AmyNewAnimCount = 4;
	RtAnimAnimation* amyCustomAnim[AmyNewAnimCount];
	PL_MOTION amyCustomAnimList[AmyNewAnimCount];
	int AmyNewAnimIndex[AmyNewAnimCount];
	int AmyNewAnimFileIndex[AmyNewAnimCount];

	const char* animName[AmyNewAnimCount] =
	{
		"hammer_jmp",
		"flip1",
		"flip2",
		"flip3"
	};


	float getHammerJumpSpd(TObjPlayer* p)
	{
		if (p->pTObjTeam != nullptr)
		{

			switch ((int)p->pTObjTeam->level[0])
			{
			case 1:
				return 3.0f;
			case 2:
				return 3.3f;
			case 3:
				return 3.6f;
			}
		}

		return 2.7f;
	}

	short Act = 90;

	void RunPhysics(TObjPlayer* p)
	{
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

		if (p->mm.reqaction == HammerJump::AmyNewAnimIndex[HammerJump::anm_HammerJump])
		{

			if (p->mm.nframe >= 18.0f)
			{
				p->spd.y = p->p.jmp_y_spd * getHammerJumpSpd(p);
			}

			return;
		}

		auto pad = player_input[p->playerNo];

		if ((p->flag & 3) != 0)
		{
			if (PCheckStop(p) > 0)
			{
				p->mm.reqaction = 0;
				p->mode = 0;
			}
			else
			{
				p->mode = (short)PlayerMode::ModeRunning;
				p->mm.reqaction = (short)PlayerAnim::Motion_Run;
			}
		}
		else
		{
			if (Amy::CheckHammerFloatInput(p))
				return;
		}
	}

	void Init()
	{
		if (assetsLoaded)
			return;


		if (isDPadUsedForFormSwap() == false || isExpandedActLoaded == false)
			return;

		// we get the next anim ID for hammer jump, from here we know in advance what the flip anim use
		// since it will be loaded right after hammer jump.
		
		// set new anim index
		for (int i = 0; i < AmyNewAnimCount; i++) 
		{
			AmyNewAnimIndex[anm_HammerJump + i] = ActExp_GetNextAvailableAnimID(Char_Amy) + i;
			AmyNewAnimFileIndex[anm_HammerJump + i] = ActExp_GetNextAvailableAnimFileID() + i;
		}

		memcpy(&amyCustomAnimList[anm_HammerJump], &amy_motions[Animation_BackFlip], sizeof(PL_MOTION));

		amyCustomAnimList[anm_HammerJump].mtnmode = 4;
		amyCustomAnimList[anm_HammerJump].speed = 1.0f;
		amyCustomAnimList[anm_HammerJump].interpolate_delta = 0.50f;
		amyCustomAnimList[anm_HammerJump].next = AmyNewAnimIndex[anm_flip1];
		amyCustomAnimList[anm_HammerJump].thismotdat = AmyNewAnimFileIndex[anm_HammerJump];

		memcpy(&amyCustomAnimList[anm_flip1], &amy_motions[Animation_BackFlip], sizeof(PL_MOTION));
		memcpy(&amyCustomAnimList[anm_flip2], &amy_motions[Animation_BackFlip2], sizeof(PL_MOTION));
		memcpy(&amyCustomAnimList[anm_flip3], &amy_motions[Animation_SideFlip], sizeof(PL_MOTION));

		auto flip1 = &amyCustomAnimList[anm_flip1];
		flip1->next = AmyNewAnimIndex[anm_flip2];
		flip1->mtnmode = 4;
		flip1->speed = 0.5f;
		flip1->thismotdat = AmyNewAnimFileIndex[anm_flip1];


		auto flip2 = &amyCustomAnimList[anm_flip2];
		flip2->mtnmode = 4;
		flip2->next = (short)AmyNewAnimIndex[anm_flip3];
		flip2->speed = 0.5f;
		flip2->thismotdat = AmyNewAnimFileIndex[anm_flip2];


		auto flip3 = &amyCustomAnimList[anm_flip3];
		flip3->mtnmode = 4;
		flip3->next = (short)Animation_Falling;
		flip3->speed = 0.5f;
		flip3->thismotdat = AmyNewAnimFileIndex[anm_flip3];


		Act = ActExp_RegisterNewCharacterMode(charaType::speedType);

		if (Act < 85)
		{
			return;
		}

		auto oneFileMem = (ONEFILE*)RwEngineInstance->memoryFuncs.rwmalloc(sizeof(ONEFILE));
		bool animOneLoaded = false;
		ONEFILE* amyAnmOneFile = nullptr;
		if (oneFileMem)
		{
			amyAnmOneFile = OneFileCtor((char*)"playmodel/newAmyAnims.one", oneFileMem, 1);
			if (amyAnmOneFile && amyAnmOneFile->memInfo.length > 0)
			{
				animOneLoaded = true;
			}
		}

		if (animOneLoaded == false)
		{
			if (oneFileMem)
				ReleaseOneFile(oneFileMem);

			return;
		}
		

		void* BufferData = RwEngineInstance->memoryFuncs.rwmalloc(0x19000);
		auto indexOneFile = ONEFILECheckFileID(amyAnmOneFile, (char*)"AM_HAMMER_JUMP.ANM");


		if (indexOneFile > 0)
		{

			for (int i = 0; i < AmyNewAnimCount; i++)
			{
				amyCustomAnim[i] = OneFileLoadHAnimation(indexOneFile + i, (void*)BufferData, oneFileMem);

				if (!amyCustomAnim[i])
					break;

				uint32_t anmListIndex = 0;
				uint32_t anmFileIndex = 0;
				auto resNewANim = ActExp_RegisterNewAnimation(Char_Amy, animName[i], &amyCustomAnimList[i], amyCustomAnim[i], &anmListIndex, &anmFileIndex);

				if (resNewANim < 0 || anmListIndex < 103)
					break;
			}
		}


		if (BufferData)
			RwEngineInstance->memoryFuncs.rwfree((void*)BufferData);

		ReleaseOneFile(oneFileMem);

		assetsLoaded = true;
	}
}