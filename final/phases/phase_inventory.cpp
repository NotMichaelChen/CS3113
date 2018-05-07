#include "phase_inventory.hpp"

#include "global.hpp"
#include "phase_beginner.hpp"
#include "phase_intermediate.hpp"

bool beginnerBoss(BossEntity* boss, float elapsed) {
    PhaseData* data = &(boss->data);

    if((data->phaseticks > Global::PHASE_LENGTH && data->phasenum == 0) ||
        (data->phaseticks > Global::PHASE_LENGTH * 2 && data->phasenum == 1) ||
        (data->phaseticks > Global::PHASE_LENGTH * 3 && data->phasenum == 2))
    {
        data->phasenum++;
        data->localticks = 0;
    }

    switch(data->phasenum) {
        case 0:
            beginnerPhaseOne(boss, elapsed);
            break;
        case 1:
            beginnerPhaseTwo(boss, elapsed);
            break;
        case 2:
            beginnerPhaseThree(boss, elapsed);
            break;
        //Time to switch bosses
        default:
            return true;
    }

    return false;
}

bool intermediateBoss(BossEntity* boss, float elapsed) {
    PhaseData* data = &(boss->data);

    if((data->phaseticks > Global::PHASE_LENGTH && data->phasenum == 0) ||
        (data->phaseticks > Global::PHASE_LENGTH * 2 && data->phasenum == 1) ||
        (data->phaseticks > Global::PHASE_LENGTH * 3 && data->phasenum == 2))
    {
        data->phasenum++;
        data->localticks = 0;
        data->is_moving = false;
    }

    switch(data->phasenum) {
        case 0:
            intermediatePhaseOne(boss, elapsed);
            break;
        case 1:
            intermediatePhaseTwo(boss, elapsed);
            break;
        case 2:
            break;
        //Time to switch bosses
        default:
            return true;
    }

    return false;
}