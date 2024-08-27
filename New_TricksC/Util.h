#pragma once

void COLLIFv(C_COLLI* param_1);
void ObjMoveOnGroundFv(OBJ_MoveOnGround* obj);
void nullsub();

DataPointer(RwV3d, AxisX, 0x742EBC);

DataPointer(RwV3d, AxisZ, 0x742ED4);
FunctionPointer(RwFrame*, RwFrameRotate, (RwFrame* frame, const RwV3d* axis, RwReal angle, RwOpCombineType combineOp), 0x64C800);

float njCos(int n);
float njSin(int n);