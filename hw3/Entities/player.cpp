#include "player.hpp"

PlayerEntity::PlayerEntity(SheetSprite& nsprite) : Entity(0, -1.7, 0, nsprite) {};

void PlayerEntity::Move(float amount) {
    x += amount*1.7;
    
    if(x < -3.3)
        x = -3.3;
    else if(x > 3.3)
        x = 3.3;
}
