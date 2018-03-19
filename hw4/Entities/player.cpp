#include "player.hpp"

PlayerEntity::PlayerEntity(SheetSprite& nsprite) : Entity(0, -2 + nsprite.getRealHeight()/2, 0, false, nsprite) {
    velcap[0] = 4;
    friction[0] = 1;
}

void PlayerEntity::Update(float elapsed) {

    Entity::Update(elapsed);

    float halfwidth = size[0]/2;
    
    if(position[0] < -3.55 + halfwidth) {
        position[0] = -3.55 + halfwidth;
        velocity[0] = 0;
    }
    else if(position[0] > 3.55 - halfwidth) {
        position[0] = 3.55 - halfwidth;
        velocity[0] = 0;
    }
}