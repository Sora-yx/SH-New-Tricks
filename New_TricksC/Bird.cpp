#include "pch.h"

MHook<TObjPlayer*, TObjTeam*, unsigned int, char> SetAmyRose_Team_t(0x5CB7D0);

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
	void(*destructor)();
	void(*exec)();
	void(*disp)();
	void(*Tdisp)();
	void(*Pdisp)();
	void(*null0)();
	void(*null1)();
	void(*null2)();
	void(*null3)();
	void(*null4)();
};



void BirdDestructor()
{

}


void BirdDisp()
{
	if (TObjBirdPclump[0])
		RPClumpRender(TObjBirdPclump[0]);
}

void BirdTDisp()
{
}

void BirdPDisp()
{
}

int __cdecl AdjustAngle(__int16 bams_a, unsigned __int16 bams_b, int limit)
{
	int result; // eax
	__int16 v4; // cx

	result = bams_b;
	v4 = bams_b - bams_a;
	if ((bams_b - bams_a) > limit || v4 < -limit)
	{
		if (v4 >= 0)
		{
			result = (limit + bams_a);
		}
		else
		{
			result = (bams_a - limit);
		}
	}
	return result;
}

void BirdExec()
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
	TObjectCreate(&birdPtr->obj, TL_03);

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

	auto oneFileMem = (ONEFILE*)RwEngineInstance->memoryFuncs.rwmalloc(92);

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
	}

	if (BirdTexDictionary)
		RwTexDictionarySetCurrent(BirdTexDictionary);

	//load model
	TObjBirdPclump[0] = OneFileLoadClump(2, BufferData, oneFileMem); //model
	//TObjChocolaPclump[1] = OneFileLoadClump(4, BufferData, oneFileMem); //ball


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
	auto res = SetAmyRose_Team_t.originalFunc(a2, a3, a5);
	LoadAmyBird();
	return res;

}

void initBird()
{
	SetAmyRose_Team_t.Hook(SetAmyRose_Team_r);
}