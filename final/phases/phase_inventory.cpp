#include "phase_inventory.hpp"

#include "global.hpp"
#include "phase_beginner.hpp"

void beginnerBoss(BossEntity* boss, float elapsed) {
    PhaseData* data = &(boss->data);

    if(data->phaseticks < Global::PHASE_LENGTH)
        beginnerPhaseOne(boss, elapsed);
    else if(data->phaseticks < Global::PHASE_LENGTH * 2)
        beginnerPhaseTwo(boss, elapsed);
    else if(data->phaseticks < Global::PHASE_LENGTH * 3)
        ;
    else
        ;
}