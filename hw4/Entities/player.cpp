#include "player.hpp"

PlayerEntity::PlayerEntity(SheetSprite& nsprite, const Uint8* k) : Entity(0, -2 + nsprite.getRealHeight()/2, 0, false, nsprite), keys(k) {
    velcap[0] = 25;
    velcap[1] = 25;
    friction[0] = 4;
    acceleration[1] = -10;
}

void PlayerEntity::Update(float elapsed) {
    if(keys[SDL_SCANCODE_LEFT]) {
        acceleration[0] = -15;
    }
    else if(keys[SDL_SCANCODE_RIGHT]) {
        acceleration[0] = 15;
    }
    else {
        acceleration[0] = 0;
    }

    if(keys[SDL_SCANCODE_SPACE]) {
        if(position[1] <= -2 + size[1]/2)
            velocity[1] = 5;
    }

    Entity::Update(elapsed);

    float halfwidth = size[0]/2;
    float halfheight = size[1]/2;
    
    if(position[0] < -3.55 + halfwidth) {
        position[0] = -3.55 + halfwidth;
        velocity[0] = 0;
    }
    else if(position[0] > 3.55 - halfwidth) {
        position[0] = 3.55 - halfwidth;
        velocity[0] = 0;
    }

    if(position[1] < -2 + halfheight) {
        position[1] = -2 + halfheight;
        velocity[1] = 0;
    }
    else if(position[1] > 2 - halfheight) {
        position[1] = 2 - halfheight;
        velocity[1] = 0;
    }
}