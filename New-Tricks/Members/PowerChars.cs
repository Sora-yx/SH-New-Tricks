using Reloaded.Hooks.Definitions;
using Reloaded.Hooks.Definitions.X86;
using Heroes.SDK.Classes.NativeClasses;
using Heroes.SDK;
using Heroes.SDK.Definitions.Enums.Custom;
using New_Tricks.Configuration;
using New_Tricks.Members;

namespace New_Tricks.Characters
{
    public unsafe class PowerChars
    {
        #region definition
        [Function(CallingConventions.Stdcall)]
        public delegate void TObjKnuxChkMode(TObjPlayer* pwp);
        private IHook<TObjKnuxChkMode> _TObjKnuxChkMode;
        public static IFunction<TObjKnuxChkMode> Fun_TObjKnuxChkMode { get; } = SDK.ReloadedHooks.CreateFunction<TObjKnuxChkMode>(0x5BA2F0);

        [Function(CallingConventions.Stdcall)]
        public delegate void KnuxExecMoveT(TObjPlayer* a1);
        private IHook<KnuxExecMoveT> _TKnuxExecMove;
        public static IFunction<KnuxExecMoveT> Fun_TObjKnuxExecMove { get; } = SDK.ReloadedHooks.CreateFunction<KnuxExecMoveT>(0x5B9BE0);

        #endregion

        private float GetTriangleDiveMaxSpd(TObjTeam* t)
        {
            switch (t->level[2])
            {
                case 1:
                    return 2.6f;
                case 2:
                    return 2.8f;
                case 3:
                    return 3.0f;
            }

            return 2.5f;
        }

        private void TObjKnuxChkModeHook(TObjPlayer* p)
        {
            
  
            bool triangleDive = ConfigV._modConfig.TriangleDiveTweaks;

            ref var pad = ref HeroesVariables.player_input.AsRef(Player.Pno);
            TObjTeam* t = p->pTObjTeam;



            _TObjKnuxChkMode.OriginalFunction(p);
        }

        private void TObjKnuxExecMoveHook(TObjPlayer* p)
        {
           // Console.WriteLine("Knux Mod: " + p->mode);
            switch (p->mode)
            {
                case 58:
                    HeroesFunc.PGetAcceleration(p);
                    break;
            }

            _TKnuxExecMove.OriginalFunction(p);
        }

        public PowerChars()
        {
            _TObjKnuxChkMode = Fun_TObjKnuxChkMode.Hook(TObjKnuxChkModeHook).Activate();
            _TKnuxExecMove = Fun_TObjKnuxExecMove.Hook(TObjKnuxExecMoveHook).Activate();

            if (ConfigV._modConfig.WidePowerTweaks)
            {
                Util.WriteNop(0x5B9FE5, 5); //nope PGetBreak so characters don't slow down
            }

            if (ConfigV._modConfig.TriangleDiveTweaks)
                Util.WriteNop(0x5AECFC, 0x2); //remove anim fan check so Triangle Dive can be used when falling.
        }
    }
}
