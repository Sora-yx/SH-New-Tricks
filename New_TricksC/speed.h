#pragma once


namespace SpeedChars
{
	void Init();
}

namespace SpinDash
{
	enum Act
	{
		ActCharge = 0x1,
		ActRelease = 0x36
	};

	void Init();
	void SetDefaultChargeSpd(TObjPlayer* p);
	void RunChargePhysics(TObjPlayer* p);
	void RunReleasePhysics(TObjPlayer* p);
	bool Charge(TObjPlayer* p);
	bool Release_(TObjPlayer* p);
}

namespace Bounce
{

	extern short Act;
	extern short ActRebound;
	void RunPhysics(TObjPlayer* p);
	void RunChkMode(TObjPlayer* p);
	void RunChkModeRebounce(TObjPlayer* p);
	bool CheckInputPress(TObjPlayer* p);
	void Init();
}