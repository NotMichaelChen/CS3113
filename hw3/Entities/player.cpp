#include "player.hpp"

PlayerEntity::PlayerEntity(SheetSprite& nsprite) : Entity(0, -1.7, 0, nsprite) {};

void PlayerEntity::Move(float amount) {
    x += amount*1.7;

    float halfwidth = getWidth()/2;
    
    if(x < -3.55 + halfwidth)
        x = -3.55 + halfwidth;
    else if(x > 3.55 - halfwidth)
        x = 3.55 - halfwidth;
}
