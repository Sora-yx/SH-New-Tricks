using Heroes.SDK.Classes.NativeClasses;
using Reloaded.Hooks.Definitions;
using Reloaded.Hooks.Definitions.X86;
using static Reloaded.Hooks.Definitions.X86.FunctionAttribute;
using Heroes.SDK;
using Heroes.SDK.Definitions.Structures.Player;
using System.Diagnostics;
using Reloaded.Memory;
using System.Runtime.InteropServices;
using New_Tricks.Characters;

namespace New_Tricks.Members
{
    public unsafe class Player
    {
        #region variable

  
        static public byte Pno = 0; //todo find a way to get pno properly

        public unsafe static bool isCPU(TObjPlayer* p)
        {
            return p != null && (p->item & 0x1000) != 0;
        }

        #endregion


    }
}
