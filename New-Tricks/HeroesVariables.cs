using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Reloaded.Memory.Pointers;
using Heroes.SDK.Definitions.Structures.Input;
using Reloaded.Hooks.Definitions.Structs;

namespace New_Tricks
{
    public unsafe static class HeroesVariables
    {   
        public static FixedArrayPtr<PLAYER_INPUT> player_input { get; } = new FixedArrayPtr<PLAYER_INPUT>((PLAYER_INPUT*)0xA4B298, 8);

        public static Ptr<int> SndSE { get; set; } = new Ptr<int>((int*)0xA2F8B0);     
    }
}
