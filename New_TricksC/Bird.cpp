#include "pch.h"

FastFunctionHook<TObjPlayer*, TObjTeam*, unsigned int, char> SetAmyRose_Team_t(0x5CB7D0);

struct TObjBird
{
	TObject obj;
	OBJ_MoveOnGround objMove;
	signed __int8 playerno = -1;
	signed __int8 animno;
	signed __int16 mode = 0;
	RwV3d pos_Target;
	RwV3d pos;
	sAngle ang;
	float spd;
	float dist_Target;
	float nframe;
	RwV3d pos_shadow;
	sRealAngle3 ang_shadow;
};

TObjBird* birdPtr = nullptr;
RpHAnimHierarchy* pHAH_Bird = nullptr;
RtAnimAnimation* pHAA_List_Bird[7] = { nullptr };
RpClump* TObjBirdPclump[2] = { nullptr };
RwTexDictionary* BirdTexDictionary = nullptr;

struct vftableBird {
	void(__fastcall* destructor)(TObjBird* ptr, char unused, char signal);
	void(__fastcall* exec)(TObjBird* ptr, char unused_edx);
	void(__fastcall* disp)(TObjBird* ptr, char unused);
	void(__fastcall* tdisp)(TObjBird* ptr, char unused);
	void(__fastcall* pdisp)(TObjBird* ptr, char unused);
	void(__fastcall* null2)(TObjBird* ptr, char unused);
	void(__fastcall* null3)(TObjBird* ptr, char unused);
	void(__fastcall* null4)(TObjBird* ptr, char unused);
	void(__fastcall* null5)(TObjBird* ptr, char unused);
	void(__fastcall* null6)(TObjBird* ptr, char unused);
};


static void __fastcall nullsub(TObjBird* ptr, char unused)
{

}


void __fastcall BirdDestructor(TObjBird* ptr, char unused, char signal)
{
	printf("Deleted Birbo\n");
	for (uint16_t i = 0; i < LengthOfArray(pHAA_List_Bird); i++)
	{
		RtAnimAnimation* animList = pHAA_List_Bird[i];
		if (animList)
		{
			RtAnimAnimationDestroy(animList);
			animList = 0;
		}

	}

	for (uint16_t i = 0; i < LengthOfArray(TObjBirdPclump); i++)
	{
		RpClump* clump = TObjBirdPclump[i];
		if (clump)
		{
			RpClumpDestroy(clump);
			clump = 0;
		}
	}

	pHAH_Bird = 0;

	RwTexDictionaryDestroy(BirdTexDictionary);
	BirdTexDictionary = 0;
	TObjectDestructor(&ptr->obj);
	if ((signal & 1) != 0)
		THeapCtrlFree(ptr, TaskHeap);
}

void __fastcall BirdDisp(TObjBird* ptr, char unused)
{
	if (!birdPtr)
		return;

	auto p = playerTop[birdPtr->playerno];
	if (p)
	{
		if (p->mode == 999 || p->charMode == CHAR_MODE_Inactive)
			return;
	}

	if (TObjBirdPclump[0])
		RPClumpRender(TObjBirdPclump[0]);
}

void __fastcall BirdTDisp(TObjBird* ptr, char unused)
{
}

void __fastcall BirdPDisp(TObjBird* ptr, char unused)
{
}


void __fastcall BirdExec(TObjBird* ptr, char unused_edx)
{
	if (pHAH_Bird)
	{
		birdPtr->nframe += 0.5f;
		float timea = birdPtr->nframe * 0.016f;
		RtAnimInterpolatorSetCurrentTime(pHAH_Bird->currentAnim, timea);
		RpHAnimHierarchyUpdateMatrices(pHAH_Bird);
	}
	
	auto bird = birdPtr;

	if (bird->playerno == -1)
	{
		for (uint8_t i = 0; i < 8; i++)
		{
			auto p = playerTop[i];

			if (p && p->characterKind == Char_Amy)
			{
				bird->playerno = i;
				auto v5 = GetTeamCharacterIdFromCCLCharacterId(playerTop[(char)i]->C_COLLI_.character_id);
				RpClumpForAllAtomics(
					TObjBirdPclump[0],
					(RpAtomicCallBack)plCallbackRpAtomicToSetRenderCallbackToUseLight,
					(void*)i);

				break;
			}

			if (i >= PMax)
				return;
		}
	}

	auto p = playerTop[bird->playerno];
	bird->ang.y = AdjustAngle(bird->ang.y, 0xC000 + p->ang.y, 1024);
	bird->ang.x += 16;
	bird->ang.z += 1024;

	RwV3d dest;
	dest.x = njCos(bird->ang.x) * 3.0f + p->position.x;
	dest.y = njSin(bird->ang.z) + 12.0f + p->position.y;
	dest.z = njSin(bird->ang.x) * 3.0f + p->position.z;

	bird->dist_Target = sqrtf(powf(dest.x - bird->pos.x, 2) + powf(dest.y - bird->pos.y, 2) + powf(dest.z - bird->pos.z, 2));

	if (bird->dist_Target >= 200.0f)
	{
		bird->pos = dest;
	}
	else
	{
		bird->pos.x += (dest.x - bird->pos.x) * 0.25f;
		bird->pos.y += (dest.y - bird->pos.y) * 0.25f;
		bird->pos.z += (dest.z - bird->pos.z) * 0.25f;
	}

	if (TObjBirdPclump[0])
	{
		float Cos = 1.0f - (sine[-(bird->ang.y) & 0xffff]);
		float Sin = (sine[-(bird->ang.y) - 0x4000u & 0xffff]);
		auto frameMdl = (RwFrame*)TObjBirdPclump[0]->object.parent;
		RwMatrixRotateOneMinusCosineSine(&frameMdl->modelling, &AxisY, Cos, Sin, rwCOMBINEREPLACE);
		RwFrameTranslate(frameMdl, &bird->pos, rwCOMBINEPOSTCONCAT);
	}

}

