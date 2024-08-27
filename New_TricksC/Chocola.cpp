#include "pch.h"


struct TObjChocola
{
	TObject obj;
	C_COLLI ccl;
	OBJ_MoveOnGround objMove;
	signed __int8 playerno = -1;
	signed __int8 animno;
	signed __int8 disp_event;
	signed __int16 mode = 0;
	signed __int16 timer_Attack;
	RwV3d pos_Target;
	RwV3d pos;
	sAngle ang;
	float spd;
	float dist_Target;
	float nframe;
	RwV3d pos_shadow;
	sRealAngle3 ang_shadow;
	PL_NODE_PARAMETER head;
	PARTICLE_TASK* pPtcl_SFA[8];
};

TObjChocola* chocolaPtr = nullptr;
RpHAnimHierarchy* pHAH_Chocola = nullptr;
RtAnimAnimation* pHAA_List_Chocola[7] = { nullptr };
RpClump* TObjChocolaPclump[2] = { nullptr };
RwTexDictionary* ChocolaTexDictionary = nullptr;

void TObjChocolaSetAnimation(int result, TObjChocola* a2)
{
	const int8_t animNo = a2->animno;

	if (animNo != result)
	{
		if (pHAA_List_Chocola[animNo])
		{
			a2->animno = result;
			RtAnimInterpolatorSetCurrentAnim(pHAH_Chocola->currentAnim, pHAA_List_Chocola[(char)result]);
			RtAnimInterpolatorSetCurrentTime(pHAH_Chocola->currentAnim, 0.0f);
			a2->nframe = 0.0f;
		}
	}
}

void TObjChocolaGetTargetPositionToChaseHer(TObjChocola* chocola)
{
	auto v1 = chocola->playerno;
	if (v1 != -1)
	{
		auto Cream = playerTop[v1];
		if (Cream)
		{
			chocola->pos_Target = Cream->position;
			chocola->pos_Target.y += 10.0f;
		}
	}
}



void ChocolaDestructor()
{
}


void ChocolaDisp()
{
	if (!chocolaPtr)
		return;

	auto p = playerTop[chocolaPtr->playerno];
	if (p)
	{
		if (p->mode == 999 || p->charMode == CHAR_MODE_Inactive)
			return;
	}

	for (uint8_t i = 0; i < 2; i++)
	{
		if (TObjChocolaPclump[i])
			RPClumpRender(TObjChocolaPclump[i]);
	}
}

void ChocolaTDisp()
{
}

void ChocolaPDisp()
{
}


