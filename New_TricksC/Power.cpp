#include "pch.h"

namespace PowerChars
{

    FastStdcallHook<void, TObjPlayer*> TObjKnuxExecMode_h(0x5B9BE0);

    //unused for now as I got feedback that it wasn't great
    float GetTriangleDiveMaxSpd(TObjTeam* t)
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


    void __stdcall TObjKnuxExecMode_r(TObjPlayer* p)
    {

        switch (p->mode)
        {
        case 58:
            PGetAcceleration(p);
            break;
        }

        TObjKnuxExecMode_h.Original(p);
    }

    void Init()
    {
        TObjKnuxExecMode_h.Hook(TObjKnuxExecMode_r);
        if (1 /**ConfigV._modConfig.WidePowerTweaks*/)
        {
            WriteNop(0x5B9FE5, 5); //nope PGetBreak so characters don't slow down
        }

        if (1 /**ConfigV._modConfig.TriangleDiveTweaks*/)
            WriteNop(0x5AECFC, 0x2); //remove anim fan check so Triangle Dive can be used when falling.
    }
}