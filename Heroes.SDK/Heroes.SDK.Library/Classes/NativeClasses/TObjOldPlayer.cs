using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using Heroes.SDK.Definitions.Structures.Player;
using Heroes.SDK.Definitions.Structures.RenderWare;
using Heroes.SDK.Definitions.Enums;
using Heroes.SDK.Definitions.Structures.RenderWare.Camera;

namespace Heroes.SDK.Classes.NativeClasses
{
    [Equals(DoNotAddEqualityOperators = true)]
    [StructLayout(LayoutKind.Explicit, Size = 0xA80)]
    public unsafe struct TObjOldPlayer
    {
        [FieldOffset(0x0)]
        public byte PARAM_SFA; // offset 0xA7C, size 0x1
        [FieldOffset(0xC0)]
        public PL_NODE_PARAMETER left_hand; // offset 0xC0, size 0x70
        [FieldOffset(0x130)]
        public PL_NODE_PARAMETER right_hand; // offset 0x130, size 0x70
        [FieldOffset(0x1A0)]
        public PL_NODE_PARAMETER waist; // offset 0x1A0, size 0x70
        [FieldOffset(0x210)]
        public PL_NODE_PARAMETER left_foot; // offset 0x210, size 0x70
        [FieldOffset(0x280)]
        public PL_NODE_PARAMETER right_foot; // offset 0x280, size 0x70
        [FieldOffset(0x2F0)]
        public PL_NODE_PARAMETER tail; // offset 0x2F0, size 0x70
        [FieldOffset(0x360)]
        public PL_NODE_PARAMETER head; // offset 0x360, size 0x70
        [FieldOffset(0x3D0)]
        public PL_NODE_PARAMETER mune; // offset 0x3D0, size 0x70
        [FieldOffset(0x440)]
        public PL_NODE_PARAMETER mouth; // offset 0x440, size 0x70
        [FieldOffset(0x4B0)]
        public PL_NODE_PARAMETER left_ear; // offset 0x4B0, size 0x70
        [FieldOffset(0x520)]
        public PL_NODE_PARAMETER right_ear; // offset 0x520, size 0x70
        [FieldOffset(0x590)]
        public PL_NODE_PARAMETER upper_jaw; // offset 0x590, size 0x70
        [FieldOffset(0x600)]
        public PL_NODE_PARAMETER lower_jaw; // offset 0x600, size 0x70
        [FieldOffset(0x67C)]
        public int destination_jump_prohibit_flag; // offset 0x67C, size 0x4
        [FieldOffset(0x680)]
        public RwV3d destination_jump_tried_pos; // offset 0x680, size 0xC
        [FieldOffset(0x68C)]
        public RwV3d formation_target_pos; // offset 0x68C, size 0xC
        [FieldOffset(0x698)]
        public int target_pos_ground_poly_group_no; // offset 0x698, size 0x4
        [FieldOffset(0x69C)]
        public float stop_moving_rad; // offset 0x69C, size 0x4
        [FieldOffset(0x6A0)]
        public float not_start_moving_rad; // offset 0x6A0, size 0x4
        [FieldOffset(0x6A4)]
        public float distance_xz_to_target_pos; // offset 0x6A4, size 0x4
        [FieldOffset(0x6A8)]
        public float distance_to_target_pos; // offset 0x6A8, size 0x4
        [FieldOffset(0x6AC)]
        public RwV3d vector_to_target_pos; // offset 0x6AC, size 0xC
        [FieldOffset(0x6B8)]
        public ENUM_CHAR_MODE char_mode; // offset 0x6B8, size 0x4
        [FieldOffset(0x6BC)]
        public ENUM_CHAR_MODE char_mode_previous; // offset 0x6BC, size 0x4
        [FieldOffset(0x6C0)]
        public ENUM_CHAR_MODE char_mode_reserve; // offset 0x6C0, size 0x4
        [FieldOffset(0x6C4)]
        public byte break_R_splash; // offset 0x6C4, size 0x1
        [FieldOffset(0x6C5)]
        public byte break_L_splash; // offset 0x6C5, size 0x1
        [FieldOffset(0x6C6)]
        public byte break_R_footprint; // offset 0x6C6, size 0x1
        [FieldOffset(0x6C7)]
        public byte break_L_footprint; // offset 0x6C7, size 0x1
        [FieldOffset(0x6C8)]
        public byte soaked_foot; // offset 0x6C8, size 0x1
        [FieldOffset(0x6C9)]
        public byte cntHome; // offset 0x6C9, size 0x1
        [FieldOffset(0x6CA)]
        public short tmHome; // offset 0x6CA, size 0x2
        [FieldOffset(0x6CC)]
        public short tmHomeCancel; // offset 0x6CC, size 0x2
        [FieldOffset(0x6D4)]
        public sAngle ang3_FlyFormationDisp; // offset 0x6D4, size 0xC
        [FieldOffset(0x6E0)]
        public sAngle ang3spd_FlyFormationDisp; // offset 0x6E0, size 0xC
        [FieldOffset(0x6EC)]
        public sAngle ang3aim_FlyFormationDisp; // offset 0x6EC, size 0xC
        [FieldOffset(0x6F8)]
        public short grind_time; // offset 0x6F8, size 0x2
        [FieldOffset(0x6FC)]
        public float grind_blend; // offset 0x6FC, size 0x4
        [FieldOffset(0x700)]
        public short fireball_time; // offset 0x700, size 0x2
        [FieldOffset(0x702)]
        public short fireball_rotate; // offset 0x702, size 0x2
        [FieldOffset(0x704)]
        public float fireball_radius; // offset 0x704, size 0x4
        [FieldOffset(0x718)]
        public short tornado_time; // offset 0x718, size 0x2
        [FieldOffset(0x71A)]
        public short tornado_rotate; // offset 0x71A, size 0x2
        [FieldOffset(0x71C)]
        public float tornado_radius; // offset 0x71C, size 0x4
        [FieldOffset(0x720)]
        public RwV3d tornado_center; // offset 0x720, size 0xC
        [FieldOffset(0x72C)]
        public float konohagakure_alpha; // offset 0x72C, size 0x4
        [FieldOffset(0x730)]
        public byte konohagakure; // offset 0x730, size 0x1
        [FieldOffset(0x731)]
        public byte trianglejump_enable; // offset 0x731, size 0x1
        [FieldOffset(0x732)]
        public short triangledive_time; // offset 0x732, size 0x2
        [FieldOffset(0x734)]
        public float triangledive_float; // offset 0x734, size 0x4
        [FieldOffset(0x738)]
        public int angy_Head; // offset 0x738, size 0x4
        [FieldOffset(0x73C)]
        public int paralysed_time; // offset 0x73C, size 0x4
        [FieldOffset(0x740)]
        public RwMatrixTag mat_event_shadow; // offset 0x740, size 0x40
        [FieldOffset(0x780)]
        public TASKWK taskwk; // offset 0x780, size 0x30
        [FieldOffset(0x7B0)]
        public MOTIONWK motionwk; // offset 0x7B0, size 0x40
        [FieldOffset(0x7F0)]
        public PLAYERWK playerwk; // offset 0x7F0, size 0x288
        [FieldOffset(0xA78)]
        public byte collide_against_wall; // offset 0xA78, size 0x1
        [FieldOffset(0xA79)]
        public byte collide_mentori; // offset 0xA79, size 0x1
        [FieldOffset(0xA7A)]
        public byte changing_path; // offset 0xA7A, size 0x1
        [FieldOffset(0xA7B)]
        public byte timerVoiceSE; // offset 0xA7B, size 0x1
    }
}