void ChocolaExec()
{
	if (!chocolaPtr)
		return;

	if (!playerTop[0])
		return;

	TObjPlayer* p = nullptr;


	if (chocolaPtr->playerno == -1)
	{
		for (uint8_t i = 0; i < 8; i++)
		{
			p = playerTop[i];

			if (p && p->characterKind == Char_Cream)
			{
				PrintMessage("Chocola Exec: Cream Found\n");
				chocolaPtr->playerno = i;
				auto v5 = GetTeamCharacterIdFromCCLCharacterId(playerTop[(char)i]->C_COLLI_.character_id);
				chocolaPtr->ccl.character_id = GetTeamCharacterIdFromCCLCharacterId(v5);
				RpClumpForAllAtomics(
					TObjChocolaPclump[1],
					(RpAtomicCallBack)plCallbackRpAtomicToSetRenderCallbackToUseLight,
					(void*)chocolaPtr->playerno);
				RpClumpForAllAtomics(
					TObjChocolaPclump[0],
					(RpAtomicCallBack)plCallbackRpAtomicToSetRenderCallbackToUseLight,
					(void*)chocolaPtr->playerno);

				break;
			}

			if (i >= PMax)
				return;
		}
	}

	p = playerTop[chocolaPtr->playerno];

	if (!p)
		return;

	switch (p->reqaction)
	{
	case 1u:
	case 2u:
	case 3u:
	case 43u:
	case 44u:
		if (chocolaPtr->mode != 5)
		{
			chocolaPtr->mode = 5;
			chocolaPtr->timer_Attack = 60;
			TObjChocolaSetAnimation(3, chocolaPtr);
		}
		break;
	case 31u:
	case 32u:
		if (chocolaPtr->mode != 3)
		{
			chocolaPtr->mode = 3;
			TObjChocolaSetAnimation(0, chocolaPtr);
		}
		break;
	case 46u:
	case 47u:
		if (chocolaPtr->mode != 4)
		{
			chocolaPtr->mode = 4;
			chocolaPtr->timer_Attack = 0;
			TObjChocolaSetAnimation(6, chocolaPtr);
		}
		break;
	default:

		if (chocolaPtr->mode >= 3 && chocolaPtr->mode <= 4)
		{
			chocolaPtr->mode = 1;
			TObjChocolaSetAnimation(0, chocolaPtr);
		}
		break;
	}

	chocolaPtr->pos.x = chocolaPtr->ccl.pos.x;
	chocolaPtr->pos.y = chocolaPtr->ccl.pos.y;
	chocolaPtr->pos.z = chocolaPtr->ccl.pos.z;

	switch (chocolaPtr->mode)
	{
	case 0:
		TObjChocolaGetTargetPositionToChaseHer((TObjChocola*)chocolaPtr);

		if (!TObjCheeseCalcRotationAndSpeedToReach((TObjCheese*)chocolaPtr))
		{
			TObjChocolaSetAnimation(1, chocolaPtr);
		}
		else
		{
			chocolaPtr->mode++;
		}
		break;
	case 1:
		TObjChocolaGetTargetPositionToChaseHer((TObjChocola*)chocolaPtr);
		if (TObjCheeseCalcPosSomething((TObjCheese*)chocolaPtr))
		{
			chocolaPtr->mode = 0;
			TObjChocolaSetAnimation(1, chocolaPtr);
		}
		else
		{
			TObjChocolaSetAnimation(0, chocolaPtr);
		}
		break;
	case 2:

		break;
	case 3:

		break;
	case 4:
		chocolaPtr->pos = p->position;
		chocolaPtr->pos_Target = p->position;
		chocolaPtr->ang = p->ang;
		break;
	case 5:

		if (--chocolaPtr->timer_Attack < 0)
		{
			chocolaPtr->mode = 0;
			TObjChocolaSetAnimation(1, chocolaPtr);
		}
		break;
	}

	if (pHAH_Chocola)
	{
		float v27 = chocolaPtr->nframe;
		if (chocolaPtr->animno == 4)
		{
			float v29 = v27 + 1.0f;
			chocolaPtr->nframe = v29;
			if (v29 >= 30.0f)
				TObjChocolaSetAnimation(5, chocolaPtr);
		}
		else if (chocolaPtr->animno == 6)
		{
			float v28 = v27 + 0.5f;
			chocolaPtr->nframe = v28;
			if (v28 >= 155.0f)
				chocolaPtr->nframe = 105.0f;
		}
		else
		{
			chocolaPtr->nframe = v27 + 1.0f;
		}
		float timea = chocolaPtr->nframe * 0.016f;
		RtAnimInterpolatorSetCurrentTime(pHAH_Chocola->currentAnim, timea);
		RpHAnimHierarchyUpdateMatrices(pHAH_Chocola);
	}


	if (TObjChocolaPclump[0])
	{
		auto frameMdl = (RwFrame*)TObjChocolaPclump[0]->object.parent;

		float Cos = 1.0f - (sine[-(chocolaPtr->ang.y) & 0xffff]);
		float Sin = (sine[-(chocolaPtr->ang.y) - 0x4000u & 0xffff]);

		RwMatrixRotateOneMinusCosineSine(&frameMdl->modelling, &AxisY, Cos, Sin, rwCOMBINEREPLACE);
		RwV3d pos = { 5.0f, 0.0f, 0.0f };
		RwFrameTranslate(frameMdl, &pos, rwCOMBINEPRECONCAT);
		RwFrameTranslate(frameMdl, &chocolaPtr->pos, rwCOMBINEPOSTCONCAT);
	}

	PLNodeSetParameter(&chocolaPtr->head);

	if (TObjChocolaPclump[1])  // Chao ball head
	{
		auto v35 = (RwFrame*)TObjChocolaPclump[1]->object.parent;
		memcpy(&v35->modelling, &chocolaPtr->head.matrix, sizeof(v35->modelling));
		v35->modelling = v35->modelling;
		RwFrameTranslate((RwFrame*)v35, &ChaoBallOffset, rwCOMBINEPRECONCAT);
		RwFrameUpdateObjects((RwFrame*)v35);
	}
	if (p->mode == 43 || chocolaPtr->animno == 6)
	{
		chocolaPtr->pos_shadow = chocolaPtr->head.pos;
	}
	else
	{
		chocolaPtr->pos_shadow = chocolaPtr->pos;
	}

	if (p->mode != 43)
	{
		auto v42 = chocolaPtr->ccl.info;
		if (chocolaPtr->mode == 2)
		{
			v42->damage = v42->damage & 0xFE | 2;
			chocolaPtr->ccl.strength = 15;
		}
		else
		{
			v42->damage &= 0xFCu;
		}

		if (chocolaPtr->mode == 3)
		{
			chocolaPtr->ccl.pos = chocolaPtr->pos;
			chocolaPtr->ccl.angle = chocolaPtr->ang;
		}
		else
		{
			C_COLLIEntry(&chocolaPtr->ccl, &chocolaPtr->pos, &chocolaPtr->ang);
		}
	}
}

