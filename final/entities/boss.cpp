#include "boss.hpp"

#include <iostream>

#include "phases/phase_inventory.hpp"

BossEntity::BossEntity(SheetSprite& nsprite, std::vector<Bullet>* b, std::vector<GeneratorEntity>* g) :
    Entity(1.5, 1, 0, nsprite), bullets(b), generators(g), bosstype(0)
{
}

void BossEntity::Update(float elapsed) {
    if(bosstype == 0)
        done = beginnerBoss(this, elapsed);
    else if(bosstype == 1)
        done = intermediateBoss(this, elapsed);
    else if(bosstype == 2)
        done = advancedBoss(this, elapsed);
    else
        throw std::runtime_error("Error: invalid bosstype");

    if(done) {
        if(bosstype == 2) {
            data.totalticks = -1;
            done = false;
        }
        else {
            bosstype++;
            int oldticks = data.totalticks;
            data = PhaseData();
            data.totalticks = oldticks;
        }

    }

    Entity::Update(elapsed);
}

void BossEntity::reset() {
    bosstype = 0;
    data = PhaseData();
    position.x = 1.5;
    position.y = 1;
}

bool BossEntity::isDone() {
    return done;
}

int BossEntity::getBossType() {
    return bosstype;
}