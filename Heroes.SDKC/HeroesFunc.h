#ifndef HEROESFUNC_H
#define HEROESFUNC_H

#include <stdint.h>
#include "MemAccess.h"
#include "UsercallFunctionHandler.h"
#include "HeroesStruct.h"
#include "HeroesEnum.h"

ThiscallFunctionPointer(void, PChangeRunningMotion, (TObjPlayer* p), 0x5A49F0);
StdcallFunctionPointer(int, CheckBeInTheAir, (TObjPlayer* p), 0x5A5860);

StdcallFunctionPointer(void, TobjSonicChkMode, (TObjSonic* p), 0x5CE550);
StdcallFunctionPointer(void, TobjSonicExecMode, (TObjPlayer* p), 0x5CD670);
StdcallFunctionPointer(int, TObjSonicChkInput, (TObjSonic* p), 0x5D35F0);


static auto SonicCheckJump = GenerateUsercallWrapper<int (*)(TObjPlayer* p)>(rEAX, 0x5D35D0, rEAX, rEAX);
static auto PCheckPower = GenerateUsercallWrapper<int (*)(float* stroke, int* angle, TObjPlayer * p)>(rEAX, 0x591340, rEAX, rEBX, rEDI, rESI);

static auto PGetSpeed = GenerateUsercallWrapper<void (*)(TObjPlayer * p)>(noret, 0x59E8C0, rEAX);
static auto PGetRotation = GenerateUsercallWrapper<void (*)(TObjPlayer * p)>(noret, 0x58E7A0, rEAX);
static auto PGetBreak = GenerateUsercallWrapper<void (*)(TObjPlayer * p)>(noret, 0x58DEB0, rEAX);
static auto PSetPosition = GenerateUsercallWrapper<int (*)(TObjPlayer * p)>(rEAX, 0x593B80, rEAX);
static auto PGetInertia = GenerateUsercallWrapper<void (*)(TObjPlayer * p)>(noret, 0x58E5C0, rEAX);
static auto PResetPosition = GenerateUsercallWrapper<void (*)(TObjPlayer * p)>(noret, 0x59A830, rEAX);
static auto PGetAccelerationAir = GenerateUsercallWrapper<void (*)(TObjPlayer * p)>(noret, 0x58D840, rEAX);

static auto SetEffectObi = GenerateUsercallWrapper<void (*)(int charNo)>(noret, 0x639120, rEDI);
static auto SetEffDash = GenerateUsercallWrapper<int* (*)(char p)>(rEAX, 0x639120, rBL);
static auto ReleaseOneFile = GenerateUsercallWrapper<signed int (*)(ONEFILE * this_)>(rEAX, 0x42F210, rEBX);

FunctionPointer(void, SetRocketHit, (char charNo), 0x639EA0);

FunctionPointer(RwMatrix*, RwMatrixTranslate, (RwMatrix* matrix, RwV3d* translation, RwOpCombineType combineOp), 0x650E00);
FunctionPointer(RwStream*, RwStreamOpen, (RwStreamType type, RwStreamAccessType accessType, const void* pData), 0x64DCE0);

