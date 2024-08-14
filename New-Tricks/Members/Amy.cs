using Heroes.SDK.Classes.NativeClasses;
using Heroes.SDK.Definitions.Enums;
using Heroes.SDK.Definitions.Enums.Custom;
using New_Tricks.Configuration;
using New_Tricks.Members;
using Reloaded.Hooks.Definitions;
using Reloaded.Hooks.Definitions.X86;
using Heroes.SDK;
using static New_Tricks.HeroesFunc;
using Heroes.SDK.Definitions.Structures.RenderWare.Object;
using Heroes.SDK.Definitions.Structures.RenderWare;

namespace New_Tricks.Characters
{
    public unsafe class Amy
    {
        static public nuint MotionsAddress = 0x8C5E10;
        static int TornadoTimer = 0;
        public static nuint hoverTimeAddr = 0x5D139E;

        public static PlayerAnim[] HoldHammerAnims = { PlayerAnim.Animation_JumpRoll, PlayerAnim.Animation_JumpDash, PlayerAnim.Animation_BackFlip, PlayerAnim.Animation_BackFlip2, PlayerAnim.Animation_SideFlip };

        [Function(CallingConventions.MicrosoftThiscall)]
        public delegate void TObjTriggerAmyHammerT(TObjPlayer* p);
        private IHook<TObjTriggerAmyHammerT> _TObjTrigAmyHamT;
        public static IFunction<TObjTriggerAmyHammerT> Fun_TObjTrigAmyHam { get; } = SDK.ReloadedHooks.CreateFunction<TObjTriggerAmyHammerT>(0x5CCDD0);

        public static short GetHammerAnims(PlayerAnim mtn)
        {
            foreach (var t in HoldHammerAnims)
            {
                if (t == mtn)
                {
                    return (short)t;
                }
            }

            return -1;
        }

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

        private unsafe static float GetPropMaxSpd(TObjTeam* t)
        {
            switch (t->level[0]) //0 is spd formation
            {
                case 1:
                    return 5.0f;
                case 2:
                    return 6.0f;
                case 3:
                    return 7.0f;
            }

            return 4.0f;
        }

        private unsafe static byte[] GetPropTimer(TObjTeam* t)
        {

            byte[] bytes = { 0xF0, 0x0, 0x0, 0x0 }; //240 frames (level 0)

            switch (t->level[0]) //0 is spd formation
            {
                case 1:
                    bytes[0] = 0x2C; //swap to 300 frames
                    bytes[1] = 0x1;
                    bytes[2] = 0x0;
                    bytes[3] = 0x0;
                    break;
                case 2:
                    bytes[0] = 0x68; //swap to 360 frames
                    bytes[1] = 0x1;
                    bytes[2] = 0x0;
                    bytes[3] = 0x0;
                    break;
                case 3:
                    bytes[0] = 0xA4; //swap to 420 frames
                    bytes[1] = 0x01;
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
            var t = p->pTObjTeam;

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
                        Util.WriteData(Amy.hoverTimeAddr, GetPropTimer(t));

                        if (p->spd.x < GetPropMaxSpd(t) && HeroesFunc.PCheckPower(null, null, p) != 0)
                            p->spd.x += GetPropSpd(t);


                    }
                    break;
                case PlayerMode.Fall:
                    if (ConfigV._modConfig.BetterProp)
                    {
                        if (p->motion != (ushort)PlayerAnim.Animation_Trick && p->spd.y <= 0.0f && (pad.jump.status & BTN_STATUS.isOn) != 0)
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

        //hacky way to make Amy's hammer show up on different action because I'm too lazy to rewrite the function
        void TriggerAmyHammerHook(TObjPlayer* p)
        {
            byte mode = (byte)p->mode;
            bool triggered = false;
            if (p->mode < byte.MaxValue && (mode == (byte)PlayerMode.Jumping || mode == (byte)PlayerMode.JumpDash))
            {
                ushort mtn = (ushort)p->motion;
                short hamMtn = GetHammerAnims((PlayerAnim)p->motion);

                if (hamMtn > -1 && mtn == hamMtn)
                {
                    triggered = true;
                    Util.WriteData(0x5CCDEA, mode); //change the action check 
                }
            }

             _TObjTrigAmyHamT.OriginalFunction(p);

            if (triggered)
                Util.WriteData(0x5CCDEA, 0x48); //restore original action check
        }

        public Amy()
        {
            _TObjTrigAmyHamT = Fun_TObjTrigAmyHam.Hook(TriggerAmyHammerHook).Activate();

            if (ConfigV._modConfig.BetterProp)
            {
                //prop
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
