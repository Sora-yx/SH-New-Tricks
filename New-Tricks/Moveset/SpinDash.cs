using Heroes.SDK.Classes.NativeClasses;
using Heroes.SDK.Definitions.Enums;
using static New_Tricks.HeroesFunc;

namespace New_Tricks.Moveset
{
    public unsafe static class SpinDash
    {
        public enum Act
        {
            Charge = 0x1,
            Release = 0x36
        };

        public static float[] spindashChargeSpd = { 0.0f, 0.0f, 0.0f, 0.0f };
        public static float[] spindashChargeTimer = { 0.0f, 0.0f, 0.0f, 0.0f };

        private static void ResetSpinDashValues(byte pno)
        {
            spindashChargeSpd[pno] = 0; 
            spindashChargeTimer[pno] = 0;
        }

        private unsafe static float GetSpinDashSpdMultiplier(TObjTeam* t)
        {
            switch (t->level[0])
            {
                case 1:
                    return 1.3f;
                case 2:
                    return 1.4f;
                case 3:
                    return 1.5f;
            }

            return 1.2f;
        }

        static public bool Charge(TObjPlayer* p)
        {
            byte pno = p->playerNo;
            ref var pad = ref HeroesVariables.player_input.AsRef(pno);
            if ((pad.action.status & BTN_STATUS.isOn) != 0)
            {

                spindashChargeTimer[pno]++;
                if (spindashChargeSpd[pno] < 10.0f * GetSpinDashSpdMultiplier(p->pTObjTeam)) //sa1 originally stop at 10, but it feels slow in Heroes.
                {
                    spindashChargeSpd[pno] += 0.40f;
                }
            }
            else
            {
                p->mode = (Int16)Act.Release;
                p->spd.x = spindashChargeSpd[pno];

                Sound.IsndSE* ptr = (Sound.IsndSE*)HeroesVariables.SndSE.Get();
                if (ptr is not null)
                    IsndSEPlay(8294, &p->position, ptr, 0, 0);

                ResetSpinDashValues(pno);
                return true;
            }

            if (spindashChargeTimer[pno] >= 100.0f)
            {
                ResetSpinDashValues(pno);
                if (p->spd.x > 0.0f)
                {
                    p->mode = 14;
                    p->motion = 6;
                    p->flag &= 0xDFF;
                    return false;
                }
                else
                {
                    p->flag &= 0xDFF;
                    p->smode = 0;
                    p->mode = 0;
                    p->motion = 0;
                    return true;
                }
            }

            return true;
        }

        static public bool Release(TObjPlayer* p)
        {

            if (SonicChkInput(p) > 0)
            {
                return true;
            }

            if (CheckBeInTheAir(p) > 0)
            {
                p->motion = 9;
                p->field_EC = 5.0f;
                p->flag &= 0xDFF;
                return false;
            }

            if (SonicCheckJump(p) > 0)
            {
                p->flag &= 0x400; //needed to make jumpball aura show up for some weird ass reason
                return true;
            }

            if (PlayerCheckSlowSpin(p))
            {
                p->flag &= unchecked((short)(0xFAFF));
                return false;
            }

            ref var pad = ref HeroesVariables.player_input.AsRef(Player.Pno);
            if ((pad.action.status & BTN_STATUS.isPress) != 0) //pressed
            {
                p->flag &= 0x500;
                p->mode = 14;
                PChangeRunningMotion(p);
                p->flag &= 0x500;

                return true;
            }


            return true;
        }

        public unsafe static void SetDefaultChargeSpd(TObjPlayer* p)
        {
            spindashChargeTimer[Player.Pno] = 0;
            spindashChargeSpd[Player.Pno] = p->spd.x <= 2.0f ? 2.0f : p->spd.x;
        }
    }
}
