#include "pch.h"
#include "speed.h"

//in Sonic Heroes, the exec function that run physics is split into two functions: "ExecCommonMode" and "ExecMode"
//ExecCommonMode is shared by everyone and is for actions (mode) < 54
//ExecMode is unique per character type (speed, fly, power) and run action >= 54

void TObjPlayExecCommonmode_r(TObjPlayer* p);
FastUsercallHook<void, TObjPlayer*> TObjPlayExecCommonmode_h(0x5A7B50, TObjPlayExecCommonmode_r, noret, rEAX);
//UsercallFuncVoid(TObjPlayExecCommonmode_h, (TObjPlayer* p), (p), 0x5A7B50, rEAX);

//only run action (mode) < 54 like explained above
//note: if we want to override the original move, we should return true
bool RunCommonExec(TObjPlayer* p)
{
	auto charID = p->characterKind;
	bool isSpinDash = true; /** ConfigV.isSpinDashAllowed(charID)*/;

	switch (p->mode)
	{
	case SpinDash::ActCharge:
		if (isSpinDash)
		{
			SpinDash::RunChargePhysics(p);
			return true; //will prevent the game to run the original physics in action 1 from rocket accel
		}
		break;
	}

	return false;
}


void TObjPlayExecCommonmode_r(TObjPlayer* p)
{

	if (RunCommonExec(p))
		return;

	TObjPlayExecCommonmode_h.Original(p);
}
