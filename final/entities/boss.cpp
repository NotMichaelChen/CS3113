#include "boss.hpp"

#include <iostream>

#include "phases/phase_inventory.hpp"
#include "phases/phase_intermediate.hpp"

BossEntity::BossEntity(SheetSprite& nsprite, std::vector<Bullet>* b, std::vector<GeneratorEntity>* g) :
    Entity(1.5, 1, 0, nsprite), bullets(b), generators(g), bosstype(0)
{
}

void BossEntity::Update(float elapsed) {
    bool done;
    switch(bosstype) {
        case 0:
            done = beginnerBoss(this, elapsed);
            break;
        case 1:
            done = intermediateBoss(this, elapsed);
            break;
        case 2:
            break;
        default:
            throw std::runtime_error("Error: invalid bosstype");
    }

    if(done) {
        bosstype++;
        data = PhaseData();
    }

    Entity::Update(elapsed);
}

void BossEntity::reset() {
    bosstype = 0;
    data = PhaseData();
    position.x = 1.5;
    position.y = 1;
}