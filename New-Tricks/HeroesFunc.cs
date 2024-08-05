using Reloaded.Hooks.Definitions.X86;
using static Reloaded.Hooks.Definitions.X86.FunctionAttribute;
using Heroes.SDK;
using Heroes.SDK.Classes.NativeClasses;
using Reloaded.Hooks.Definitions;
using Heroes.SDK.Definitions.Enums.Custom;
using Heroes.SDK.Definitions.Structures.RenderWare;


namespace New_Tricks
{
    public static unsafe class HeroesFunc
    {
        #region PhysicsFunc
        [Function(new[] { Register.eax }, Register.eax, StackCleanup.Caller)]
        public delegate void PGetAccelAirType(TObjPlayer* p);
        public static IFunction<PGetAccelAirType> Fun_PGetAccelerationAir { get; } = SDK.ReloadedHooks.CreateFunction<PGetAccelAirType>(0x58D840);
        public static PGetAccelAirType PGetAccelerationAir { get; } = Fun_PGetAccelerationAir.GetWrapper();


        [Function(new[] { Register.eax }, Register.eax, StackCleanup.Caller)]
        public delegate void PGetSpdType(TObjPlayer* p);
        public static IFunction<PGetSpdType> Fun_PGetSpeed { get; } = SDK.ReloadedHooks.CreateFunction<PGetSpdType>(0x59E8C0);
        public static PGetSpdType PGetSpeed { get; } = Fun_PGetSpeed.GetWrapper();


        [Function(new[] { Register.eax }, Register.eax, StackCleanup.Caller)]
        public delegate void PGetRotType(TObjPlayer* p);
        public static IFunction<PGetRotType> Fun_PGetRot { get; } = SDK.ReloadedHooks.CreateFunction<PGetRotType>(0x58E7A0);
        public static PGetRotType PGetRotation { get; } = Fun_PGetRot.GetWrapper();


        [Function(new[] { Register.eax }, Register.eax, StackCleanup.Caller)]
        public delegate void PGetBreakType(TObjPlayer* p);
        public static IFunction<PGetBreakType> Fun_PGetBreak { get; } = SDK.ReloadedHooks.CreateFunction<PGetBreakType>(0x58DEB0);
        public static PGetBreakType PGetBreak { get; } = Fun_PGetBreak.GetWrapper();

        [Function(new[] { Register.eax }, Register.eax, StackCleanup.Caller)]
        public delegate int PSetPosType(TObjPlayer* p);
        public static IFunction<PSetPosType> Fun_PSetPos { get; } = SDK.ReloadedHooks.CreateFunction<PSetPosType>(0x593B80);
        public static PSetPosType PSetPosition { get; } = Fun_PSetPos.GetWrapper();


        [Function(new[] { Register.eax }, Register.eax, StackCleanup.Caller)]
        public delegate void PGetInertiaType(TObjPlayer* p);
        public static IFunction<PGetInertiaType> Fun_PGetInertia { get; } = SDK.ReloadedHooks.CreateFunction<PGetInertiaType>(0x58E5C0);
        public static PGetInertiaType PGetInertia { get; } = Fun_PGetInertia.GetWrapper();

        [Function(new[] { Register.eax }, Register.eax, StackCleanup.Caller)]
        public delegate void PResetPosType(TObjPlayer* p);
        public static IFunction<PResetPosType> Fun_PResetPos { get; } = SDK.ReloadedHooks.CreateFunction<PResetPosType>(0x58E5C0);
        public static PResetPosType PResetPosition { get; } = Fun_PResetPos.GetWrapper();


        #endregion

        #region EffFuncs


        [Function(new[] { Register.edi }, Register.eax, StackCleanup.Caller)]
        public delegate void SetEffObiType(byte pno);
        public static IFunction<SetEffObiType> Fun_SetEffObi { get; } = SDK.ReloadedHooks.CreateFunction<SetEffObiType>(0x639120);
        public static SetEffObiType SetEffectObi { get; } = Fun_SetEffObi.GetWrapper();


        [Function(new[] { Register.ebx }, Register.eax, StackCleanup.Caller)]
        public delegate int* SetEffDashT(byte formationTypeID);
        public static IFunction<SetEffDashT> Fun_EffDash { get; } = SDK.ReloadedHooks.CreateFunction<SetEffDashT>(0x6348E0);
        public static SetEffDashT SetEffDash { get; } = Fun_EffDash.GetWrapper();


