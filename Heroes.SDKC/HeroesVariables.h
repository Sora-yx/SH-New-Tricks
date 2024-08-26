

#ifndef HEROESVARS_H
#define HEROESVARS_H

#include "MemAccess.h"
#include "HeroesStruct.h"


DataPointer(int*, SndSE, 0xA2F8B0);
DataArray(PLAYER_INPUT, player_input, 0xA4B298, 8);

DataArray(PL_MOTION, sonic_motions, 0x8C4A60, 105);
DataArray(PL_MOTION, shadow_motions, 0x8C5438, 105);
DataArray(PL_MOTION, amy_motions, 0x8C5E10, 105);
DataArray(PL_MOTION, espio_motions, 0x8C67E8, 105);

DataArray(PL_MOTION, knuckles_motions, 0x8BF678, 107);
DataArray(PL_MOTION, omega_motions, 0x8C0080, 107);
DataArray(PL_MOTION, big_motions, 0x8C0A88, 107);
DataArray(PL_MOTION, vector_motions, 0x8C1490, 107);

DataArray(PL_MOTION, miles_motions, 0x8C1FD0, 93);
DataArray(PL_MOTION, rouge_motions, 0x8C2888, 93);
DataArray(PL_MOTION, cream_motions, 0x8C3140, 93);
DataArray(PL_MOTION, charmy_motions, 0x8C39F8, 93);

DataArray(RtAnimAnimation*, pHAA_List_Cheese, 0xA4C278, 7);
DataPointer(CCL_INFO, Cheese_Col, 0x8BF638);
DataPointer(RwGlobals*, RwEngineInstance, 0x8E0A4C);
DataPointer(RwTexDictionary*, CheeseTexDictionary, 0xA78AB8);
DataArray(RpClump*, TObjCheesePclump, 0xA78AAC, 2);
DataPointer(RpHAnimHierarchy*, pHAH_Cheese, 0xA78AB4);
DataPointer(RwV3d, AxisY, 0x742EC8);
DataArray(char*, name_cheese_anim, 0x8BF61C, 7);
DataPointer(THeapCtrl*, TaskHeap, 0x9DEE00);
DataPointer(TObject*, TL_03, 0xA778AC);
DataPointer(const RwChar, fopen_rb, 0x799454);
DataPointer(RwModuleInfo, streamModule, 0x8E0A88);
DataArray(RwReal, sine, 0x9DEE08, 512);
DataPointer(RwV3d, ChaoBallOffset, 0x8DDF24);
DataPointer(CCL_SEARCH, CCL_MASTERSearch, 0x9CE864);


DataArray(int, gTeamMemberDat, 0x8BEB80, 16);
DataArray(TObjPlayer*, playerTop, 0xA4B1B0, 8);
DataArray(TObjTeam*, teamTop, 0xA4C268, 4);
DataArray(int, cannonCharacterIndex, 0x8DD134, 3);
DataArray(int, TeamcharacterIDOrder, 0x8DDD88, 3);

#endif