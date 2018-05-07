#include "phase_advanced.hpp"

#include "global.hpp"
#include "patterns/patterns.hpp"
#include "movement/lerpfuncs.hpp"
#include "vec.hpp"
#include "util.hpp"

void advancedPhaseOne(BossEntity* boss, float elapsed) {
    const int MOVETICKS = 60;

    //for convenience
    PhaseData* data = &(boss->data);

    //Part one: move into position
    if(data->localticks < MOVETICKS) {
        if(!data->is_moving) {
            data->origin = boss->position;
            data->destination = Vec(0,1.5);
            data->is_moving = true;
        }
        else {
            //Compute movement
            float adjustedtime = (data->localticks)/(float)(MOVETICKS);
            boss->position = easeInOut(data->origin, data->destination, adjustedtime);
        }
    }
    //Part two: Generate spiral & random bursts
    else {
        //Spiral
        if(data->localticks % 15 == 0) {
            SheetSprite bulletsprite(Global::bullet_spritesheet, 112, 49, 16, 16, 0.1, 1024, 1024);
            std::vector<Bullet> newbullets = generateCircle(bulletsprite, boss->position, 0.7, 6, data->localticks/(20*Global::PI));
            boss->bullets->insert(boss->bullets->end(), newbullets.begin(), newbullets.end());
        }
        //Bursts
        if(data->localticks % 80 == 0) {
            Vec genpos;
            genpos.x = randFloat(-2, 2);
            genpos.y = randFloat(-0.5, 1);

            SheetSprite generatorsprite(Global::bullet_spritesheet, 288, 0, 32, 32, 0.1, 1024, 1024);
            SheetSprite bulletsprite(Global::bullet_spritesheet, 112, 49, 16, 16, 0.1, 1024, 1024);
            GeneratorEntity genent(generatorsprite, bulletsprite, genpos, 0, 30, 60, 5, boss->bullets);
            
            boss->generators->push_back(genent);
        }
    }

    data->localticks++;
    data->phaseticks++;
}

void advancedPhaseTwo(BossEntity* boss, float elapsed) {

}

void advancedPhaseThree(BossEntity* boss, float elapsed) {

}