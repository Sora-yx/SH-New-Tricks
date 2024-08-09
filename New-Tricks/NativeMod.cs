using Heroes.SDK.Classes.NativeClasses;
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace New_Tricks
{

    public class NativeMod
    {
 
        private static IntPtr pDll { get; set; } = IntPtr.Zero;

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern IntPtr LoadLibrary(string dllToLoad);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern IntPtr GetProcAddress(IntPtr hModule, string procedureName);

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool FreeLibrary(IntPtr hModule);

        static string path = Path.GetFullPath(Path.Combine(Environment.CurrentDirectory, "TricksC.dll"));


        // Import the InitializeOutput function from the C++ DLL
        [DllImport("TricksC.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void InitializeOutput();

        // Import the PrintMessage function from the C++ DLL
        [DllImport("TricksC.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void PrintMessage(string message);

        [DllImport("TricksC.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void PrintVar(string message);

        [DllImport("TricksC.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ReloadedStart();

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate void InitializeOutputDelegate();

        public static void CallFunc(string name)
        {
            IntPtr pAddressOfFunctionToCall = GetProcAddress(pDll, name);
            InitializeOutputDelegate initializeOutput = (InitializeOutputDelegate)Marshal.GetDelegateForFunctionPointer(
            pAddressOfFunctionToCall, typeof(InitializeOutputDelegate));
            initializeOutput();
        }

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        private delegate int InitializeOutputDelegateInt();

        public static int CallFuncInt(string name)
        {
            IntPtr pAddressOfFunctionToCall = GetProcAddress(pDll, name);
            InitializeOutputDelegateInt initializeOutput = (InitializeOutputDelegateInt)Marshal.GetDelegateForFunctionPointer(
            pAddressOfFunctionToCall, typeof(InitializeOutputDelegateInt));
            return initializeOutput();
        }

        [DllImport("TricksC.dll", CallingConvention = CallingConvention.Cdecl)]
        public static unsafe extern int TobjSonicCheckInput_r(void* p);


        public NativeMod(string directoryFolder)
        {
            InitializeOutput();
        }
    }
}
