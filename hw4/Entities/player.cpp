#include "player.hpp"

PlayerEntity::PlayerEntity(SheetSprite& nsprite) : Entity(0, -2 + nsprite.getRealHeight()/2, 0, false, nsprite) {};

void PlayerEntity::Move(float amount) {
    position[0] += amount*1.7;

    float halfwidth = size[0]/2;
    
    if(position[0] < -3.55 + halfwidth)
        position[0] = -3.55 + halfwidth;
    else if(position[0] > 3.55 - halfwidth)
        position[0] = 3.55 - halfwidth;
}