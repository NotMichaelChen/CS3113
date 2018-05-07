#include "player.hpp"

#include "global.hpp"
#include "util.hpp"

PlayerEntity::PlayerEntity(SheetSprite& nsprite, SheetSprite dotsprite, const Uint8* k, std::vector<unsigned int> c) :
    Entity(1, -0.5, 0, nsprite), lives(3), keys(k), controls(c), updatecounter(0), invinc_counter(0), hit_dot(dotsprite)
{
    if(controls.size() != 5) {
        throw std::runtime_error("Error: control vector passed does not have 5 keys");
    }
}

void PlayerEntity::Update(float elapsed) {
    float applied_speed = keys[controls[4]] ? slow_speed : fast_speed;

    if(keys[controls[0]]) {
        velocity.x = -applied_speed;
    }
    else if(keys[controls[1]]) {
        velocity.x = applied_speed;
    }
    else {
        velocity.x = 0;
    }
    if(keys[controls[2]]) {
        velocity.y = applied_speed;
    }
    else if(keys[controls[3]]) {
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

    //Animation updating
    const int FRAMEDELAY = 10;

    if(updatecounter % FRAMEDELAY == 0) {
        float spritex = sprite.spritecoord.x + sprite.spritesize.x;
        if(spritex >= sprite.sheetsize.x)
            spritex = 0;
        float spritey = sprite.spritecoord.y;
        sprite.setTexCoords(spritex, spritey);
    }

    updatecounter++;
    if(invinc_counter > 0)
        invinc_counter--;
}

void PlayerEntity::Draw(ShaderProgram* program) {

    Entity::Draw(program);
    if(keys[controls[4]])
        hit_dot.Draw(program, position, rotation);
}

float PlayerEntity::getRadius() {
    return hit_dot.getRealWidth();
}

void PlayerEntity::setInvinc() {
    invinc_counter = 120;
}

bool PlayerEntity::isInvinc() {
    return invinc_counter > 0;
}

void PlayerEntity::reset() {
    updatecounter = 0;
    invinc_counter = 0;
    lives = 3;
}