FunctionPointer(const RwTexDictionary*, RwTexDictionaryForAllTextures, (const RwTexDictionary* dict, RwTextureCallBack fpCallBack, void* pData), 0x64E0F0);
FunctionPointer(RwTexture*, objCallbackChangeTextureFilterMode, (RwTexture* texture, void* pdata), 0x42BCB0);
FunctionPointer(RwTexDictionary*, RwTexDictionarySetCurrent, (RwTexDictionary* dict), 0x64E430);
FunctionPointer(RpClump*, RPClumpRender, (RpClump* a1), 0x66B4F0);
FunctionPointer(RwBool, RwStreamClose, (RwStream* stream, void* pdata), 0x64DC10);
FunctionPointer(RwFrame*, RwFrameTranslate, (RwFrame* frame, const RwV3d* translation, RwOpCombineType combineOp), 0x64C620);
FunctionPointer(RwMatrix*, RwMatrixRotateOneMinusCosineSine, (RwMatrix* matrix, const RwV3d* unitAxis, float oneMinusCosine, float sine, RwOpCombineType combineOp), 0x6506B0);
FunctionPointer(RpClump*, RpClumpForAllAtomics, (RpClump* clump, RpAtomicCallBack callback, void* pdata), 0x66B540);
FunctionPointer(RpAtomicCallBack, plCallbackRpAtomicToSetRenderCallbackToUseLight, (RpAtomic* a1, void* a2), 0x581F30);
FunctionPointer(void, RtAnimInterpolatorSetCurrentAnim, (void* a1, void* a2), 0x69DFC0);
FunctionPointer(int, RtAnimInterpolatorSetCurrentTime, (void* anim, float time), 0x69E490);
FunctionPointer(RwBool, RpHAnimHierarchyUpdateMatrices, (RpHAnimHierarchy* hierarchy), 0x6A8660);
FunctionPointer(RwFrame*, RwFrameUpdateObjects, (RwFrame* frame), 0x64C280);
FunctionPointer(RtAnimAnimation*, RtCompressedKeyConvertFromStdKey, (RtAnimAnimation* stdkeyanim), 0x6BAFF0);
FunctionPointer(RtAnimAnimation*, RtAnimAnimationDestroy, (RtAnimAnimation* animation), 0x69DB00);

FunctionPointer(RpHAnimHierarchy*, RpHAnimFrameGetHierarchy, (RwFrame* frame_), 0x6A8640);
FunctionPointer(RwFrame*, RwFrameForAllChildren, (RwFrame* frame_, RwFrameCallBack callBack_, void* data), 0x64C5E0);
FunctionPointer(RwFrame*, GetChildFrameHierarchy, (RwFrame* frame, void* data), 0x4A21F0);
FunctionPointer(RpAtomic*, SetHierarchyForSkinAtomic, (RpAtomic* atomic, void* data), 0x5A22A0);
FunctionPointer(RpHAnimHierarchy*, RpHAnimHierarchyAttach, (RpHAnimHierarchy* hierarchy), 0x6A8560);
FunctionPointer(int, RtAnimInterpolatorAddAnimTime, (RtAnimInterpolator* a1, float a2), 0x69E2B0);


StdcallFunctionPointer(int, TObjFormGateSubGetPlayerIDFromCol, (TObjFormGateSub* a1), 0x473C80);
ThiscallFunctionPointer(void, TObjOldPlayerPlayerModeChangeToFall, (TObjPlayer* p), 0x5A6E40);

ThiscallFunctionPointer(TObject*, TObjCheeseCreate, (TObject* this_, TObjCheese* cheese), 0x5B51C0);
FastcallFunctionPointer(void*, THeapCtrlMalloc, (unsigned int size, THeapCtrl* this_), 0x428280);


//void __usercall __spoils<ecx,edx> TObject::TObject(TObject *this@<eax>, TObject *parent@<ecx>)
static const void* const TObjectCreatePtr = (void*)0x443260;
static inline void TObjectCreate(TObject* t, TObject* parent)
{
	__asm
	{
		mov ecx, parent
		mov eax, t
		call TObjectCreatePtr
	}
}

//void __usercall C_COLLI::Init(unsigned __int8 id@<al>, C_COLLI *this@<esi>, CCL_INFO *info, int nbInfo)
static const void* const C_ColInitPtr = (void*)0x4074B0;
static inline int C_COLLIInit(uint8_t id, C_COLLI* this_, CCL_INFO* info, int nbinfo)
{
	int result;

	__asm
	{
		push[nbinfo]
		push[info]
		mov esi, [this_]
		mov al, [id]
		call C_ColInitPtr
		mov result, eax
	}
	return result;
}

//RwBool __userpurge ONEFILE::LoadOneFile@<eax>(ONEFILE *this@<eax>, char *filename)
static const void* const ONEFILELoadOneFilePtr = (void*)0x42F100;
static inline RwBool LoadOneFile(ONEFILE* this_, char* filename)
{
	RwBool result;

	__asm
	{
		push[filename]
		mov eax, [this_]
		call ONEFILELoadOneFilePtr
		mov result, eax
	}
	return result;
}

