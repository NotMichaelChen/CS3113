#include "bullet.hpp"

#include "global.hpp"
#include "util.hpp"

Bullet::Bullet(SheetSprite& nsprite, float x, float y, float velx, float vely, float accx, float accy, float rot) : 
    Entity(x, y, rot, nsprite)
{
    velocity[0] = velx;
    velocity[1] = vely;

    acceleration[0] = accx;
    acceleration[1] = accy;
}

bool Bullet::shouldDelete(PlayerEntity& player) {
    //Wall detection
    float halfwidth = size[0]/2;
    float halfheight = size[1]/2;
    
    if(position[0] < -Global::ORTHO_X + halfwidth)
        return true;
    else if(position[0] > Global::ORTHO_X - halfwidth)
        return true;

    if(position[1] < -Global::ORTHO_Y + halfheight)
        return true;
    else if(position[1] > Global::ORTHO_Y - halfheight)
        return true;
    
    //Assume size.x is the radius of the circle
    //TODO: Player size is too big
    if(dist(position, player.position) <= size[0]/2 + player.getRadius()/2)
        return true;
    
    return false;
}