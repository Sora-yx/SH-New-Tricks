using Heroes.SDK;
using Heroes.SDK.Classes.NativeClasses;
using Reloaded.Hooks.Definitions;
using Reloaded.Hooks.Definitions.X86;
using static System.Runtime.InteropServices.JavaScript.JSType;
using New_Tricks.Configuration;
using static Reloaded.Hooks.Definitions.X86.FunctionAttribute;
using Heroes.SDK.Definitions.Enums.Custom;
using New_Tricks.Members;
using System.Diagnostics;


namespace New_Tricks.Characters
{
    public static class CommonFly
    {
        public unsafe static void RunFlyChkMode(TObjPlayer* p)
        {
            switch (p->mode)
            {

                default:

                    break;
            }
        }
    }


    public unsafe class FlyChars
    {
        #region definition
        [Function(CallingConventions.Stdcall)]
        public delegate void TObjMilesChkMode(TObjPlayer* pwp);
        private IHook<TObjMilesChkMode> _TObjMilesChkMode;
        public static IFunction<TObjMilesChkMode> Fun_TObjMilesChkMode { get; } = SDK.ReloadedHooks.CreateFunction<TObjMilesChkMode>(0x5C3EB0);

        [Function(new[] { Register.eax }, Register.eax, StackCleanup.Caller)]
        public delegate void MilesExecMoveT(TObjPlayer* a1);
        private IHook<MilesExecMoveT> _TMilesExecMove;
        public static IFunction<MilesExecMoveT> Fun_MilesExecMove { get; } = SDK.ReloadedHooks.CreateFunction<MilesExecMoveT>(0x5C3B30);

        static readonly byte[] flyByteNew = { 0x0, 0xC0, 0x79, 0x44 };
        static readonly byte[] flyByteOrigin = { 0x0, 0x0, 0x34, 0x43 };

        static private nuint flyVSpdCapAdd = 0x789FA4;
        static private byte[] flyVSpdCapNew = { 0x0, 0x0, 0x87, 0x43 };
        static private byte[] flyVSpdCapOrigin = { 0x0, 0x0, 0xB4, 0x42 };

        public static nuint creamMtnAddress = 0x8C3140;

        #endregion

        private float GetFlyTimerIncr(TObjTeam* t)
        {
            switch (t->level[1]) //1 is flying formation
            {
                case 1:
                    return 0.8f;
                case 2:
                    return 0.6f;
                case 3:
                    return 0.4f;
            }

            return 1.0f;
        }

        private float GetFlyMaxSpd(TObjTeam* t)
        {
            switch (t->level[1]) //1 is flying formation
            {
                case 1:
                    return 3.0f;
                case 2:
                    return 4.0f;
                case 3:
                    return 5.0f;
            }

            return 2.0f;
        }


        private void TObjMilesChkModeHook(TObjPlayer* p)
        {
            // Util.WriteData(flyTimeOffAdd, flyByteNew);
            _TObjMilesChkMode.OriginalFunction(p);


            //Util.WriteData(flyTimeOffAdd, flyByteOrigin);

        }

        private void TObjMilesExecMoveHook(TObjPlayer* p)
        {
            //Console.WriteLine("Miles Mod: " + p->mode);

            bool vSpeed = ConfigV._modConfig.IncreaseSpeedCap;
            bool flightT = ConfigV._modConfig.FlightTweaks;
            bool isCpu = Player.isCPU(p);

            if (vSpeed && !isCpu)
                Util.WriteData(flyVSpdCapAdd, flyVSpdCapNew);

            switch ((PlayerMode)p->mode)
            {
                case PlayerMode.Fly:
                    if (flightT && !isCpu)
                    {
                        if (HeroesFunc.PCheckPower(null, null, p) != 0)
                        {
                            if (p->lightDashLastRingPos_HHC.z < 180.0f)
                                p->lightDashLastRingPos_HHC.z += GetFlyTimerIncr(p->pTObjTeam);

                            if (p->spd.x < GetFlyMaxSpd(p->pTObjTeam))
                            {
                                p->spd.x += 0.04f;
                            }
                        }
                    }
                    break;
                case PlayerMode.FlyTired:
                    if (flightT && !isCpu)
                    {
                        if (HeroesFunc.PCheckPower(null, null, p) > 0 && p->spd.x < 1.0f)
                        {
                            p->spd.x += 1.0f; //goofy hacky way to interrupt kill momentum (for now).
                        }
                    }
                    break;
                case PlayerMode.Cream_CheeseAtk:
                    if (ConfigV._modConfig.CheeseTweaks)
                    {
                        HeroesFunc.PGetAcceleration(p);
                    }
                    break;
            }

            _TMilesExecMove.OriginalFunction(p);

            if (vSpeed && !Player.isCPU(p))
                Util.WriteData(flyVSpdCapAdd, flyVSpdCapOrigin);
        }


        public FlyChars()
        {
            _TObjMilesChkMode = Fun_TObjMilesChkMode.Hook(TObjMilesChkModeHook).Activate();

            if (ConfigV._modConfig.FlightTweaks)
            {
                Util.WriteNop(0x5C5743, 21);
                // Util.WriteNop(0x5C5741, 32);   //remove clear speed once fly is over
                Util.WriteNop(0x5C571D, 0x6); //remove flight timer we will manually update it for convenience due to how it works originally.
                _TMilesExecMove = Fun_MilesExecMove.Hook(TObjMilesExecMoveHook).Activate();
            }

            if (ConfigV._modConfig.CheeseTweaks)
            {
                Util.WriteNop(0x5C3C71, 0x5); //remove PGetBreak so Cream doesn't slow down when using Cheese

                var anim = HeroesVariables.cream_motions.AsRef((ushort)PlayerAnim.Animation_CheeseAttack);
                
                if (anim.speed < 2.5f)
                {
                    anim.speed = 2.5f;
                    Util.WriteDataInArray(creamMtnAddress, anim, (ushort)PlayerAnim.Animation_CheeseAttack);
                }
            }

        }
    }

}
