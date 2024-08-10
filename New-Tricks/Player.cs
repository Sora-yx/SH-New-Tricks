using Heroes.SDK.Classes.NativeClasses;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace New_Tricks
{
    public static class Player
    {
        #region variable

        static public byte Pno = 0; //todo find a way to get pno properly

        public unsafe static bool isCPU(TObjPlayer* p)
        {
            return (p != null && (p->item & 0x1000) != 0);
        }

        #endregion
    }
}
