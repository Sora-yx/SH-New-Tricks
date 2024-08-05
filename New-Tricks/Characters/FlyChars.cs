using Heroes.SDK;
using Heroes.SDK.Classes.NativeClasses;
using Reloaded.Hooks.Definitions;
using Reloaded.Hooks.Definitions.X86;
using Heroes.SDK.API;
using static System.Runtime.InteropServices.JavaScript.JSType;


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

        static private nuint flyTimeOff = 0x789FE4;
        static public float myFloat = 180.0f * 4.0f;
        static readonly byte[] flyByteOrigin = { 0x0, 0x0, 0x34, 0x43 };

        #endregion

        public void TObjMilesChkModeHook(TObjPlayer* p)
        {
            _TObjMilesChkMode.OriginalFunction(p);

        }

        public FlyChars()
        {
            _TObjMilesChkMode = Fun_TObjMilesChkMode.Hook(TObjMilesChkModeHook).Activate();

  
       
            //Util.WriteData((nuint)0x5C5725, byteArray);

            // Step 2: Convert the float to a byte array
            //byte[] byteArray = BitConverter.GetBytes(myFloat);
            //Util.WriteData(0x5C5725, (float*)fuck);
        }
    }

}
