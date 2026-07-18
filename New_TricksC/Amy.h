#pragma once

void initBird();

namespace Amy
{
	void Init();
	bool CheckHammerFloatInput(TObjPlayer* p);
	void RunAmyExecMode(TObjPlayer* p);
	bool RunAmyChkMode(TObjPlayer* p);
}

namespace HammerJump
{
	void Init();
	extern short HammerJumpAct;
	extern short HammerJumpMtn;
	void RunPhysics(TObjPlayer* p);
	void RunChkMode(TObjPlayer* p);
}