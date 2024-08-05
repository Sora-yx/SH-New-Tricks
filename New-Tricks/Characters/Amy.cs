using Heroes.SDK.Classes.NativeClasses;
using Heroes.SDK.Definitions.Enums;
using Heroes.SDK.Definitions.Enums.Custom;
using Heroes.SDK.Definitions.Structures.RenderWare;
using New_Tricks.Configuration;

namespace New_Tricks.Characters
{
    public static class Amy
    {
        static int TornadoTimer = 0;

        public unsafe static float getHammerJumpSpd(TObjPlayer* p)
        {
            if (p->pTObjTeam != null)
            {
                /*Console.WriteLine("Team 0 Lvl: " + p->pTObjTeam->level[0]);
                Console.WriteLine("Team 1 Lvl: " + p->pTObjTeam->level[1]);
                Console.WriteLine("Team 2 Lvl: " + p->pTObjTeam->level[2]);     */


                Console.WriteLine("Team No: " + p->pTObjTeam->teamNo);
                Console.WriteLine("Team Kind: " + p->pTObjTeam->teamKind.ToString());
                // Console.WriteLine("Team 2 Lvl: " + p->pTObjTeam->level[2]);
                switch ((int)p->pTObjTeam->level[0])
                {
                    case 1:
                        return 2.0f;
                    case 2:
                        return 3.0f;
                    case 3:
                        return 4.5f;
                }
            }

            return 1.5f;
        }

        public static nuint hoverTimeAddr = 0x5D139E;
        public unsafe static bool RunAmyChkMode(TObjPlayer* p)
        {
            if (p->characterKind != Character.Amy)
                return false;
        
            switch ((PlayerMode)p->mode)
            {
                case PlayerMode.Running:

                    /*if (pad.ButtonFlags.HasFlag(Heroes.SDK.Definitions.Structures.Input.ButtonFlags.CameraL))
                    {
                        if (p->spd.x >= 3.0f)
                            p->spd.y += getHammerJumpSpd(p);
                    }*/
                    break;
                case PlayerMode.HammerFloat:
                    if (ConfigV._modConfig.BetterProp)
                    {
                        if (p->spd.x < 12.0f && p->spd.x > 1.0f)
                            p->spd.x += 0.1f;
                    }
                    break;
            }

            return false;
        }

        public static unsafe void RunAmyExecMode(TObjPlayer* p)
        {

            switch ((PlayerMode)p->mode)
            {
                case PlayerMode.Amy_Tornado:
                    if (ConfigV._modConfig.AmyTornadoTweaks)
                    {
                        if (p->spd.y <= 0.0f)
                            p->spd.y = 0.0f;

                        HeroesFunc.PGetAccelerationAir(p);
                        HeroesFunc.PGetSpeed(p);
                    }
                    break;

                case PlayerMode.HammerFloat:
                    if ( (p->flag & 3) != 0)
                    {
                        Console.WriteLine("ayo");
                    }
                    break;
            }

        }

        public static void Init()
        {
            if (ConfigV._modConfig.BetterProp)
            {
                //prop
                byte[] byteArray = new byte[] { 0x3E, 0x7 };
                Util.WriteData(Amy.hoverTimeAddr, byteArray); //increase Amy Hover timer from 120 frames to 999
            }

            if (ConfigV._modConfig.AmyTornadoTweaks)
            {
                Util.WriteData(0x5D13CF, Util.nopFunc); //remove clear speed
                Util.WriteData(0x5D114F, Util.nopFunc); //remove clear speed for Hammer mov
                byte[] byteArray =  new byte[] { 0x3C }; 
                Util.WriteData(0x5D1101, byteArray); //reduce delay to start tornado move
                byteArray[0] = 0x19; 
                Util.WriteData(0x5D1160, byteArray); //reduce delay to finish tornado move
            }
        }
    }
}
