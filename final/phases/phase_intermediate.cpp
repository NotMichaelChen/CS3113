#include "phase_intermediate.hpp"

#include "global.hpp"
#include "patterns/patterns.hpp"
#include "movement/lerpfuncs.hpp"
#include "vec.hpp"
#include "util.hpp"

void intermediatePhaseOne(BossEntity* boss, float elapsed) {
    //States: 0=waiting, 1=moving
    const int WAITTICKS = 40;
    const int MOVETICKS = 90;
    const int FIREDELAY = 15;

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
        data->origin = boss->position;
        data->destination.x = randFloat(0.5, 2);
        data->destination.y = randFloat(0.5, 2);

        if(data->origin.x > 0)
            data->destination.x = -data->destination.x;

        data->is_moving = true;
    }
    else if(data->statenum == 1) {
        //Compute firing
        if(data->localticks % FIREDELAY == 0) {
            SheetSprite bulletsprite(Global::bullet_spritesheet, 112, 49, 16, 16, 0.1, 1024, 1024);
            std::vector<Bullet> newbullets = generateCircle(bulletsprite, boss->position, 0.8, 25, 0);
            boss->bullets->insert(boss->bullets->end(), newbullets.begin(), newbullets.end());
        }

        //Compute movement
        float adjustedtime = (data->localticks)/(float)(MOVETICKS);
        boss->position = linearInterpolation(data->origin, data->destination, adjustedtime);
    }

    data->localticks++;
    data->phaseticks++;
    data->totalticks++;
}

void intermediatePhaseTwo(BossEntity* boss, float elapsed) {
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
    //Part two: spawn random bullet fountains
    else {
        if(data->localticks % 80 == 0) {
            Vec genpos;
            genpos.x = randFloat(-2, 2);
            genpos.y = randFloat(-0.5, 1.5);

            SheetSprite generatorsprite(Global::bullet_spritesheet, 288, 0, 32, 32, 0.1, 1024, 1024);
            SheetSprite bulletsprite(Global::bullet_spritesheet, 112, 49, 16, 16, 0.1, 1024, 1024);
            GeneratorEntity genent(generatorsprite, bulletsprite, genpos, 0, 30, 60, 5, boss->bullets);
            
            boss->generators->push_back(genent);
        }
    }

    data->localticks++;
    data->phaseticks++;
    data->totalticks++;
}

void intermediatePhaseThree(BossEntity* boss, float elapsed) {
    //States: 0=moveintoplace, 1=waiting, 2=sweepleft, 3=waiting, 4=sweepright,
    const int FIRETICKS = 100;
    const int WAITTICKS = 30;
    const int MOVETICKS = 60;
    const int FIREDELAY = 10;

    //for convenience
    PhaseData* data = &(boss->data);

    //Update state
    if(data->statenum == 0 && data->localticks >= MOVETICKS) {
        data->localticks = 0;
        data->is_moving = false;
        data->statenum++;
    }
    if((data->statenum == 1 && data->localticks >= WAITTICKS) ||
        (data->statenum == 2 && data->localticks >= FIRETICKS) ||
        (data->statenum == 3 && data->localticks >= WAITTICKS) ||
        (data->statenum == 4 && data->localticks >= FIRETICKS))
    {
        data->localticks = 0;
        data->is_moving = false;
        data->statenum = (data->statenum+1) % 5;
        if(data->statenum == 0)
            data->statenum++;
    }

    if(data->statenum == 0) {
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
    else if(data->statenum == 2) {
        if(data->localticks % FIREDELAY == 0) {
            SheetSprite bulletsprite(Global::bullet_spritesheet, 112, 49, 16, 16, 0.1, 1024, 1024);
            float angle = Global::PI + data->localticks/(10*Global::PI);
            std::vector<Bullet> newbullets = generateStaticCircle(bulletsprite, boss->position, 0.6, angle, 0.7, 15);
            boss->bullets->insert(boss->bullets->end(), newbullets.begin(), newbullets.end());
        }
    }
    else if(data->statenum == 4) {
        if(data->localticks % FIREDELAY == 0) {
            SheetSprite bulletsprite(Global::bullet_spritesheet, 112, 49, 16, 16, 0.1, 1024, 1024);
            float angle = -data->localticks/(10*Global::PI);
            std::vector<Bullet> newbullets = generateStaticCircle(bulletsprite, boss->position, 0.6, angle, 0.7, 15);
            boss->bullets->insert(boss->bullets->end(), newbullets.begin(), newbullets.end());
        }
    }

    data->localticks++;
    data->phaseticks++;
    data->totalticks++;
}