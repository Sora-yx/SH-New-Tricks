using System.Runtime.InteropServices;
using Heroes.SDK.Definitions.Structures.RenderWare;

namespace Heroes.SDK.Classes.NativeClasses
{
    [Equals(DoNotAddEqualityOperators = true)]
    [StructLayout(LayoutKind.Explicit, Size = 0x30)]
    public unsafe struct TASKWK
    {
        [FieldOffset(0x0)]
        short mode;
        [FieldOffset(0x2)]
        short modeLast;
        [FieldOffset(0x4)]
        short smode;
        [FieldOffset(0x6)]
        short flag;
        [FieldOffset(0x8)]
        ushort wtimer;
        [FieldOffset(0xC)]
        sAngle ang;
        [FieldOffset(0x18)]
        RwV3d pos;
        [FieldOffset(0x24)]
        RwV3d scl;
    };

}
