#include "pch.h"
#include "Amy.h"

namespace HammerJump
{

    float getHammerJumpSpd(TObjPlayer* p)
    {
        if (p->pTObjTeam != nullptr)
        {

            switch ((int)p->pTObjTeam->level[0])
            {
            case 1:
                return 2.3f;
            case 2:
                return 2.6f;
            case 3:
                return 2.9f;
            }
        }

        return 2.0f;
    }

    const short HammerJumpAct = 90;
    const short HammerJumpMtn = 51;

    void RunPhysics(TObjPlayer* p)
    {
        PResetAngle(p);
        PGetAccelerationAir(p);
        PGetSpeed(p);
        PSetPosition(p);
        PResetPosition(p);
    }

    void RunChkMode(TObjPlayer* p)
    {
        if (ChkInputLight(p) > 0)
        {
            return;
        }

        if (p->mm.reqaction == HammerJumpMtn)
        {

            if (p->mm.nframe >= 18.0f)
            {
                p->spd.y = p->p.jmp_y_spd * getHammerJumpSpd(p);
            }

            return;
        }

       auto pad = player_input[p->playerNo];

        if ((p->flag & 3) != 0)
        {
            if (PCheckStop(p) > 0)
            {
                p->mm.reqaction = 0;
                p->mode = 0;
            }
            else
            {
                p->mode = (short)PlayerMode::ModeRunning;
                p->mm.reqaction = (short)PlayerAnim::Motion_Run;
            }
        }
        else
        {
            if (Amy::CheckHammerFloatInput(p))
                return;
        }
    }

    void Init()
    {
        auto anim = &amy_motions[HammerJumpMtn];

        anim->speed = 0.8f;
        anim->mtnmode = 4;
        anim->next = (short)Animation_BackFlip;

        auto flip1 = &amy_motions[Animation_BackFlip];
        flip1->next = Animation_SideFlip;
        flip1->mtnmode = 4;
        flip1->speed = 0.5f;

        auto flip2 = &amy_motions[Animation_SideFlip];
        flip2->mtnmode = 4;
        flip2->next = (short)Animation_BackFlip2;
        flip2->speed = 1.0f;


        auto flip3 = &amy_motions[Animation_BackFlip2];
        flip3->mtnmode = 4;
        flip3->next = (short)Animation_SideFlip;
        flip3->speed = 1.0f;

    }
}