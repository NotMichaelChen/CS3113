#include "phase_inventory.hpp"

#include <vector>

#include <iostream>

#include "global.hpp"
#include "patterns/patterns.hpp"
#include "entities/bullet.hpp"
#include "SheetSprite.hpp"
#include "movement/lerpfuncs.hpp"

void beginnerBoss(BossEntity* boss, float elapsed) {
    //for convenience
    PhaseData* data = &(boss->data);

    if(data->ticks == 60) {
        //Generate a ring before moving
        SheetSprite bulletsprite(Global::bullet_spritesheet, 16, 49, 16, 16, 0.1, 1024, 1024);
        std::vector<Bullet> newbullets = generateCircle(bulletsprite, boss->position, 0.5, 25);
        boss->bullets->insert(boss->bullets->end(), newbullets.begin(), newbullets.end());

        //Figure out where to go next
        std::copy(boss->position, boss->position+2, data->origin);
        if(data->origin[0] > 0)
            data->destination[0] = -1.5;
        else
            data->destination[0] = 1.5;

        //Begin moving
        data->is_moving = true;
    }

    if(data->is_moving) {
        //Compute movement
        float adjustedtime = (data->ticks-60)/60.0;
        easeInOut(boss->position, data->origin, data->destination, adjustedtime);

        if(data->ticks == 120) {
            data->is_moving = false;
            data->ticks = 0;
        }
    }

    data->ticks++;
}