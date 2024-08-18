using Heroes.SDK;
using Heroes.SDK.Classes.NativeClasses;
using Reloaded.Hooks.Definitions;
using Reloaded.Hooks.Definitions.X86;
using static System.Runtime.InteropServices.JavaScript.JSType;
using Heroes.SDK.Definitions.Enums;
using Heroes.SDK.Definitions.Enums.Custom;
using New_Tricks.Configuration;
using New_Tricks.Moveset;
using static New_Tricks.HeroesFunc;
using System.Diagnostics;



namespace New_Tricks.Characters
{

    public unsafe class SpeedChars
    {
        private Amy _Amy;

        #region variablesDefinition
        static public nuint SonkMotionsAddress = 0x8C4A60;
        static public nuint ShadowMotionsAddress = 0x8C5438;
        static public nuint EspioMotionsAddress = 0x8C67E8;


        #endregion

        #region HooksDefinition
        [Function(CallingConventions.Stdcall)]
        public delegate void TObjSonicChkMode(TObjPlayer* pwp);
        private IHook<TObjSonicChkMode> _TObjSonicChkMode;
        public static IFunction<TObjSonicChkMode> Fun_TObjSonicChkMode { get; } = SDK.ReloadedHooks.CreateFunction<TObjSonicChkMode>(0x5CE550);

        [Function(CallingConventions.Stdcall)]
        public delegate void TObjSonicExecMode(TObjPlayer* pwp);
        private IHook<TObjSonicExecMode> _TObjSonicExecMode;
        public static IFunction<TObjSonicExecMode> Fun_TObjSonicExecMode { get; } = SDK.ReloadedHooks.CreateFunction<TObjSonicExecMode>(0x5CD670);


        [Function(CallingConventions.Stdcall)]
        public delegate int TObjSonicChkInput(TObjPlayer* pwp);
        private IHook<TObjSonicChkInput> _TObjSonicChkInput;
        public static IFunction<TObjSonicChkInput> Fun_TObjSonicChkInput { get; } = SDK.ReloadedHooks.CreateFunction<TObjSonicChkInput>(0x5D35F0);



        [Function(CallingConventions.MicrosoftThiscall)]
        public delegate void TObjPModeChgReadyToRocketAccelT(TObjPlayer* p);
        private IHook<TObjPModeChgReadyToRocketAccelT> _TObjPModeChgReadyToRocketAccelT;
        public static IFunction<TObjPModeChgReadyToRocketAccelT> Fun_TObjPModeChgReadyToRocketAccel { get; } = SDK.ReloadedHooks.CreateFunction<TObjPModeChgReadyToRocketAccelT>(0x5A6E10);


        #endregion

        private bool once = false;
        int ChkInputHook(TObjPlayer* p)
        {


            if ((p->flag & 0x1000) == 0)
                return 0;

            int smode = p->smode - 2;
            int remFlag = p->flag & 0x100000;
            bool isSpinDashAllowed = ConfigV.isSpinDashAllowed(p->characterKind);

            //Console.Write("\nsmode: " + smode);
            switch (smode)
            {
                case 14:
                    if (isSpinDashAllowed)
                    {
                        p->motion = 10;
                        p->mode = 1;
                        p->flag |= 0x500;
                        *(short*)p->gap988 = 60;


                        if (HeroesVariables.SndSE)
                            IsndSEPlay(8293, &p->position, (Sound.IsndSE*)HeroesVariables.SndSE.Get(), 0, 0);

                        SpinDash.SetDefaultChargeSpd((TObjPlayer*)p);
                        return 1;
                    }
                    break;
                case 45:
                    if (ConfigV._modConfig.AmyTornadoTweaks)
                    {
                        if (p->characterKind == Character.Amy)
                        {
                            p->mode = (short)PlayerMode.Amy_Tornado;
                            p->motion = 100;
                            p->flag &= unchecked((short)(0xFAFF));
                            return 1;
                        }
                    }
                    break;
                case 50: //remove legacy dash with spin dash
                    if (p->characterKind == Character.Amy && isSpinDashAllowed)
                    {
                        return 0;
                    }
                    break;
                case 55:
                    if (p->characterKind == Character.Espio && isSpinDashAllowed)
                    {
                        if (p->field_395 > 0)
                            break;

                        return 0;
                    }
                    break;
                case 57: //see above
                    if ((p->characterKind == Character.Sonic || p->characterKind == Character.Shadow) && isSpinDashAllowed)
                    {
                        return 0;
                    }
                    break;
            }

            return _TObjSonicChkInput.OriginalFunction(p);
        }



