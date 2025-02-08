#pragma once

void COLLIFv(C_COLLI* param_1);
void ObjMoveOnGroundFv(OBJ_MoveOnGround* obj);
void __fastcall nullsub();


float njCos(int n);
float njSin(int n);
int AdjustAngle(__int16 bams_a, unsigned __int16 bams_b, int limit);
void WriteNop(intptr_t address, const uint16_t count);
bool PlayerCheckSlowSpinSpinDash(TObjPlayer* p);
void RunCommonPhysics(TObjPlayer* p);

bool ChkInputLight(TObjPlayer* p);
bool IsOnPath(TObjPlayer* p);