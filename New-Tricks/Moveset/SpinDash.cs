using Heroes.SDK;
using Heroes.SDK.Classes.NativeClasses;
using Reloaded.Hooks.Definitions;
using Reloaded.Hooks.Definitions.X86;
using Heroes.SDK.API;
using Heroes.SDK.Definitions.Enums.Custom;
using Heroes.SDK.Definitions.Enums;
using static New_Tricks.HeroesFunc;
using Reloaded.Memory.Pointers;

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

        static public bool Charge(TObjPlayer* p)
        {
            ref var pad = ref HeroesVariables.player_input.AsRef(Player.Pno);
            if ((pad.action.status & BTN_STATUS.isOn) != 0)
            {
                Console.WriteLine("Charge Spin Dash...");
                spindashChargeTimer[Player.Pno]++;
                if (spindashChargeSpd[Player.Pno] < 10.0f * 1.6) //sa1 originally stop at 10, but it feels slow in Heroes.
                {
                    spindashChargeSpd[Player.Pno] += 0.40f;
                }
            }
            else
            {
                p->mode = (UInt16)Act.Release;
                p->spd.x = spindashChargeSpd[Player.Pno];

                if (p->spd.x >= 10.0f)
                {
                    var rng = new Random();
                    int res = rng.Next(0, 2);
                    if (res >= 1)
                    {
                        //SetEffDash(Player.Pno);
                        //SetRocketHit((byte)p->characterKind);
                        p->spd.x += 2.0f;
                    }
                }

                Sound.IsndSE* ptr = (Sound.IsndSE*)HeroesVariables.SndSE.Get();
                if (ptr is not null)
                    IsndSEPlay(8294, &p->position, ptr, 0, 0);

                return true;
            }

            if (spindashChargeTimer[Player.Pno] >= 300.0f)
            {
                spindashChargeTimer[Player.Pno] = 0;
                spindashChargeSpd[Player.Pno] = 0;
                if (p->spd.x > 0.0f)
                {
                    p->mode = 14;
                    p->motion = 6;
                    return false;
                }
                else
                {
                    p->mode = 0;
                    p->motion = 0;
                    return false;
                }
            }

            return true;
        }

        static public bool Release(TObjPlayer* p)
        {
            if (CheckBeInTheAir(p) > 0)
            {
                p->motion = 9;
                p->field_EC = 5.0f;
                p->statusRelated0x1B8 = (int)(p->statusRelated0x1B8 & 0xFFFFDFFF | 0x500);
                spindashChargeSpd[Player.Pno] = 0;
                return false;
            }

            if (SonicCheckJump(p) > 0)
            {
                p->statusRelated0x1B8 &= 0xFFFFdf;
                spindashChargeSpd[Player.Pno] = 0;
                return false;
            }

            if (PlayerCheckSlowSpin(p))
            {
                p->statusRelated0x1B8 &= 0xFFFFFA;
                spindashChargeSpd[Player.Pno] = 0;
                return false;
            }

            ref var pad = ref HeroesVariables.player_input.AsRef(Player.Pno);
            if ((pad.action.status & BTN_STATUS.isPress) != 0) //pressed
            {
                Console.WriteLine("Cancelled Spin Dash...");
                p->statusRelated0x1B8 &= 0xFFFFFA;
                p->mode = 14;
                PChangeRunningMotion(p);
                spindashChargeSpd[Player.Pno] = 0;
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
