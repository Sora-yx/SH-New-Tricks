using Reloaded.Hooks.Definitions;
using Reloaded.Hooks.Definitions.X86;
using Heroes.SDK;
using Heroes.SDK.Classes.NativeClasses;
using Heroes.SDK.Definitions.Enums;
using Heroes.SDK.Definitions.Enums.Custom;

namespace New_Tricks.Members
{
    public unsafe class Team
    {
        [Function(CallingConventions.MicrosoftThiscall)]
        public delegate void TeamExecT(TObjTeam* a1);
        private IHook<TeamExecT> _TeamExec;
        public static IFunction<TeamExecT> Fun_TeamExec { get; } = SDK.ReloadedHooks.CreateFunction<TeamExecT>(0x5B10E0);


        private void TObjTeamHook(TObjTeam* t)
        {
            //Console.WriteLine("Team Mode " + t->formationNo);

            TObjPlayer* p = t->playerPtr2;
            ref var pad = ref HeroesVariables.player_input.AsRef(Player.Pno);
            switch (t->teamplayMode)
            {
                case ENUM_TEAMPLAY_MODE.TEAM_MODE_FORMATION:
                    if (p->mode == (short)PlayerMode.Fall)
                    {
                        if ((pad.jump.status & BTN_STATUS.isOn) != 0)
                        {
                            //t->teamplayMode = ENUM_TEAMPLAY_MODE.TEAM_MODE_TRIANGLE_DIVE;
                            //HeroesFunc.PModeChangeToTriangleDive(p);
                            //t->formationNo = 5;
                        }
                    }
                    break;


            }

            _TeamExec.OriginalFunction(t);
        }

        public Team() 
        {
            _TeamExec = Fun_TeamExec.Hook(TObjTeamHook).Activate();
        }
    }
}
