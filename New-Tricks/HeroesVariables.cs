using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Reloaded.Memory.Pointers;
using Heroes.SDK.Definitions.Structures.Input;
using Reloaded.Hooks.Definitions.Structs;
using Heroes.SDK.Definitions.Structures.Player;
using New_Tricks.Characters;

namespace New_Tricks
{
    public unsafe static class HeroesVariables
    {   
        public static FixedArrayPtr<PLAYER_INPUT> player_input { get; } = new FixedArrayPtr<PLAYER_INPUT>((PLAYER_INPUT*)0xA4B298, 8);

        public static Ptr<int> SndSE { get; set; } = new Ptr<int>((int*)0xA2F8B0);


        public static FixedArrayPtr<MML_MOTIONTABLE> player_motions { get; } = new FixedArrayPtr<MML_MOTIONTABLE>((MML_MOTIONTABLE*)0xA47FBC, 777);


        public static FixedArrayPtr<PL_MOTION> sonk_motions { get; } = new FixedArrayPtr<PL_MOTION>((PL_MOTION*)SpeedChars.SonkMotionsAddress, 105);
        public static FixedArrayPtr<PL_MOTION> shadow_motions { get; } = new FixedArrayPtr<PL_MOTION>((PL_MOTION*)SpeedChars.ShadowMotionsAddress, 105);
        public static FixedArrayPtr<PL_MOTION> amy_motions { get; } = new FixedArrayPtr<PL_MOTION>((PL_MOTION*)Amy.MotionsAddress, 105);
        public static FixedArrayPtr<PL_MOTION> espio_motions { get; } = new FixedArrayPtr<PL_MOTION>((PL_MOTION*)SpeedChars.EspioMotionsAddress, 105);


        public static FixedArrayPtr<PL_MOTION> cream_motions { get; } = new FixedArrayPtr<PL_MOTION>((PL_MOTION*)FlyChars.creamMtnAddress, 93);
    }
}
