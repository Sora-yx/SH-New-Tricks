using System.Runtime.InteropServices;
using Heroes.SDK.Definitions.Structures.Player;
using Heroes.SDK.Definitions.Structures.RenderWare;
using Heroes.SDK.Definitions.Enums.Custom;
using Heroes.SDK.Definitions.Enums;

namespace Heroes.SDK.Classes.NativeClasses
{
    [StructLayout(LayoutKind.Explicit, Size = 0x288)]
    public unsafe struct PLAYERWK
    {
        [FieldOffset(0x0)]
        public char playerno; // offset 0x0, size 0x1
        [FieldOffset(0x1)]
        public char characterno; // offset 0x1, size 0x1
        [FieldOffset(0x2)]
        public char suitno; // offset 0x2, size 0x1
        [FieldOffset(0x3)]
        public char appearanceno; // offset 0x3, size 0x1
        [FieldOffset(0x4)]
        public fixed char selectable_mode[8]; // offset 0x4, size 0x8
        [FieldOffset(0xC)]
        public char selectable_mode_num; // offset 0xC, size 0x1
        [FieldOffset(0xD)]
        public char select_mode; // offset 0xD, size 0x1
        [FieldOffset(0xE)]
        public char selected_mode; // offset 0xE, size 0x1
        [FieldOffset(0x10)]
        public short item; // offset 0x10, size 0x2
        [FieldOffset(0x12)]
        public short jumptimer; // offset 0x12, size 0x2
        [FieldOffset(0x14)]
        public short nocontimer; // offset 0x14, size 0x2
        [FieldOffset(0x16)]
        public short breathtimer; // offset 0x16, size 0x2
        [FieldOffset(0x18)]
        public short waittimer; // offset 0x18, size 0x2
        [FieldOffset(0x1A)]
        public short confutimer; // offset 0x1A, size 0x2
        [FieldOffset(0x1C)]
        public short flag; // offset 0x1C, size 0x2
        [FieldOffset(0x1E)]
        public short path_point; // offset 0x1E, size 0x2
        [FieldOffset(0x20)]
        public int equipment; // offset 0x20, size 0x4
        [FieldOffset(0x24)]
        public int input_val; // offset 0x24, size 0x4
        [FieldOffset(0x28)]
        public int slant_run; // offset 0x28, size 0x4
        [FieldOffset(0x2C)]
        public float hpos; // offset 0x2C, size 0x4
        [FieldOffset(0x30)]
        public float dotp; // offset 0x30, size 0x4
        [FieldOffset(0x34)]
        public float accel; // offset 0x34, size 0x4
        [FieldOffset(0x38)]
        public float force; // offset 0x38, size 0x4
        [FieldOffset(0x3C)]
        public float frict; // offset 0x3C, size 0x4
        [FieldOffset(0x40)]
        public float framespeed; // offset 0x40, size 0x4
        [FieldOffset(0x44)]
        public float HP; // offset 0x44, size 0x4
        [FieldOffset(0x48)]
        public RwV3d eff; // offset 0x48, size 0xC
        [FieldOffset(0x54)]
        public RwV3d acc; // offset 0x54, size 0xC
        [FieldOffset(0x60)]
        public RwV3d spd; // offset 0x60, size 0xC
        [FieldOffset(0x6C)]
        public RwV3d wall_normal; // offset 0x6C, size 0xC
        [FieldOffset(0x78)]
        public RwV3d floor_normal; // offset 0x78, size 0xC
        [FieldOffset(0x84)]
        public RwV3d ceiling_normal; // offset 0x84, size 0xC
        [FieldOffset(0x90)]
        public int attr; // offset 0x90, size 0x4
        [FieldOffset(0x94)]
        public int last_attr; // offset 0x94, size 0x4
        [FieldOffset(0x98)]
        public int attr_wall; // offset 0x98, size 0x4
        [FieldOffset(0x9C)]
        public int last_attr_wall; // offset 0x9C, size 0x4
        [FieldOffset(0xA0)]
        public int attr_ceiling; // offset 0xA0, size 0x4
        [FieldOffset(0xA4)]
        public int last_attr_ceiling; // offset 0xA4, size 0x4
        [FieldOffset(0xA8)]
        public short poly_no; // offset 0xA8, size 0x2
        [FieldOffset(0xAC)]
        public RwV3d vUp; // offset 0xAC, size 0xC
        [FieldOffset(0xB8)]
        public RwV3d vAt; // offset 0xB8, size 0xC
        [FieldOffset(0xC8)]
        public Physics p; // offset 0xC8, size 0x84
        [FieldOffset(0x14C)]
        public mtnmanwk mm; // offset 0x14C, size 0x70
        [FieldOffset(0x1BC)]
        public mtnmanwk mm_sub; // offset 0x1BC, size 0x70
        [FieldOffset(0x22C)]
        public PLAYER_VCOLLI shadow; // offset 0x22C, size 0x24
        [FieldOffset(0x250)]
        public ENUM_TEAM_ROLE role; // offset 0x250, size 0x4
        [FieldOffset(0x254)]
        public ENUM_PLAYER_TYPE player_type; // offset 0x254, size 0x4
        [FieldOffset(0x25C)]
        public byte teamNo; // offset 0x25C, size 0x1
        [FieldOffset(0x25D)]
        public byte memberNo; // offset 0x25D, size 0x1
        [FieldOffset(0x25E)]
        public byte controllerNo; // offset 0x25E, size 0x1
        [FieldOffset(0x25F)]
        public byte modeFinishedFlag; // offset 0x25F, size 0x1
        [FieldOffset(0x260)]
        public float accelMax; // offset 0x260, size 0x4
        [FieldOffset(0x264)]
        public float speedMax; // offset 0x264, size 0x4
        [FieldOffset(0x268)]
        public int polyGroupNo; // offset 0x268, size 0x4
        [FieldOffset(0x26C)]
        public int parabolicJumpRemainingTime; // offset 0x26C, size 0x4
        [FieldOffset(0x270)]
        public RwV3d parabolicJumpExpectLandingPos; // offset 0x270, size 0xC
        [FieldOffset(0x27C)]
        public RwV3d parabolicJumpV; // offset 0x27C, size 0xC
    }
}
