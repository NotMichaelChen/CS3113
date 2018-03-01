#include "player.hpp"

PlayerEntity::PlayerEntity(SheetSprite& nsprite) : Entity(0, -2, 0, nsprite) {};

void PlayerEntity::Move(float amount) {
    x += amount*1.5;
}
