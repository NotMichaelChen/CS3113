#include "boss.hpp"

#include "phases/phase_inventory.hpp"

BossEntity::BossEntity(SheetSprite& nsprite, std::vector<Bullet>* b) : Entity(0, 1, 0, nsprite), bullets(b) {
}

void BossEntity::Update(float elapsed) {
    beginnerBoss(this, elapsed);

    Entity::Update(elapsed);

    ticks++;
}

int BossEntity::getTicks() {
    return ticks;
}