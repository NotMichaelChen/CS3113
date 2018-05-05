#include "bullet.hpp"

#include "global.hpp"
#include "util.hpp"

Bullet::Bullet(SheetSprite& nsprite, Vec pos, Vec vel, Vec acc, float rot) : 
    Entity(pos.x, pos.y, rot, nsprite)
{
    velocity = vel;

    acceleration = acc;
}

bool Bullet::shouldDelete(PlayerEntity& player) {
    //Wall detection
    float halfwidth = size.x/2;
    float halfheight = size.y/2;
    
    if(position.x < -Global::ORTHO_X - halfwidth)
        return true;
    else if(position.x > Global::ORTHO_X + halfwidth)
        return true;

    if(position.y < -Global::ORTHO_Y - halfheight)
        return true;
    else if(position.y > Global::ORTHO_Y + halfheight)
        return true;
    
    //Assume size.x is the radius of the circle
    if(dist(position, player.position) <= size.x/2 + player.getRadius()/2)
        return true;
    
    return false;
}