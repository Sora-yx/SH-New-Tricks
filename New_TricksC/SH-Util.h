#pragma once

#define PL_FLAG_INPUT      0x1000                  
#define PL_FLAG_PATH       0x2000 

enum RwRenderState
{
    rwRENDERSTATENARENDERSTATE = 0,
    rwRENDERSTATETEXTURERASTER = 1,
    rwRENDERSTATETEXTUREADDRESS = 2,
    rwRENDERSTATETEXTUREADDRESSU = 3,
    rwRENDERSTATETEXTUREADDRESSV = 4,
    rwRENDERSTATETEXTUREPERSPECTIVE = 5,
    rwRENDERSTATEZTESTENABLE = 6,
    rwRENDERSTATESHADEMODE = 7,
    rwRENDERSTATEZWRITEENABLE = 8,
    rwRENDERSTATETEXTUREFILTER = 9,
    rwRENDERSTATESRCBLEND = 10,
    rwRENDERSTATEDESTBLEND = 11,
    rwRENDERSTATEVERTEXALPHAENABLE = 12,
    rwRENDERSTATEBORDERCOLOR = 13,
    rwRENDERSTATEFOGENABLE = 14,
    rwRENDERSTATEFOGCOLOR = 15,
    rwRENDERSTATEFOGTYPE = 16,
    rwRENDERSTATEFOGDENSITY = 17,
    rwRENDERSTATECULLMODE = 20,
    rwRENDERSTATESTENCILENABLE = 21,
    rwRENDERSTATESTENCILFAIL = 22,
    rwRENDERSTATESTENCILZFAIL = 23,
    rwRENDERSTATESTENCILPASS = 24,
    rwRENDERSTATESTENCILFUNCTION = 25,
    rwRENDERSTATESTENCILFUNCTIONREF = 26,
    rwRENDERSTATESTENCILFUNCTIONMASK = 27,
    rwRENDERSTATESTENCILFUNCTIONWRITEMASK = 28,
};




enum PlayerStatus
{
	PlayerStatus_isOnGround = 0x1,
	PlayerStatus_isOnObject = 0x2,
	PlayerStatus_isHurt = 0x4,
	PlayerStatus_0x8 = 0x8,
	PlayerStatus_0x10 = 0x10,
	PlayerStatus_0x20 = 0x20,
	PlayerStatus_0x40 = 0x40,
	PlayerStatus_0x80 = 0x80,
	PlayerStatus_isJumpBall = 0x100,
	PlayerStatus_isAttacking = 0x400,
	PlayerStatus_UsedDashPad = 0x1000,
	PlayerStatus_AutoPath = 0x2000,
	PlayerStatus_AutoMoveAtStart = 0x4000,
	PlayerStatus_CanUseSpecialAttacks = 0x100000,
	PlayerStatus_hasPressedJump = 0x200000,
	PlayerStatus_Konohagakure = 0x400000,
	PlayerStatus_0x800000 = 0x800000,
	PlayerStatus_isNotNPC = 0x1000000,
	PlayerStatus_AvailableForAirAttack = 0x2000000,
};


struct Pt_TEXTURE {

    RwTexture* pTex; // offset 0x0, size 0x4
    char* pTexName; // offset 0x4, size 0x4
};

struct Pt_TEXLIST {
    Pt_TEXTURE* pTexArray; // offset 0x0, size 0x4
    unsigned int numTexArray; // offset 0x4, size 0x4
};


DataPointer(RwV3d, AxisX, 0x742EBC);
DataPointer(RwV3d, AxisZ, 0x742ED4);
FunctionPointer(RwFrame*, RwFrameRotate, (RwFrame* frame, const RwV3d* axis, RwReal angle, RwOpCombineType combineOp), 0x64C800);
FunctionPointer(int, RwRenderStateGet, (RwRenderState state, void* value), 0x64CA00);
FunctionPointer(int, RwRenderStateSet, (RwRenderState state, void* value), 0x64C9B0);
FastcallFunctionPointer(void, TObjectDestructor, (TObject* t), 0x443320);
FastcallFunctionPointer(BOOL, PCheckStop, (TObjPlayer* p), 0x5A56A0);
DataPointer(int, IsndSE, 0xA2F8B0);

intptr_t ShadowMotionsAddress = 0x8C5438;
intptr_t EspioMotionsAddress = 0x8C67E8;
DataPointer(sPeriCtrl, PeriCtrl, 0xA23678);
DataArray(unsigned int, PeriCtrlMap, 0x7C7418, 7);
FunctionPointer(RwBool, RpClumpDestroy, (RpClump* clump), 0x66BC60);
FunctionPointer(RwBool, RwTexDictionaryDestroy, (RwTexDictionary* dict), 0x64E060);


//void __userpurge THeapCtrl::Free(void *addr@<eax>, THeapCtrl *this)
static const void* const THeapCtrlFreePtr = (void*)0x4282D0;
static inline void THeapCtrlFree(void* addr, THeapCtrl* this_)
{

    __asm
    {
        push[this_]
        mov eax, [addr]
        call THeapCtrlFreePtr
    }
}

//int __userpurge IsndSE::Play@<eax>(__int16 seId_HHC@<bx>, RwV3d *pos@<edi>, IsndSE *this@<esi>, char a4, int a5)
static const void* const IsndSEPlayPtr = (void*)0x440750;
static inline int IsndSEPlay(__int16 seId_HHC, RwV3d* pos, void* this_, char a4, int a5)
{
	int result;
    __asm
    {
        push a5
        movzx eax, a4  //Ensure a4 is 4 bytes before pushing
        push eax
		mov esi, this_
		mov edi, pos
        mov bx, seId_HHC
        call IsndSEPlayPtr
        mov result, eax
    }
	return result;
}

namespace COLLI_
{
    //CCL_INFO *__usercall C_COLLI::~C_COLLI@<eax>(C_COLLI *a1@<edi>)
    static const void* const DestructorPtr = (void*)0x407440;
    static inline CCL_INFO* Destructor(C_COLLI* a1)
    {
        CCL_INFO* result;
        __asm
        {
            mov edi, a1
            call DestructorPtr
            mov result, eax
        }
        return result;
    }
}


namespace ADV_STORY
{
    //int __usercall ADV_STORY::GetStoryProgress@<eax>(int a1@<eax>)
    static const void* const GetStoryProgressPtr = (void*)0x4564E0;
    static inline int GetStoryProgress(int teamID)
    {
        int result;
        __asm
        {
            mov eax, teamID
            call GetStoryProgressPtr
            mov result, eax
        }
        return result;
    }
}

DataPointer(int, dword_7C8BE4, 0x7C8BE4);

namespace TQuestSeqCtrl
{
    //int __usercall ADV_STORY::GetStoryProgress@<eax>(int a1@<eax>)
    static const void* const CheckSequenceVarsPtr = (void*)0x442BC0;
    static inline int CheckSequenceVars(int teamID)
    {
        int result;
        __asm
        {
            mov eax, teamID
            call CheckSequenceVarsPtr
            mov result, eax
        }
        return result;
    }
}

static auto SetEffectDash = GenerateUsercallWrapper<int* (*)(BYTE formationTypeID)>(rEAX, 0x6348E0, rBL);
static auto VibeShot = GenerateUsercallWrapper<void (*)(int a1, int controllerNo, int a3, int count)>(noret, 0x4442D0, rEAX, rECX, stack4, stack4);
FunctionPointer(int*, SetEffectRocketJump, (char character), 0x639F20);