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
    //Part two: Generate lines & random bursts
    else {
        //Lines
        if(data->localticks % 25 == 0) {
            const int ARMS = 8;

            SheetSprite bulletsprite(Global::bullet_spritesheet, 112, 49, 16, 16, 0.1, 1024, 1024);

            for(int i = 1; i < ARMS; i++) {
                boss->bullets->push_back(generateSingle(bulletsprite, boss->position, Global::PI + (Global::PI*i)/ARMS, 0.8));
            }
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
        if(data->localticks % 10 == 0) {
            SheetSprite bulletsprite(Global::bullet_spritesheet, 112, 49, 16, 16, 0.1, 1024, 1024);
            std::vector<Bullet> newbullets = generateCircle(bulletsprite, boss->position, 0.8, 6, data->localticks/(20*Global::PI));
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

void advancedPhaseThree(BossEntity* boss, float elapsed) {
    //States: 0=waiting, 1=moving, 2=firing
    const int FIRETICKS = 100;
    const int WAITTICKS = 0;
    const int MOVETICKS = 60;
    const int FIREDELAY = 10;

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

    if(data->statenum == 0) {
        //Bursts
        if(data->localticks == 0) {
            Vec genpos;
            genpos.x = randFloat(-2, 2);
            genpos.y = randFloat(-0.5, 1);

            SheetSprite generatorsprite(Global::bullet_spritesheet, 288, 0, 32, 32, 0.1, 1024, 1024);
            SheetSprite bulletsprite(Global::bullet_spritesheet, 112, 49, 16, 16, 0.1, 1024, 1024);
            GeneratorEntity genent(generatorsprite, bulletsprite, genpos, 0, 30, 60, 5, boss->bullets);
            
            boss->generators->push_back(genent);
        }
        if(data->localticks % FIREDELAY == 0) {
            SheetSprite bulletsprite(Global::bullet_spritesheet, 112, 49, 16, 16, 0.1, 1024, 1024);
            std::vector<Bullet> newbullets;

            int pattern = randInt(0, 1);
            if(pattern == 0 && data->localticks) {
                newbullets = generateCircle(bulletsprite, boss->position, 0.5, randInt(20, 25), randFloat(0, Global::PI));
            }
            else if(pattern == 1 && data->localticks) {
                newbullets = generateLineSpread(bulletsprite, boss->position, {1.5, -0.5}, randInt(5, 15));
            }

            boss->bullets->insert(boss->bullets->end(), newbullets.begin(), newbullets.end());
        }
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
}