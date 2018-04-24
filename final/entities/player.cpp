#include "player.hpp"

#include "global.hpp"
#include "util.hpp"

PlayerEntity::PlayerEntity(SheetSprite& nsprite, SheetSprite dotsprite, const Uint8* k) : 
    Entity(1, -0.5, 0, nsprite),
    keys(k),
    hit_dot(dotsprite)
{}

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
    
    if(position[0] < -Global::ORTHO_X + halfwidth)
        position[0] = -Global::ORTHO_X + halfwidth;
    else if(position[0] > Global::ORTHO_X - halfwidth)
        position[0] = Global::ORTHO_X - halfwidth;

    if(position[1] < -Global::ORTHO_Y + halfheight)
        position[1] = -Global::ORTHO_Y + halfheight;
    else if(position[1] > 0.25 - halfheight)
        position[1] = 0.25 - halfheight;
}

void PlayerEntity::Draw(ShaderProgram* program) {
    Entity::Draw(program);
    if(keys[SDL_SCANCODE_LSHIFT])
        hit_dot.Draw(program, position[0], position[1], rotation);
}