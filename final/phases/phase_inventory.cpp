#include "phase_inventory.hpp"

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
        std::vector<Bullet> newbullets = generateCircle(bulletsprite, boss->position, 0.5, 25);
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