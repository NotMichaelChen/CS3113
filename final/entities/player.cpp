#include "player.hpp"

#include "util.hpp"

PlayerEntity::PlayerEntity(SheetSprite& nsprite, const Uint8* k) : Entity(1, -0.5, 0, nsprite), keys(k) {}

void PlayerEntity::Update(float elapsed) {
    if(keys[SDL_SCANCODE_LEFT]) {
        velocity[0] = -1;
    }
    else if(keys[SDL_SCANCODE_RIGHT]) {
        velocity[0] = 1;
    }
    else {
        velocity[0] = 0;
    }
    if(keys[SDL_SCANCODE_UP]) {
        velocity[1] = 1;
    }
    else if(keys[SDL_SCANCODE_DOWN]) {
        velocity[1] = -1;
    }
    else {
        velocity[1] = 0;
    }

    Entity::Update(elapsed);
}