        private bool RunCommonSpdCharsChkMode(TObjPlayer* p)
        {
            bool isSpinDash = ConfigV.isSpinDashAllowed(p->characterKind);

            switch ((PlayerMode)p->mode)
            {
                case PlayerMode.RocketAccelCharge:
                    if (isSpinDash)
                    {
                        return SpinDash.Charge(p);
                    }
                    break;
                case PlayerMode.RocketAccelRelease:
                    if (isSpinDash)
                    {
                        return SpinDash.Release(p);
                    }
                    break;
            }

            return false;
        }

        private bool RunCommonSpdCharsExec(TObjPlayer* p)
        {
            var charID = p->characterKind;
            bool isSpinDash = ConfigV.isSpinDashAllowed(charID);

            switch (p->mode)
            {
                case (short)SpinDash.Act.Charge:
                    if (isSpinDash)
                    {
                        SpinDash.RunChargePhysics(p);
                        return true;
                    }
                    break;

                case (short)SpinDash.Act.Release:
                    if (isSpinDash)
                    {
                        SpinDash.RunReleasePhysics(p);
                        return true;
                    }
                    break;
                case 71:
                    if (isSpinDash && charID == Character.Espio && ConfigV._modConfig.EspioTornadoTweaks)
                    {
                        PGetAccelerationAir(p);
                        PGetSpeed(p);
                    }
                    break;

            }

            return false;
        }

        private void TObjSonicExecHook(TObjPlayer* p)
        {
            //Console.WriteLine("Cur Mode " + p->mode);
            if (RunCommonSpdCharsExec(p))
                return;

            Amy.RunAmyExecMode(p);
            _TObjSonicExecMode.OriginalFunction(p);
        }

        private void TObjSonicChkModeHook(TObjPlayer* p)
        {
            //Console.WriteLine("Current Mode " + p->mode);
            // Console.WriteLine("Cur ANim " + p->motion);
            if (RunCommonSpdCharsChkMode(p) || Amy.RunAmyChkMode(p))
                return;

            _TObjSonicChkMode.OriginalFunction(p);
        }



        //this doesn't use TObjPlayer; it's probably TObjOld, but I'm too lazy to figure the struct properly.
        //TObjTeam pointer seem to be at the exact same data, so we can use it instead.
        private void TObjPModeChgReadyToRocketAccelHook(TObjPlayer* p)
        {
            TObjTeam* team = p->pTObjTeam;

            Character player = team->playerPtr0[team->leaderPlayerNo].characterKind;
            if (ConfigV.isSpinDashAllowed(player))
            {
                return;
            }

            _TObjPModeChgReadyToRocketAccelT.OriginalFunction(p);
        }

        public SpeedChars()
        {
            _TObjSonicExecMode = Fun_TObjSonicExecMode.Hook(TObjSonicExecHook).Activate();
            _TObjSonicChkMode = Fun_TObjSonicChkMode.Hook(TObjSonicChkModeHook).Activate();
            _TObjSonicChkInput = Fun_TObjSonicChkInput.Hook(ChkInputHook).Activate();

            _Amy = new Amy();

            if (ConfigV._modConfig.EspioTornadoTweaks)
            {
                Util.WriteNop(0x5D0F3A, 0x5);     //remove Clear Speed
        
            }

            if (ConfigV.isSpinDashEnabledForAtLeastAPlayer())
            {
                _TObjPModeChgReadyToRocketAccelT = Fun_TObjPModeChgReadyToRocketAccel.Hook(TObjPModeChgReadyToRocketAccelHook).Activate();
                SpinDash.Init();
            }
        }
    }
}
