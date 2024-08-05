using Heroes.SDK.Definitions.Structures.RenderWare;
using Heroes.SDK.Utilities.Misc;
using Reloaded.Hooks.Definitions;
using Reloaded.Hooks.Definitions.X86;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using static New_Tricks.Sound;
using static Reloaded.Hooks.Definitions.X86.FunctionAttribute;
using static System.Runtime.InteropServices.JavaScript.JSType;
using Heroes.SDK;

namespace New_Tricks
{
    public unsafe static class Sound
    {
        [StructLayout(LayoutKind.Explicit, Size = 0xC)]
        public unsafe struct SE_TABLE
        {
            [FieldOffset(0x0)]
            public ushort seId;
            [FieldOffset(0x2)]
            public sbyte bankNo;
            [FieldOffset(0x3)]
            public sbyte listNo;
            [FieldOffset(0x4)]
            public sbyte volume;
            [FieldOffset(0x5)]
            public byte dist;
            [FieldOffset(0x6)]
            public byte time;
            [FieldOffset(0x7)]
            public byte flag;
            [FieldOffset(0x8)]
            public short db;
            [FieldOffset(0xA)]
            public byte priority;
            [FieldOffset(0xB)]
            public byte dummy;
        }


        [StructLayout(LayoutKind.Explicit, Size = 0x8)]
        public unsafe struct IsndSETbl
        {
            [FieldOffset(0x0)]
            public int num;
            [FieldOffset(0x4)]
            public SE_TABLE* data;
        };

        [StructLayout(LayoutKind.Explicit, Size = 0x3C)]
        public unsafe struct IsndCallSE
        {
            [FieldOffset(0x0)]
            public sbyte handleNum;
            [FieldOffset(0x1)]
            public sbyte bank;
            [FieldOffset(0x2)]
            public sbyte list;
            [FieldOffset(0x3)]
            public byte pri;
            [FieldOffset(0x4)]
            public byte pan;
            [FieldOffset(0x5)]
            public byte span;
            [FieldOffset(0x6)]
            public byte vol;
            [FieldOffset(0x7)]
            public byte volofs;
            [FieldOffset(0x8)]
            public byte volmax;
            [FieldOffset(0x9)]
            public byte ctflg;
            [FieldOffset(0xC)]
            public uint mode;
            [FieldOffset(0x10)]
            public short pitch;
            [FieldOffset(0x12)]
            public short timer;
            [FieldOffset(0x14)]
            public short timermax;
            [FieldOffset(0x16)]
            public ushort playtime;
            [FieldOffset(0x18)]
            public ushort SEID;
            [FieldOffset(0x1C)]
            public uint ptr;
            [FieldOffset(0x20)]
            public RwV3d pos;
            [FieldOffset(0x2C)]
            public float field_30_PCspecific__;
            [FieldOffset(0x30)]
            public float rangedist;
            [FieldOffset(0x34)]
            public float prevdist;
            [FieldOffset(0x38)]
            public SE_TABLE* table;
        };


        [StructLayout(LayoutKind.Explicit, Size = 0xA54)]
        public unsafe struct IsndSE
        {
            [FieldOffset(0x0)]
            public byte isPause;
            [FieldOffset(0x1)]
            public byte nextvoice_pt;
            [FieldOffset(0x2)]
            public byte nextvoice_pt2;
            [FieldOffset(0x3)]
            public byte ringTimer;
            [FieldOffset(0x4)]
            public byte ringSide;
            [FieldOffset(0x5)]
            public byte local_speach;
            [FieldOffset(0x8)]
            public fixed byte sebuf[0x3C * 43]; //IsndCallSE
            [FieldOffset(0xA1C)]
            public int isSndFXOn_HHC;
            [FieldOffset(0xA20)]
            public fixed byte gapA20[4];
            [FieldOffset(0xA24)]
            public fixed byte table_HHC[0x8 * 5]; //IsndSETbl
            [FieldOffset(0xA4C)]
            public fixed byte gapA4C[4];
            [FieldOffset(0xA50)]
            public int field_A50;
        };


        [Function(new[] { Register.eax, Register.edx, Register.eax }, Register.eax, StackCleanup.Callee)]
        public delegate IsndCallSE* IsndCallSET(RwV3d* pos, SE_TABLE* table, byte a3, IsndSE* t, int seId_hhc);
        public static IFunction<IsndCallSET> Fun_IsndNewCall { get; } = SDK.ReloadedHooks.CreateFunction<IsndCallSET>(0x440650);
        public static IsndCallSET IsndNewCall { get; } = Fun_IsndNewCall.GetWrapper();


        public static short IsndSE_GetTblNumFromID(ushort seId_HHC)
        {
            short result = -1;

            switch (seId_HHC >> 12)                     // / 0x1000
            {
                case 1:
                    result = 1;
                    break;
                case 2:
                    result = 2;
                    break;
                case 3:
                    result = 3;
                    break;
            }

            return result;

        }

        public unsafe static void Play(ushort seId_HHC, RwV3d* pos, IsndSE* ptr, byte volMax, int a5)
        {
            return;
            IsndSETbl* curTable;
            short id = IsndSE_GetTblNumFromID(seId_HHC);

            if (id > 0)
            {
                curTable = (IsndSETbl*)&ptr->table_HHC[id];
            }
            else
            {
                return;
            }

            if (seId_HHC >= curTable->num)
                return;

            SE_TABLE* data = curTable->data;
            sbyte list = data[seId_HHC].listNo;
            SE_TABLE* seTable = &data[seId_HHC];

            if (list < 0)
                return;

            IsndCallSE* sndCall = IsndNewCall(pos, seTable, 0, ptr, seId_HHC);
            
            if (sndCall is null)
                return;

            sndCall->mode = 5;

            if (pos is not null)
            {
                sndCall->mode = 0x405;
            }

            sndCall->volmax = volMax;
            sndCall->volofs = volMax;
            sndCall->ptr = (uint)a5;


        }


    }
}