//ONEFILE *__userpurge ONEFILE::ONEFILE@<eax>(char *fname@<eax>, ONEFILE *this@<esi>, int boolLoadOneFile)
static const void* const ONEFILECtorPtr = (void*)0x42F0D0;
static inline ONEFILE* OneFileCtor(char* fname, ONEFILE* this_, int boolLoadOneFile)
{
	ONEFILE* result;

	__asm
	{
		push[boolLoadOneFile]
		mov esi, [this_]
		mov eax, [fname]
		call ONEFILECtorPtr
		mov result, eax
	}
	return result;
}

//RwTexDictionary *__userpurge ONEFILE::OneFileLoadTextureDictionay@<eax>(RwUInt32 type@<eax>, void *dest@<ecx>, ONEFILE *this)
static const void* const OneFileLoadTextureDictionaryPtr = (void*)0x42F3C0;
static inline RwTexDictionary* OneFileLoadTextureDictionary(RwUInt32 type_, void* dest, ONEFILE* this_)
{
	RwTexDictionary* result;

	__asm
	{
		push[this_]
		mov ecx, [dest]
		mov eax, [type_]
		call OneFileLoadTextureDictionaryPtr
		mov result, eax
	}
	return result;
}

//RwTexDictionary *__usercall texLoadTexDictionaryFile@<eax>(char *textureFileName@<eax>)
static const void* const texLoadTexDictionaryFilePtr = (void*)0x444090;
static inline RwTexDictionary* texLoadTexDictionaryFile(const char* texFileName)
{
	RwTexDictionary* result;

	__asm
	{
		mov eax, [texFileName]
		call texLoadTexDictionaryFilePtr
		mov result, eax
	}
	return result;
}

//RpClump *__userpurge ONEFILE::OneFileLoadClump@<eax>(RwUInt32 type@<eax>, void *dest@<ecx>, ONEFILE *this)
static const void* const OneFileLoadClumpPtr = (void*)0x42F440;
static inline RpClump* OneFileLoadClump(RwUInt32 id, void* dest, ONEFILE* this_)
{
	RpClump* result;

	__asm
	{
		push[this_]
		mov ecx, [dest]
		mov eax, [id]
		call OneFileLoadClumpPtr
		mov result, eax
	}
	return result;
}

//RtAnimAnimation *__userpurge ONEFILE::OneFileLoadHAnimation@<eax>(RwUInt32 type@<eax>, void *dest@<ecx>, ONEFILE *this)
static const void* const OneFileLoadHAnimationPtr = (void*)0x42F600;
static inline RtAnimAnimation* OneFileLoadHAnimation(RwUInt32 id, void* dest, ONEFILE* this_)
{
	RtAnimAnimation* result;

	__asm
	{
		push[this_]
		mov ecx, [dest]
		mov eax, [id]
		call OneFileLoadHAnimationPtr
		mov result, eax
	}
	return result;
}

//RwChar *__usercall RsPathnameCreate@<eax>(const RwChar *srcBuffer@<eax>)
static const void* const RsPathnameCreatePtr = (void*)0x446100;
static inline RwChar* RsPathnameCreate(const RwChar* srcBuffer)
{
	RwChar* result;

	__asm
	{
		mov eax, [srcBuffer]
		call RsPathnameCreatePtr
		mov result, eax
	}
	return result;
}

//RwTexDictionary *__usercall texLoadTexDictionaryMemory@<eax>(RwStream *stream@<esi>)
static const void* const texLoadTexDictionaryMemoryPtr = (void*)0x444040;
static inline RwTexDictionary* texLoadTexDictionaryMemory(RwStream* stream)
{
	RwTexDictionary* result;

	__asm
	{
		mov esi, [stream]
		call texLoadTexDictionaryMemoryPtr
		mov result, eax
	}
	return result;
}

static const void* const TObjCheeseCalcRotationAndSpeedToReachPtr = (void*)0x5B5A10;
static inline int TObjCheeseCalcRotationAndSpeedToReach(TObjCheese* cheese)
{
	int result;

	__asm
	{
		mov esi, [cheese]
		call TObjCheeseCalcRotationAndSpeedToReachPtr
		mov result, eax
	}
	return result;
}

