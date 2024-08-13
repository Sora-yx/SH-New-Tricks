 using Heroes.SDK.Classes.NativeClasses;
using Heroes.SDK.Definitions.Enums;
using Heroes.SDK.Definitions.Enums.Custom;
using New_Tricks.Configuration;

namespace New_Tricks.Characters
{
    public static class Amy
    {
        static int TornadoTimer = 0;
        public static nuint hoverTimeAddr = 0x5D139E;

        public unsafe static float getHammerJumpSpd(TObjPlayer* p)
        {
            if (p->pTObjTeam != null)
            {

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

        private unsafe static float GetPropSpd(TObjTeam* t)
        {
            switch (t->level[0]) //0 is spd formation
            {
                case 1:
                    return 0.1f;
                case 2:
                    return 0.2f;
                case 3:
                    return 0.3f;
            }

            return 0.05f;
        }

        private unsafe static byte[] GetPropTimer(TObjTeam* t)
        {

      
            byte[] bytes = { 0xF0, 0x0, 0x0, 0x0 }; //240 frames

            switch (t->level[0]) //0 is spd formation
            { 
                case 1:
                    bytes[0] = 0xE0; //swap to 480 frames
                    bytes[1] = 0x1;
                    bytes[2] = 0x0;
                    bytes[3] = 0x0;
                break;
                case 2:
                    bytes[0] = 0x58; //swap to 600 frames
                    bytes[1] = 0x2;
                    bytes[2] = 0x0;
                    bytes[3] = 0x0;
                    break;
                case 3:
                    bytes[0] = 0xD0; //swap to 720 frames
                    bytes[1] = 0x02;
                    bytes[2] = 0x0;
                    bytes[3] = 0x0;
                    break;
            }

            return bytes;
        }


        public unsafe static bool RunAmyChkMode(TObjPlayer* p)
        {
            if (p->characterKind != Character.Amy)
                return false;

            ref var pad = ref HeroesVariables.player_input.AsRef(Player.Pno);

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
                        Util.WriteData(Amy.hoverTimeAddr, GetPropTimer(p->pTObjTeam));

                        if (p->spd.x < 12.0f && HeroesFunc.PCheckPower(null, null, p) != 0)
                            p->spd.x += GetPropSpd(p->pTObjTeam);

                   
                    }
                    break;
                case PlayerMode.Fall:
                    if (ConfigV._modConfig.BetterProp)
                    {
                        if (p->lightDashCountSinceLastRing_HHC == 0 && p->spd.y <= 0.0f && (pad.jump.status & BTN_STATUS.isOn) != 0)
                        {
                            p->mode = 77; // start hammer float check
                            p->motion = 102;
                            p->flag &= 0xFAF;
                            p->spd.y = 0.0f;
                            p->lightDashCountSinceLastRing_HHC = 0;
                            p->grindTimer = 0;
                            return false;
                        }
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
    
                    break;
            }

        }

        public static void Init()
        {
            if (ConfigV._modConfig.BetterProp)
            {
                //prop
                /*byte[] byteArray = new byte[] { 0x3E, 0x7, 0x0, 0x0 };
                Util.WriteData(Amy.hoverTimeAddr, byteArray); //increase Amy Hover timer from 120 frames to 999*/


                Util.WriteNop(0x5CEFC1, 2); //remove anim check for prop
                //Util.WriteNop(0x5CEFE8, 7); //remove reset timer for prop, we will manually set it for convenience.
            }

            if (ConfigV._modConfig.AmyTornadoTweaks)
            {

                Util.WriteData(0x5D13CF, Util.nopFunc); //remove clear speed
                Util.WriteData(0x5D114F, Util.nopFunc); //remove clear speed for Hammer mov
                byte[] byteArray = new byte[] { 0x3C };
                Util.WriteData(0x5D1101, byteArray); //reduce delay to start tornado move
                byteArray[0] = 0x19;
                Util.WriteData(0x5D1160, byteArray); //reduce delay to finish tornado move
            }
        }
    }
}
