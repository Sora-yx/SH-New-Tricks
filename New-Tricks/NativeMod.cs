using Heroes.SDK.Classes.NativeClasses;
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace New_Tricks
{

    public class NativeMod
    {

        [DllImport("New_TricksC.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void InitializeOutput();


        [DllImport("New_TricksC.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ReloadedStart();



        public NativeMod()
        {
     
            InitializeOutput();
            ReloadedStart();
        }
    }
}
