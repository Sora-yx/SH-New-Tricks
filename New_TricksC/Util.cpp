#include "pch.h"

void COLLIFv(C_COLLI* param_1)
{
	param_1->info = 0x0;
	param_1->flag = 0;
	param_1->nbHit = 0;
	param_1->nbInfo = 0;
	param_1->strength = 1;
	param_1->vitality = 1;
	param_1->field_7C.y = 0.0f;
}

void ObjMoveOnGroundFv(OBJ_MoveOnGround* obj)
{
	obj->spdObject.z = 0.0f;
	obj->spdObject.y = 0.0f;
	obj->spdObject.x = 0.0f;
	obj->cCheck = 1;
	obj->bound_mode = OBJ_MOG_BOUND_MODE_REAL;
	obj->bound_coef = 0.75f;
	obj->flagMOG = obj->flagMOG & 0xf0ff;
	obj->flagMOG = obj->flagMOG & 0xfff0;
	obj->lattr_Ignore = 0;
}