static const void* const TObjCheeseCalcPosSomethingPtr = (void*)0x5B5CA0;
static inline int TObjCheeseCalcPosSomething(TObjCheese* cheese)
{
	int result;

	__asm
	{
		mov ebx, [cheese]
		call TObjCheeseCalcPosSomethingPtr
		mov result, eax
	}
	return result;
}


//int __usercall GetTeamCharacterIdFromCCLCharacterId@<eax>(int result@<eax>)
static const void* const GetTeamCharacterIdFromCCLCharacterIdPtr = (void*)0x582970;
static inline int GetTeamCharacterIdFromCCLCharacterId(int a1)
{
	int result;

	__asm
	{
		mov eax, [a1]
		call GetTeamCharacterIdFromCCLCharacterIdPtr
		mov result, eax
	}
	return result;
}

//int __usercall PL_NODE_PARAMETER::SetParameter@<eax>(PL_NODE_PARAMETER * a1@<eax>)
static const void* const PLNodeSetParameterPtr = (void*)0x581E10;
static inline int PLNodeSetParameter(PL_NODE_PARAMETER* a1)
{
	int result;

	__asm
	{
		mov eax, [a1]
		call PLNodeSetParameterPtr
		mov result, eax
	}
	return result;
}

//int __userpurge PL_NODE_PARAMETER::SearchNodeFrameFromNodeID@<eax>(int node_HHC@<ebx>, RpHAnimHierarchy *animation@<esi>, PL_NODE_PARAMETER *frame)
static const void* const SearchNodeFrameFromNodeIDPtr = (void*)0x581DB0;
static inline int SearchNodeFrameFromNodeID(int node_HHC, RpHAnimHierarchy* animation, PL_NODE_PARAMETER* frame)
{
	int result;

	__asm
	{
		push[frame]
		mov esi, [animation]
		mov ebx, [node_HHC]
		call SearchNodeFrameFromNodeIDPtr
		mov result, eax
	}
	return result;
}

//int __usercall C_COLLI::Entry@<eax>(C_COLLI *this@<eax>, RwV3d *pos@<edx>, sAngle *ang@<ecx>)
static const void* const C_COLLIEntryPtr = (void*)0x459210;
static inline int C_COLLIEntry(C_COLLI* col, RwV3d* pos, sAngle* ang)
{
	int result;
	__asm
	{
		mov ecx, [ang]
		mov edx, [pos]
		mov eax, [col]
		call C_COLLIEntryPtr
		mov result, eax
	}
	return result;
}


//void __usercall sub_58DBA0(int eax0@<eax>)
static const void* const sub_58DBA0Ptr = (void*)0x58DBA0;
static inline void sub_58DBA0(TObjPlayer* t)
{
	__asm
	{
		mov eax, [t]
		call sub_58DBA0Ptr
	}
}

//void __usercall PResetAngle(TObjPlayer *TObjPlayer@<eax>)
static const void* const PResetAnglePtr = (void*)0x591930;
static inline void PResetAngle(TObjPlayer* t)
{
	__asm
	{
		mov eax, [t]
		call PResetAnglePtr
	}
}


//void __usercall TObjOldPlayer::PlayerModeChangeToLand(TObjPlayer *esi0@<esi>)
static const void* const TObjOldPlayerPlayerModeChangeToLandPtr = (void*)0x5A6B40;
static inline void TObjOldPlayerPlayerModeChangeToLand(TObjPlayer* t)
{
	__asm
	{
		mov esi, [t]
		call TObjOldPlayerPlayerModeChangeToLandPtr
	}
}


//CCL_HIT_INFO *__usercall C_COLLI::IsHitKindEx@<eax>(unsigned __int8 kind@<bl>, C_COLLI *twp@<esi>)
static const void* const C_COLLIIsHitKindEPtr = (void*)0x414C70;
static inline CCL_HIT_INFO* C_COLLIIsHitKindEx(unsigned __int8 kind, C_COLLI* twp)
{
	CCL_HIT_INFO* result;

	__asm
	{
		mov esi, [twp]
		mov bl, [kind]
		call C_COLLIIsHitKindEPtr
		mov result, eax
	}
	return result;
}


#endif 