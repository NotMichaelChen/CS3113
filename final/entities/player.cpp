#include "player.hpp"

#include "global.hpp"
#include "util.hpp"

PlayerEntity::PlayerEntity(SheetSprite& nsprite, SheetSprite dotsprite, const Uint8* k) :
    Entity(1, -0.5, 0, nsprite),
    keys(k),
    callcounter(0),
    hit_dot(dotsprite)
{}

void PlayerEntity::Update(float elapsed) {
    float applied_speed = keys[SDL_SCANCODE_LSHIFT] ? slow_speed : fast_speed;

    if(keys[SDL_SCANCODE_LEFT]) {
        velocity.x = -applied_speed;
    }
    else if(keys[SDL_SCANCODE_RIGHT]) {
        velocity.x = applied_speed;
    }
    else {
        velocity.x = 0;
    }
    if(keys[SDL_SCANCODE_UP]) {
        velocity.y = applied_speed;
    }
    else if(keys[SDL_SCANCODE_DOWN]) {
        velocity.y = -applied_speed;
    }
    else {
        velocity.y = 0;
    }

    Entity::Update(elapsed);

    //Wall detection
    float halfwidth = size.x/2;
    float halfheight = size.y/2;
    
    if(position.x < -Global::ORTHO_X + halfwidth)
        position.x = -Global::ORTHO_X + halfwidth;
    else if(position.x > Global::ORTHO_X - halfwidth)
        position.x = Global::ORTHO_X - halfwidth;

    if(position.y < -Global::ORTHO_Y + halfheight)
        position.y = -Global::ORTHO_Y + halfheight;
    else if(position.y > 0.25 - halfheight)
        position.y = 0.25 - halfheight;
}

void PlayerEntity::Draw(ShaderProgram* program) {
    const int FRAMEDELAY = 10;

    if(callcounter % FRAMEDELAY == 0) {
        float spritex = sprite.spritecoord.x + sprite.spritesize.x;
        if(spritex >= sprite.sheetsize.x)
            spritex = 0;
        float spritey = sprite.spritecoord.y;
        sprite.setTexCoords(spritex, spritey);
    }

    Entity::Draw(program);
    if(keys[SDL_SCANCODE_LSHIFT])
        hit_dot.Draw(program, position, rotation);
    
    callcounter++;
}

float PlayerEntity::getRadius() {
    return hit_dot.getRealWidth();
}