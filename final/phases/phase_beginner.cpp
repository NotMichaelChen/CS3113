#include "phase_beginner.hpp"

#include <vector>

#include "global.hpp"
#include "patterns/patterns.hpp"
#include "entities/bullet.hpp"
#include "SheetSprite.hpp"
#include "movement/lerpfuncs.hpp"
#include "util.hpp"

void beginnerPhaseOne(BossEntity* boss, float elapsed) {
    const int BEGINMOVE = 30;
    const float MOVELEN = 70.0;

    //for convenience
    PhaseData* data = &(boss->data);

    if(data->localticks == BEGINMOVE) {
        //Generate a ring before moving
        SheetSprite bulletsprite(Global::bullet_spritesheet, 112, 49, 16, 16, 0.1, 1024, 1024);
        std::vector<Bullet> newbullets = generateCircle(bulletsprite, boss->position, 0.5, 25, 0);
        boss->bullets->insert(boss->bullets->end(), newbullets.begin(), newbullets.end());

        //Figure out where to go next
        data->origin = boss->position;
        if(data->origin.x > 0)
            data->destination.Set(-1.5, 1);
        else
            data->destination.Set(1.5, 1);

        //Begin moving
        data->is_moving = true;
    }

    if(data->is_moving) {
        //Compute movement
        float adjustedtime = (data->localticks - BEGINMOVE)/(MOVELEN);
        boss->position = easeInOut(data->origin, data->destination, adjustedtime);

        if(data->localticks == (MOVELEN+BEGINMOVE)) {
            data->is_moving = false;
            data->localticks = 0;
        }
    }

    data->localticks++;
    data->phaseticks++;
    data->totalticks++;
}

void beginnerPhaseTwo(BossEntity* boss, float elapsed) {
    const int BEGINMOVE = 20;
    const float MOVELEN = 50.0;

    PhaseData* data = &(boss->data);

    if(data->localticks == BEGINMOVE) {
        //Generate a line spread before moving
        SheetSprite bulletsprite(Global::bullet_spritesheet, 112, 49, 16, 16, 0.1, 1024, 1024);
        std::vector<Bullet> newbullets = generateLineSpread(bulletsprite, boss->position, {1.5, -0.8}, 15);
        boss->bullets->insert(boss->bullets->end(), newbullets.begin(), newbullets.end());

        //Figure out where to go next
        data->destination = data->origin = boss->position;
        data->destination.x = randFloat(-2.5, 2.5);

        //Begin moving
        data->is_moving = true;
    }

    if(data->is_moving) {
        //Compute movement
        float adjustedtime = (data->localticks - BEGINMOVE)/(MOVELEN);
        boss->position = easeInOut(data->origin, data->destination, adjustedtime);

        if(data->localticks == (MOVELEN+BEGINMOVE)) {
            data->is_moving = false;
            data->localticks = 0;
        }
    }
    
    data->localticks++;
    data->phaseticks++;
    data->totalticks++;
}

void beginnerPhaseThree(BossEntity* boss, float elapsed) {
    //States: 0=firing, 1=waiting, 2=moving
    const int FIRETICKS = 100;
    const int WAITTICKS = 60;
    const int MOVETICKS = 60;
    const int FIREDELAY = 20;

    //for convenience
    PhaseData* data = &(boss->data);

    //Update state
    if((data->statenum == 0 && data->localticks >= FIRETICKS) ||
        (data->statenum == 1 && data->localticks >= WAITTICKS) ||
        (data->statenum == 2 && data->localticks >= MOVETICKS))
    {
        data->localticks = 0;
        data->is_moving = false;
        data->statenum = (data->statenum+1) % 3;
    }

    if(data->statenum == 0 && data->localticks % FIREDELAY == 0) {
        SheetSprite bulletsprite(Global::bullet_spritesheet, 112, 49, 16, 16, 0.1, 1024, 1024);
        std::vector<Bullet> newbullets = generateCircle(bulletsprite, boss->position, 0.5, 25, data->localticks/33.0);
        boss->bullets->insert(boss->bullets->end(), newbullets.begin(), newbullets.end());
    }
    //Use is_moving to indicate if we've computed the next location yet
    else if(data->statenum == 1 && !data->is_moving) {
        data->destination = data->origin = boss->position;
        data->destination.x = randFloat(-2.5, 2.5);

        data->is_moving = true;
    }
    else if(data->statenum == 2) {
        //Compute movement
        float adjustedtime = (data->localticks)/(float)(MOVETICKS);
        boss->position = easeInOut(data->origin, data->destination, adjustedtime);
    }

    data->localticks++;
    data->phaseticks++;
    data->totalticks++;
}