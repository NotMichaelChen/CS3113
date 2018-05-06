#include "bullet.hpp"

#include "global.hpp"
#include "util.hpp"

Bullet::Bullet(SheetSprite& nsprite, Vec pos, Vec vel, Vec acc, float rot) : 
    Entity(pos.x, pos.y, rot, nsprite)
{
    velocity = vel;

    acceleration = acc;
}

int Bullet::checkCollision(PlayerEntity& player) {
    //Wall detection
    float halfwidth = size.x/2;
    float halfheight = size.y/2;
    
    if(position.x < -Global::ORTHO_X - halfwidth)
        return 1;
    else if(position.x > Global::ORTHO_X + halfwidth)
        return 1;

    if(position.y < -Global::ORTHO_Y - halfheight)
        return 1;
    else if(position.y > Global::ORTHO_Y + halfheight)
        return 11;
    
    //Assume size.x is the radius of the circle
    if(dist(position, player.position) <= size.x/2 + player.getRadius()/2)
        return 2;
    
    return 0;
}