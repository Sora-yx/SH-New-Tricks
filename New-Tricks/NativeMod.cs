using Reloaded.Mod.Interfaces;
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;


namespace New_Tricks
{

    public class NativeMod
    {
        const string modName = "New_TricksC.dll";

        [DllImport(modName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void InitializeOutput();


        [DllImport(modName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ReloadedStart();


        public NativeMod()
        {
            InitializeOutput();
            ReloadedStart();
        }
    }
}