        [Function(CallingConventions.Cdecl)]
        public delegate void SetRocketHitT(byte charID);
        public static IFunction<SetRocketHitT> Fun_SetRocketHit { get; } = SDK.ReloadedHooks.CreateFunction<SetRocketHitT>(0x639EA0);
        public static SetRocketHitT SetRocketHit { get; } = Fun_SetRocketHit.GetWrapper();

        #endregion

        #region Players
        [Function(CallingConventions.MicrosoftThiscall)]
        public delegate void SetPChangeRunMtnType(TObjPlayer* p);
        public static IFunction<SetPChangeRunMtnType> Fun_PChangeRunMtn { get; } = SDK.ReloadedHooks.CreateFunction<SetPChangeRunMtnType>(0x5A49F0);
        public static SetPChangeRunMtnType PChangeRunningMotion { get; } = Fun_PChangeRunMtn.GetWrapper();

        [Function(CallingConventions.Stdcall)]
        public delegate int CheckBeInTheAirType(TObjPlayer* p);
        public static IFunction<CheckBeInTheAirType> Fun_CheckbeInTheAir { get; } = SDK.ReloadedHooks.CreateFunction<CheckBeInTheAirType>(0x5A5860);
        public static CheckBeInTheAirType CheckBeInTheAir { get; } = Fun_CheckbeInTheAir.GetWrapper();

        [Function(new[] { Register.eax }, Register.eax, StackCleanup.Caller)]
        public delegate int CheckJumpType(TObjPlayer* p);
        public static IFunction<CheckJumpType> Fun_ChkJump { get; } = SDK.ReloadedHooks.CreateFunction<CheckJumpType>(0x5D35D0);
        public static CheckJumpType SonicCheckJump { get; } = Fun_ChkJump.GetWrapper();

        [Function(CallingConventions.Stdcall)]
        public delegate int SonkChkInputType(TObjPlayer* p);
        public static IFunction<SonkChkInputType> Fun_SonkChkInput { get; } = SDK.ReloadedHooks.CreateFunction<SonkChkInputType>(0x5D35F0);
        public static SonkChkInputType SonicChkInput { get; } = Fun_SonkChkInput.GetWrapper();

        #endregion

        #region Misc

        [Function(new[] { Register.eax }, Register.eax, StackCleanup.Callee)]
        public delegate int PConvertVectorType(TObjPlayer* p, RwV3d* in_, RwV3d* out_);
        public static IFunction<PConvertVectorType> Fun_PConvVectorP2G { get; } = SDK.ReloadedHooks.CreateFunction<PConvertVectorType>(0x580520);
        public static PConvertVectorType PConvertVector_P2G { get; } = Fun_PConvVectorP2G.GetWrapper();


        /*Used to create Tornado with Amy*/
        [Function(new[] { Register.ecx, Register.edi }, Register.eax, StackCleanup.Caller)]
        public delegate void sub_63E940T(int ecx, int* a2, byte a3, int* pos, int* a4);
        public static IFunction<sub_63E940T> Fun_63E940 { get; } = SDK.ReloadedHooks.CreateFunction<sub_63E940T>(0x63E940);
        public static sub_63E940T sub_63E940 { get; } = Fun_63E940.GetWrapper();

        #endregion

       

       
        #region Sound

        [Function(new[] { Register.ebx, Register.edi, Register.esi }, Register.eax, StackCleanup.Callee)]
        public delegate int IsndSEPlayT(ushort seId, RwV3d* pos, Sound.IsndSE* IsndSE, byte a4, int a5);
        public static IFunction<IsndSEPlayT> Fun_IsndSEPlay { get; } = SDK.ReloadedHooks.CreateFunction<IsndSEPlayT>(0x440750);
        public static IsndSEPlayT IsndSEPlay { get; } = Fun_IsndSEPlay.GetWrapper();



        #endregion

        #region Functions
        public static void RunCommonPhysics(TObjPlayer* p)
        {
            PGetSpeed(p);
            PSetPosition(p);
            PResetPosition(p);
        }

        public static bool PlayerCheckSlowSpin(TObjPlayer* p)
        {
            if (p->spd.x >= p->p.slide_speed)
                return false;

            if (p->spd.x > 0.0f)
            {
                p->mode = (ushort)PlayerMode.Running;
            }
            else
            {
                p->mode = 0;
                p->idleTime = 0;
            }
            p->statusRelated0x1B8 &= ~1280;
            p->motion = (short)PlayerAnim.PlayerAnimation_Land_;

            return true;
        }
        #endregion
    }
}
