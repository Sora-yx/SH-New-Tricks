#pragma once

void LoadAmyBird();

namespace Amy
{
	void Init();
	bool CheckHammerFloatInput(TObjPlayer* p);
	void RunAmyExecMode(TObjPlayer* p);
	bool RunAmyChkMode(TObjPlayer* p);

}

namespace HammerJump
{

	enum AmyCustomAnimE
	{
		anm_HammerJump,
		anm_flip1,
		anm_flip2,
		anm_flip3
	};

	void Init();
	extern short Act;
	extern int AmyNewAnimIndex[];
	void RunPhysics(TObjPlayer* p);
	void RunChkMode(TObjPlayer* p);
}