struct vftableChocola {
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

static vftableChocola vfTable = { ChocolaDestructor, ChocolaExec, ChocolaDisp, ChocolaTDisp, ChocolaPDisp, nullsub, nullsub, nullsub, nullsub, nullsub };


void LoadChocola()
{
	PrintMessage("Init Chocola Custom Task..\n");
	chocolaPtr = (TObjChocola*)THeapCtrlMalloc(sizeof(TObjChocola) + 8, TaskHeap);
	TObjectCreate(&chocolaPtr->obj, TL_03);
	COLLIFv(&chocolaPtr->ccl);
	ObjMoveOnGroundFv(&chocolaPtr->objMove);
	chocolaPtr->obj.ClassName = (char*)"TObjChocola";
	chocolaPtr->obj.__vftable = &vfTable;
	chocolaPtr->playerno = -1;
	for (uint8_t i = 0; i < 7; i++)
		pHAA_List_Chocola[i] = 0;

	for (uint8_t i = 0; i < PMax; i++)
	{
		auto P = playerTop[i];
		if (P)
		{
			if (P->characterKind == Char_Cream && (P->mode != 999))
			{
				PrintMessage("Found Cream, execution of the task will continue\n");
				break;
			}
		}
	}

	auto oneFileMem = (ONEFILE*)RwEngineInstance->memoryFuncs.rwmalloc(92);

	if (oneFileMem)
	{
		if (OneFileCtor((char*)"playmodel/chocola.one", oneFileMem, 1))
		{
			PrintMessage("Successfully Loaded One File Chocola.\n");
		}
	}

	void* BufferData = RwEngineInstance->memoryFuncs.rwmalloc(0x19000);
	if (!ChocolaTexDictionary) //skip if already loaded
	{
		//3 is texID
		ChocolaTexDictionary = OneFileLoadTextureDictionary(3, BufferData, oneFileMem);
	}

	if (ChocolaTexDictionary)
	{
		int a3 = 6;
		RwTexDictionaryForAllTextures(ChocolaTexDictionary, objCallbackChangeTextureFilterMode, &a3);
		RwTexDictionarySetCurrent(ChocolaTexDictionary);
	}

	//load model
	TObjChocolaPclump[0] = OneFileLoadClump(2, BufferData, oneFileMem); //model
	TObjChocolaPclump[1] = OneFileLoadClump(4, BufferData, oneFileMem); //ball

	for (uint8_t i = 0; i < 7; ++i)
	{
		uint8_t indexOneFile = i + 5; //anim start at index 5 in the one file (originally 3 but +2 is needed due to how the index code work)
		auto v22 = OneFileLoadHAnimation(indexOneFile, (void*)BufferData, oneFileMem);
		pHAA_List_Chocola[i] = v22;
		auto v23 = v22->interpInfo->typeID;
		if (v23 != 2 && v23 == 1)
		{
			auto v24 = RtCompressedKeyConvertFromStdKey(v22);
			RtAnimAnimationDestroy(pHAA_List_Chocola[i]);
			pHAA_List_Chocola[i] = v24;
		}
	}


	if (BufferData)
		RwEngineInstance->memoryFuncs.rwfree((void*)BufferData);

	ReleaseOneFile(oneFileMem);
	RwEngineInstance->memoryFuncs.rwfree(oneFileMem);

	if (TObjChocolaPclump[0])
	{
		if (!pHAH_Chocola)
		{
			auto v28 = &TObjChocolaPclump[0]->object.parent;
			auto anim = RpHAnimFrameGetHierarchy((RwFrame*)TObjChocolaPclump[0]->object.parent);
			if (!anim)
			{
				RwFrameForAllChildren((RwFrame*)*v28, GetChildFrameHierarchy, &anim);
			}

			pHAH_Chocola = anim;
		}

		if (pHAH_Chocola)
		{
			RpClumpForAllAtomics(TObjChocolaPclump[0], SetHierarchyForSkinAtomic, pHAH_Chocola);
			pHAH_Chocola->flags |= 0x3000u;
			RtAnimInterpolatorSetCurrentAnim(&pHAH_Chocola->currentAnim->pCurrentAnim, &pHAA_List_Chocola[0]->interpInfo);
			RpHAnimHierarchyAttach(pHAH_Chocola);
			RpHAnimHierarchyUpdateMatrices(pHAH_Chocola);
			RtAnimInterpolatorSetCurrentTime(pHAH_Chocola->currentAnim, 0.0f);
			RtAnimInterpolatorAddAnimTime(pHAH_Chocola->currentAnim, 0.0f);
			chocolaPtr->head.pFrame_Root = pHAH_Chocola->parentFrame;
			SearchNodeFrameFromNodeID(1, pHAH_Chocola, (PL_NODE_PARAMETER*)&chocolaPtr->head);
		}
	}

	C_COLLIInit(1u, &chocolaPtr->ccl, &Cheese_Col, 1);
}

void* __fastcall MallocCheese(unsigned int size, THeapCtrl* this_)
{
	LoadChocola();
	TObjCheese* cheeseTask = (TObjCheese*)THeapCtrlMalloc(0x1BCu, TaskHeap);
	return cheeseTask;
}


void InitChocola()
{
	WriteCall((void*)0x5C1629, MallocCheese);
}