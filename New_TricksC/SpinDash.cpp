#include "pch.h"
#include "speed.h"

namespace SpinDash
{


  // static float spindashChargeSpd[] = {0.0f, 0.0f, 0.0f, 0.0f};
   static float spindashChargeTimer[] = {0.0f, 0.0f, 0.0f, 0.0f};

    void ResetSpinDashValues(const uint8_t pno)
    {
 
        spindashChargeTimer[pno] = 0;
    }

    float GetSpinDashSpdMultiplier(TObjTeam* t)
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

    bool Charge(TObjPlayer* p)
    {
        uint8_t pno = p->playerNo;

        if (TObjSonicChkInput((TObjSonic*)p) || CheckBeInTheAir(p))
        {
            ResetSpinDashValues(pno);
            p->flag &= 0xFFFFDFFF;
            return true;
        }


        if ((player_input[pno].action.status & isOn) != 0)
        {
            spindashChargeTimer[pno]++;
            if (p->field_EC < 10.0f * GetSpinDashSpdMultiplier(p->pTObjTeam)) //sa1 originally stop at 10, but it feels slow in Heroes.
            {
                p->field_EC += 0.40f;
            }
        }
        else
        {
            p->lightDashCountSinceLastRing_HHC = 0;
            p->mode = SpinDash::ActRelease;
            p->spd.x = p->field_EC;


            if (SndSE)
                IsndSEPlay(8294, &p->position, SndSE, 0, 0);

            ResetSpinDashValues(pno);
            return true;
        }

        if (spindashChargeTimer[pno] >= 100.0f)
        {
            ResetSpinDashValues(pno);
            if (p->spd.x > 0.0f)
            {
                p->mode = PlayerMode::ModeRunning;
                p->mm.reqaction = 6;
                p->flag &= 0xFFFFDFFF;
            }
            else
            {
                p->flag &= 0xFFFFDFFF;
                p->mode = PlayerMode::ModeWait;
                p->idleTime = 0;
                p->mm.reqaction = 0;
            }
        }

        return true;
    }

    bool Release_(TObjPlayer* p)
    {
        if (TObjSonicChkInput((TObjSonic*)p))
        {
            return true;
        }

        if ((p->flag & PL_FLAG_PATH) != 0) 
        {
            p->mode = 14;
            return true;
        }

        if (CheckBeInTheAir(p) > 0)
        {
            int flag = p->flag & 0xFFFFDFFF | 0x500;
            p->mm.reqaction = 9;
            p->field_EC = 5.0f;
            p->flag = flag;
            return true;
        }

        if (SonicCheckJump(p) > 0)
        {
            p->flag &= 0xFFFFDFFF; 
            return true;
        }

        if (PlayerCheckSlowSpinSpinDash(p))
        {
            PChangeRunningMotion(p);
            p->flag &= 0xFFFFFAFF;
        }

        return true;
    }

    void SetDefaultChargeSpd(TObjPlayer* p)
    {
        spindashChargeTimer[p->playerNo] = 0;
        p->field_EC = p->spd.x <= 2.0f ? 2.0f : p->spd.x;
    }

    void RunChargePhysics(TObjPlayer* p)
    {
        PGetRotation(p);
        PGetBreak(p);
        RunCommonPhysics(p);
        SetEffectObi(0);
    }

    void RunReleasePhysics(TObjPlayer* p)
    {
        PGetRotation(p);
        PGetInertia(p);
        RunCommonPhysics(p);

        if (p->mm.action == 10 || p->mm.reqaction == 10)
        {
            SetEffectObi(0);
        }
    }

    void Init() //make jump ball anim loop instead of being based on speed
    {
        if (isSpinDashAllowed(Char_Sonic))
        {
            auto anim = &sonic_motions[10];
            if (anim && anim->mtnmode == 10)
            {
                anim->mtnmode = 3;
            }
        }

        if (isSpinDashAllowed(Char_Shadow))
        {
            auto anim = &shadow_motions[10];
            if (anim && anim->mtnmode == 10)
            {
                anim->mtnmode = 3;
            }
        }

        if (isSpinDashAllowed(Char_Amy))
        {
            auto anim = &amy_motions[10];
            if (anim && anim->mtnmode == 10)
            {
                anim->mtnmode = 3;
            }
        }

        if (isSpinDashAllowed(Char_Espio))
        {
            auto anim = &espio_motions[10];
            if (anim && anim->mtnmode == 10)
            {
                anim->mtnmode = 3;
            }
        }
    }
}