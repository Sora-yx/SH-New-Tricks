using Heroes.SDK;
using Heroes.SDK.Classes.NativeClasses;
using Reloaded.Hooks.Definitions;
using Reloaded.Hooks.Definitions.X86;
using static System.Runtime.InteropServices.JavaScript.JSType;
using Heroes.SDK.Definitions.Enums;
using Heroes.SDK.Definitions.Enums.Custom;
using New_Tricks.Configuration;
using New_Tricks.Moveset;
using static Reloaded.Hooks.Definitions.X86.FunctionAttribute;
using Heroes.SDK.Definitions.Structures.Player;
using static New_Tricks.HeroesFunc;
using Heroes.SDK.Definitions.Structures.RenderWare;
using System.Collections.Generic;


namespace New_Tricks.Characters
{

    public unsafe class SpeedChars
    {
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


        [Function(new[] { Register.edi }, Register.eax, StackCleanup.Callee)]
        public delegate void PSetMotionType(mtnmanwk* a1, int a2);
        private IHook<PSetMotionType> _TPSetMotion;
        public static IFunction<PSetMotionType> Fun_PSetMotion { get; } = SDK.ReloadedHooks.CreateFunction<PSetMotionType>(0x5A22D0);
        #endregion


        private IHook<IsndSEPlayT> _TIsndSEPlay;

        int ChkInputHook(TObjPlayer* p)
        {
            if ((p->flag & 0x1000) == 0)
                return 0;

            int remFlag = p->flag & ~0x100000;
            int smode = p->smode - 2;
            bool isSpinDashAllowed = ConfigV.isSpinDashAllowed(p->characterKind);

            Console.WriteLine("smode is " + smode);
            switch (smode)
            {
                case 14:
                    //5A5AB0
                    if (isSpinDashAllowed && p->nextAnimation_HHC == 10)
                    {
                        p->motion = 10;
                        p->mode = 1;
                        p->flag = remFlag | 0x500;
                        p->gap988[0] = 60;


                        Sound.IsndSE* ptr = (Sound.IsndSE*)HeroesVariables.SndSE.Get();
                        if (ptr is not null)
                            IsndSEPlay(8293, &p->position, ptr, 0, 0);
                        SpinDash.SetDefaultChargeSpd(p);
                        return 1;
                    }

                    break;
                case 36:
                    if (isSpinDashAllowed)
                        return 0;
                    break;
                case 45:
                    //hammer tornado
                    if (ConfigV._modConfig.AmyTornadoTweaks)
                    {
                        if (p->characterKind == Character.Amy)
                        {
                            p->mode = (ushort)PlayerMode.Amy_Tornado;
                            p->motion = 100;
                            p->statusRelated0x1B8 &= 0xFFFFFAF;
                            return 1;
                        }
                    }
                    break;
                case 50:
                    if (p->characterKind == Character.Amy && isSpinDashAllowed)
                    {
                        return 0;
                    }
                    break;
                case 57:
                    if (p->characterKind == Character.Sonic && isSpinDashAllowed)
                    {
                        return 0;
                    }
                    break;

            }

            return _TObjSonicChkInput.OriginalFunction(p);
        }



        public bool RunCommonSpdCharsChkMode(TObjPlayer* p)
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

        public bool RunCommonSpdCharsExec(TObjPlayer* p)
        {
            bool isSpinDash = ConfigV.isSpinDashAllowed(p->characterKind);

            switch (p->mode)
            {
                case 1:
                    if (isSpinDash)
                    {
                        HeroesFunc.PGetRotation(p);
                        HeroesFunc.PGetBreak(p);
                        HeroesFunc.RunCommonPhysics(p);
                        HeroesFunc.SetEffectObi(Player.Pno);
                        return true;
                    }
                    break;

                case 54:
                    if (isSpinDash)
                    {
                        PGetRotation(p);
                        PGetInertia(p);
                        RunCommonPhysics(p);

                        if (p->animCopy == 10 || p->motion == 10)
                        {
                            SetEffectObi(Player.Pno);
                        }
                        return true;
                    }
                    break;
            }

            return false;
        }

        public void TObjSonicExecHook(TObjPlayer* p)
        {
            if (RunCommonSpdCharsExec(p))
                return;

            Amy.RunAmyExecMode(p);
            _TObjSonicExecMode.OriginalFunction(p);
        }

        public void TObjSonicChkModeHook(TObjPlayer* p)
        {
            if (RunCommonSpdCharsChkMode(p) || Amy.RunAmyChkMode(p))
                return;

            _TObjSonicChkMode.OriginalFunction(p);
        }

        public void PSetMotionHook(mtnmanwk* a1, int a2)
        {
            if (a1->reqaction == 10 && a1->mtnmode == 10) //hacky way to force jumpball anim to not be related on speed so it can work with Spin Dash
            {
                a1->mtnmode = 3;
            }

            _TPSetMotion.OriginalFunction(a1, a2);
        }

        public SpeedChars()
        {
            _TObjSonicChkMode = Fun_TObjSonicChkMode.Hook(TObjSonicChkModeHook).Activate();
            _TObjSonicExecMode = Fun_TObjSonicExecMode.Hook(TObjSonicExecHook).Activate();
            _TObjSonicChkInput = Fun_TObjSonicChkInput.Hook(ChkInputHook).Activate();

            Amy.Init();

            if (ConfigV.isSpinDashEnabledForAtLeastAPlayer())
                _TPSetMotion = Fun_PSetMotion.Hook(PSetMotionHook).Activate();


        }
    }
}
