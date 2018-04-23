#include "boss.hpp"

#include "patterns/pattern_inventory.hpp"

BossEntity::BossEntity(SheetSprite& nsprite) : Entity(0, 1, 0, nsprite) {
}

void BossEntity::Update(float elapsed) {
    beginnerBoss(this, elapsed);
}