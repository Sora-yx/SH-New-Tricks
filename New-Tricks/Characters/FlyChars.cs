using Heroes.SDK;
using Heroes.SDK.Classes.NativeClasses;
using Reloaded.Hooks.Definitions;
using Reloaded.Hooks.Definitions.X86;
using Heroes.SDK.API;
using static System.Runtime.InteropServices.JavaScript.JSType;
using System.Runtime.InteropServices;
using New_Tricks.Configuration;
using static Reloaded.Hooks.Definitions.X86.FunctionAttribute;
using Heroes.SDK.Utilities.Misc;
using Heroes.SDK.Definitions.Enums.Custom;


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

        private float GetFlySpd(TObjTeam* t)
        {
            switch (t->level[1]) //1 is flying formation
            {
                case 1:
                    return 0.08f;
                case 2:
                    return 0.1f;
                case 3:
                    return 0.15f;
            }

            return 0.04f;
        }

        private void TObjMilesChkModeHook(TObjPlayer* p)
        {
           // Util.WriteData(flyTimeOffAdd, flyByteNew);
            _TObjMilesChkMode.OriginalFunction(p);


            //Util.WriteData(flyTimeOffAdd, flyByteOrigin);

        }

        private void TObjMilesExecMoveHook(TObjPlayer* p)
        {
            Console.WriteLine("Tails DOTP " + p->dotp);
          //  Console.WriteLine("Tails Cur SMode " + p->smode);
            bool vSpeed = ConfigV._modConfig.IncreaseSpeedCap;
            p->nocontimer = 0;

            if (vSpeed && !Player.isCPU(p))
                Util.WriteData(flyVSpdCapAdd, flyVSpdCapNew);

            if (ConfigV._modConfig.FlightTweaks && p->mode == 52 && HeroesFunc.PCheckPower(null, null, p) != 0)
            {
                p->spd.x += GetFlySpd(p->pTObjTeam);
                if (p->lightDashLastRingPos_HHC.z < 180.0f)
                    p->lightDashLastRingPos_HHC.z += GetFlyTimerIncr(p->pTObjTeam);
            }
            else if (p->mode == 53)
            {
                if (HeroesFunc.PCheckPower(null, null, p) > 0 && p->spd.x < 1.0f)
                {
                    p->spd.x = 4.0f;
                }
                   
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
                byte[] FUCK = { 0x4 };
                //Util.WriteData(0x5C575F, FUCK);
                //Util.WriteNop(0x59AA54, 0x2);

            }


            //byte[] t = { 0x74 };
            //Util.WriteData(0x5C5734, t);
           // Util.WriteNop(0x5C5734, 2);
            //Util.WriteData((nuint)0x5C5725, byteArray);

            // Step 2: Convert the float to a byte array
            //byte[] byteArray = BitConverter.GetBytes(myFloat);
            //Util.WriteData(0x5C5725, (float*)fuck);
        }
    }

}
