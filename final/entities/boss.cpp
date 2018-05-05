#include "boss.hpp"

#include "phases/phase_inventory.hpp"

BossEntity::BossEntity(SheetSprite& nsprite, std::vector<Bullet>* b) : Entity(1.5, 1, 0, nsprite), bullets(b) {
    data.destination[1] = 1;
}

void BossEntity::Update(float elapsed) {
    beginnerBoss(this, elapsed);

    Entity::Update(elapsed);
}