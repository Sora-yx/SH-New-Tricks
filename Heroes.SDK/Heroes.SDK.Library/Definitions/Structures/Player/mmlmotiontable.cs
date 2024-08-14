using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;

namespace Heroes.SDK.Definitions.Structures.Player
{
    [Equals(DoNotAddEqualityOperators = true)]
    [StructLayout(LayoutKind.Explicit, Size = 0x10)]
    public unsafe struct MML_MOTIONTABLE
    {
        [FieldOffset(0x0)]
        int thismotion;
        [FieldOffset(0x4)]
        int id;
        [FieldOffset(0x8)]
        void *ptr;
        [FieldOffset(0xC)]
        void* pARAM;
    }
}
