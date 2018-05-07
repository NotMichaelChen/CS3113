#include "phase_intermediate.hpp"

#include <random>

#include "global.hpp"
#include "patterns/patterns.hpp"
#include "movement/lerpfuncs.hpp"

void intermediatePhaseOne(BossEntity* boss, float elapsed) {
    //States: 0=waiting, 1=moving
    const int WAITTICKS = 60;
    const int MOVETICKS = 90;
    const int FIREDELAY = 20;

    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_real_distribution<> distribution(-2.5, 2.5);

    //for convenience
    PhaseData* data = &(boss->data);

    //Update state
    if((data->statenum == 0 && data->localticks >= WAITTICKS) ||
        (data->statenum == 1 && data->localticks >= MOVETICKS))
    {
        data->localticks = 0;
        data->is_moving = false;
        data->statenum = (data->statenum+1) % 2;
    }

    //Use is_moving to indicate if we've computed the next location yet
    if(data->statenum == 0 && !data->is_moving) {
        data->destination = data->origin = boss->position;
        data->destination.x = distribution(engine);

        data->is_moving = true;
    }
    else if(data->statenum == 1) {
        //Compute firing
        if(data->localticks % FIREDELAY == 0) {
            SheetSprite bulletsprite(Global::bullet_spritesheet, 112, 49, 16, 16, 0.1, 1024, 1024);
            std::vector<Bullet> newbullets = generateCircle(bulletsprite, boss->position, 0.5, 25, 0);
            boss->bullets->insert(boss->bullets->end(), newbullets.begin(), newbullets.end());
        }

        //Compute movement
        float adjustedtime = (data->localticks)/(float)(MOVETICKS);
        boss->position = easeInOut(data->origin, data->destination, adjustedtime);
    }

    data->localticks++;
    data->phaseticks++;
}