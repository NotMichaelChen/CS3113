#include "player.hpp"

#include "util.hpp"

PlayerEntity::PlayerEntity(SheetSprite& nsprite, const Uint8* k) : Entity(1, -0.5, 0, nsprite), keys(k) {}

void PlayerEntity::Update(float elapsed) {
    float applied_speed = keys[SDL_SCANCODE_LSHIFT] ? slow_speed : fast_speed;

    if(keys[SDL_SCANCODE_LEFT]) {
        velocity[0] = -applied_speed;
    }
    else if(keys[SDL_SCANCODE_RIGHT]) {
        velocity[0] = applied_speed;
    }
    else {
        velocity[0] = 0;
    }
    if(keys[SDL_SCANCODE_UP]) {
        velocity[1] = applied_speed;
    }
    else if(keys[SDL_SCANCODE_DOWN]) {
        velocity[1] = -applied_speed;
    }
    else {
        velocity[1] = 0;
    }

    Entity::Update(elapsed);

    //Wall detection

    float halfwidth = size[0]/2;
    float halfheight = size[1]/2;
    
    if(position[0] < -3.55 + halfwidth)
        position[0] = -3.55 + halfwidth;
    else if(position[0] > 3.55 - halfwidth)
        position[0] = 3.55 - halfwidth;

    if(position[1] < -2 + halfheight)
        position[1] = -2 + halfheight;
    else if(position[1] > 0.25 - halfheight)
        position[1] = 0.25 - halfheight;

}