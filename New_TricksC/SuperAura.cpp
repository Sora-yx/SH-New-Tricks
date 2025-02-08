#include "pch.h"

RpClump* SADXAuraMdl =  nullptr;
RwTexDictionary* SADXAuraTexDictionary = nullptr;

struct TOBjSuperAura
{
	TObject obj;
	OBJ_MoveOnGround objMove;
	signed __int8 playerno = -1;
	signed __int16 mode = 0;
	RwV3d pos;

};


void LoadSuperAura()
{

	auto oneFileMem = (ONEFILE*)RwEngineInstance->memoryFuncs.rwmalloc(92);

	if (oneFileMem)
	{
		OneFileCtor((char*)"playmodel/SSAura.one", oneFileMem, 1);
	}

	void* BufferData = RwEngineInstance->memoryFuncs.rwmalloc(0x19000);
	if (!SADXAuraTexDictionary) //skip if already loaded
	{
		//3 is texID
		SADXAuraTexDictionary = OneFileLoadTextureDictionary(3, BufferData, oneFileMem);
	}

	if (SADXAuraTexDictionary)
	{
		RwTexDictionarySetCurrent(SADXAuraTexDictionary);
	}

	//load model
	SADXAuraMdl = OneFileLoadClump(2, BufferData, oneFileMem); //model

	if (BufferData)
		RwEngineInstance->memoryFuncs.rwfree((void*)BufferData);

	ReleaseOneFile(oneFileMem);
	RwEngineInstance->memoryFuncs.rwfree(oneFileMem);
}

FastcallMHook<void, TObjPlayer*> TObjSonicDisp_t(0x5D1A20);

void __fastcall TObjSonicDisp_r(TObjPlayer* this_)
{
	void* value;
	void* v18;
	void* v16;
	void* v15;
	void* a2a;
	RwRenderStateGet(rwRENDERSTATESRCBLEND, &value);
	RwRenderStateGet(rwRENDERSTATEDESTBLEND, &v18);
	RwRenderStateGet(rwRENDERSTATECULLMODE, &v16);
	RwRenderStateGet(rwRENDERSTATEFOGENABLE, &v15);
	RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &a2a);

	RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)5);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)1);
	RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)1);
	RwRenderStateSet(rwRENDERSTATEFOGENABLE, 0);
	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)1);

	RPClumpRender(SADXAuraMdl);

	RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)a2a);
	RwRenderStateSet(rwRENDERSTATEFOGENABLE, v15);
	RwRenderStateSet(rwRENDERSTATECULLMODE, v16);
	RwRenderStateSet(rwRENDERSTATESRCBLEND, value);
	RwRenderStateSet(rwRENDERSTATEDESTBLEND, v18);




	TObjSonicDisp_t.CallOriginal(this_);
}

MHook<TObjPlayer*, TObjTeam*, unsigned int, char> SetSonicTheHedgehog_Team_t(0x5CB170);
TObjPlayer* __cdecl SetSonicTheHedgehog_Team_r(TObjTeam* TObjTeam, unsigned int playerNo, char memberNo)
{
	auto res = SetSonicTheHedgehog_Team_t.CallOriginal(TObjTeam, playerNo, memberNo);
	LoadSuperAura();
	return res;
}

void initSuperAura()
{
	TObjSonicDisp_t.Hook(TObjSonicDisp_r);
	SetSonicTheHedgehog_Team_t.Hook(SetSonicTheHedgehog_Team_r);

}