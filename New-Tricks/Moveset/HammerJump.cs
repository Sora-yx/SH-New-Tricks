using Heroes.SDK.Classes.NativeClasses;
using Heroes.SDK.Definitions.Enums;
using Heroes.SDK.Definitions.Enums.Custom;
using New_Tricks.Characters;
using System.Diagnostics;
using static New_Tricks.HeroesFunc;


namespace New_Tricks.Moveset
{
    public unsafe static class HammerJump
    {

        public unsafe static float getHammerJumpSpd(TObjPlayer* p)
        {
            if (p->pTObjTeam != null)
            {

                switch ((int)p->pTObjTeam->level[0])
                {
                    case 1:
                        return 2.3f;
                    case 2:
                        return 2.6f;
                    case 3:
                        return 2.9f;
                }
            }

            return 2.0f;
        }

        readonly public static short HammerJumpAct = 90;
        readonly public static short HammerJumpMtn = 51;
        public static void RunPhysics(TObjPlayer* p)
        {
            PResetAngle(p);
            PGetAccelerationAir(p);
            PGetSpeed(p);
            PSetPosition(p);
            PResetPosition(p);
        }

        public static void RunChkMode(TObjPlayer* p)
        {
            if (SonicChkInput(p) > 0)
            {
                return;
            }

            if (p->motion == HammerJumpMtn)
            {

                if (p->AnimFrame >= 18.0f)
                {
                    p->spd.y = p->p.jmp_y_spd * getHammerJumpSpd(p);
                }

                return;
            }

            ref var pad = ref HeroesVariables.player_input.AsRef(p->playerNo);

            if ((p->flag & 3) != 0)
            {
                if (PCheckStop(p) > 0)
                {
                    p->motion = 0;
                    p->mode = 0;
                }
                else
                {
                    p->mode = (short)PlayerMode.Running;
                    p->motion = (short)PlayerAnim.Motion_Run;
                }
            }
            else
            {
                if (Amy.CheckHammerFloatInput(p, ref pad))
                    return;
            }
        }

        public static void Init()
        {
            var anim = HeroesVariables.amy_motions.AsRef((ushort)HammerJumpMtn);

            anim.speed = 0.8f;
            anim.mtnmode = 4;
            anim.next = (short)PlayerAnim.Animation_BackFlip;
            Util.WriteDataInArray(Amy.MotionsAddress, anim, (ushort)HammerJumpMtn);


            var flip1 = HeroesVariables.amy_motions.AsRef((ushort)PlayerAnim.Animation_BackFlip);
            flip1.next = (short)PlayerAnim.Animation_SideFlip;
            flip1.mtnmode = 4;
            flip1.speed = 0.5f;
            Util.WriteDataInArray(Amy.MotionsAddress, flip1, (ushort)PlayerAnim.Animation_BackFlip);

            var flip2 = HeroesVariables.amy_motions.AsRef((ushort)PlayerAnim.Animation_SideFlip);
            flip2.mtnmode = 4;
            flip2.next = (short)PlayerAnim.Animation_BackFlip2;
            flip2.speed = 1.0f;
            Util.WriteDataInArray(Amy.MotionsAddress, flip2, (ushort)PlayerAnim.Animation_SideFlip);

            var flip3 = HeroesVariables.amy_motions.AsRef((ushort)PlayerAnim.Animation_BackFlip2);
            flip3.mtnmode = 4;
            flip3.next = (short)PlayerAnim.Animation_SideFlip;
            flip3.speed = 1.0f;
            Util.WriteDataInArray(Amy.MotionsAddress, flip3, (ushort)PlayerAnim.Animation_BackFlip2);

        }
    }
}
