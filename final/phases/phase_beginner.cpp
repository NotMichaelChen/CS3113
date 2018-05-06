#include "phase_beginner.hpp"

#include <vector>
#include <random>

#include "global.hpp"
#include "patterns/patterns.hpp"
#include "entities/bullet.hpp"
#include "SheetSprite.hpp"
#include "movement/lerpfuncs.hpp"

void beginnerPhaseOne(BossEntity* boss, float elapsed) {
    const int BEGINMOVE = 30;
    const float MOVELEN = 70.0;

    //for convenience
    PhaseData* data = &(boss->data);

    if(data->ticks == BEGINMOVE) {
        //Generate a ring before moving
        SheetSprite bulletsprite(Global::bullet_spritesheet, 16, 49, 16, 16, 0.1, 1024, 1024);
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
        float adjustedtime = (data->ticks - BEGINMOVE)/(MOVELEN);
        boss->position = easeInOut(data->origin, data->destination, adjustedtime);

        if(data->ticks == (MOVELEN+BEGINMOVE)) {
            data->is_moving = false;
            data->ticks = 0;
        }
    }

    data->ticks++;
    data->phaseticks++;
}

void beginnerPhaseTwo(BossEntity* boss, float elapsed) {
    const int BEGINMOVE = 20;
    const float MOVELEN = 50.0;

    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_real_distribution<> distribution(-2.5, 2.5);

    PhaseData* data = &(boss->data);

    if(data->ticks == BEGINMOVE) {
        //Generate a line spread before moving
        SheetSprite bulletsprite(Global::bullet_spritesheet, 16, 49, 16, 16, 0.1, 1024, 1024);
        std::vector<Bullet> newbullets = generateLineSpread(bulletsprite, boss->position, {1.5, -0.8}, 15);
        boss->bullets->insert(boss->bullets->end(), newbullets.begin(), newbullets.end());

        //Figure out where to go next
        data->destination = data->origin = boss->position;
        data->destination.x = distribution(engine);

        //Begin moving
        data->is_moving = true;
    }

    if(data->is_moving) {
        //Compute movement
        float adjustedtime = (data->ticks - BEGINMOVE)/(MOVELEN);
        boss->position = easeInOut(data->origin, data->destination, adjustedtime);

        if(data->ticks == (MOVELEN+BEGINMOVE)) {
            data->is_moving = false;
            data->ticks = 0;
        }
    }
    
    data->ticks++;
    data->phaseticks++;
}

void beginnerPhaseThree(BossEntity* boss, float elapsed) {
    //States: 0=firing, 1=waiting, 2=moving
    const int FIRETICKS = 100;
    const int WAITTICKS = 60;
    const int MOVETICKS = 60;
    const int FIREDELAY = 20;

    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_real_distribution<> distribution(-2.5, 2.5);

    //for convenience
    PhaseData* data = &(boss->data);

    //Update state
    if((data->statenum == 0 && data->ticks >= FIRETICKS) ||
        (data->statenum == 1 && data->ticks >= WAITTICKS) ||
        (data->statenum == 2 && data->ticks >= MOVETICKS))
    {
        data->ticks = 0;
        data->is_moving = false;
        data->statenum = (data->statenum+1) % 3;
    }

    if(data->statenum == 0 && data->ticks % FIREDELAY == 0) {
        SheetSprite bulletsprite(Global::bullet_spritesheet, 16, 49, 16, 16, 0.1, 1024, 1024);
        std::vector<Bullet> newbullets = generateCircle(bulletsprite, boss->position, 0.5, 25, data->ticks/33.0);
        boss->bullets->insert(boss->bullets->end(), newbullets.begin(), newbullets.end());
    }
    //Use is_moving to indicate if we've computed the next location yet
    else if(data->statenum == 1 && !data->is_moving) {
        data->destination = data->origin = boss->position;
        data->destination.x = distribution(engine);

        data->is_moving = true;
    }
    else if(data->statenum == 2) {
        //Compute movement
        float adjustedtime = (data->ticks)/(float)(MOVETICKS);
        boss->position = easeInOut(data->origin, data->destination, adjustedtime);
    }

    data->ticks++;
    data->phaseticks++;
}