static vftableBird vfTablebird = { BirdDestructor, BirdExec, BirdDisp, BirdTDisp, BirdPDisp, nullsub, nullsub, nullsub, nullsub, nullsub };


void LoadAmyBird()
{
	PrintMessage("Init Amy Bird Task..\n");
	birdPtr = (TObjBird*)THeapCtrlMalloc(sizeof(TObjBird) + 8, TaskHeap);
	tobject::tobject(&birdPtr->obj, TL_03);

	ObjMoveOnGroundFv(&birdPtr->objMove);
	birdPtr->obj.ClassName = (char*)"TObjBird";
	birdPtr->obj.__vftable = &vfTablebird;
	birdPtr->playerno = -1;

	for (uint8_t i = 0; i < PMax; i++)
	{
		auto P = playerTop[i];
		if (P)
		{
			if (P->characterKind == Char_Amy)
			{
				PrintMessage("Found Amy, execution of the task will continue\n");
				break;
			}
		}
	}

	auto oneFileMem = (ONEFILE*)RwEngineInstance->memoryFuncs.rwmalloc(sizeof(ONEFILE));

	if (oneFileMem)
	{
		if (OneFileCtor((char*)"playmodel/bird.one", oneFileMem, 1))
		{
			PrintMessage("Successfully Loaded One File Bird.\n");
		}
	}

	void* BufferData = RwEngineInstance->memoryFuncs.rwmalloc(0x19000);
	if (!BirdTexDictionary) //skip if already loaded
	{
		//3 is texID
		BirdTexDictionary = OneFileLoadTextureDictionary(3, BufferData, oneFileMem);
		BirdTexDictionary = BirdTexDictionary;
	}

	if (BirdTexDictionary)
		RwTexDictionarySetCurrent(BirdTexDictionary);

	//load model
	TObjBirdPclump[0] = OneFileLoadClump(2, BufferData, oneFileMem); //model


	uint8_t indexOneFile = 4; 
	pHAA_List_Bird[0] = OneFileLoadHAnimation(indexOneFile, (void*)BufferData, oneFileMem);


	if (BufferData)
		RwEngineInstance->memoryFuncs.rwfree((void*)BufferData);

	ReleaseOneFile(oneFileMem);
	RwEngineInstance->memoryFuncs.rwfree(oneFileMem);

	if (TObjBirdPclump[0] && pHAA_List_Bird[0])
	{
		if (!pHAH_Bird)
		{
			auto v28 = &TObjBirdPclump[0]->object.parent;
			auto anim = RpHAnimFrameGetHierarchy((RwFrame*)TObjBirdPclump[0]->object.parent);
			if (!anim)
			{
				RwFrameForAllChildren((RwFrame*)*v28, GetChildFrameHierarchy, &anim);
			}

			pHAH_Bird = anim;
		}

		if (pHAH_Bird)
		{
			RpClumpForAllAtomics(TObjBirdPclump[0], SetHierarchyForSkinAtomic, pHAH_Bird);
			RtAnimInterpolatorSetCurrentAnim(&pHAH_Bird->currentAnim->pCurrentAnim, &pHAA_List_Bird[0]->interpInfo);
			RpHAnimHierarchyAttach(pHAH_Bird);
			RpHAnimHierarchyUpdateMatrices(pHAH_Bird);
			RtAnimInterpolatorSetCurrentTime(pHAH_Bird->currentAnim, 0.0f);
			RtAnimInterpolatorAddAnimTime(pHAH_Bird->currentAnim, 0.0f);
		}
	}
}

TObjPlayer* __cdecl SetAmyRose_Team_r(TObjTeam* a2, unsigned int a3, char a5)
{
	auto res = SetAmyRose_Team_t.Original(a2, a3, a5);
	LoadAmyBird();
	return NULL;
}


void initBird()
{
	SetAmyRose_Team_t.Hook(SetAmyRose_Team_r);
}