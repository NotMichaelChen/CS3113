#include "bullet.hpp"

#include "util.hpp"

Bullet::Bullet(SheetSprite& nsprite) : Entity(0, 0, 0, nsprite) {
}

bool Bullet::shouldDelete(PlayerEntity& player) {
    //Wall detection
    float halfwidth = size[0]/2;
    float halfheight = size[1]/2;
    
    if(position[0] < -3.55 + halfwidth)
        return true;
    else if(position[0] > 3.55 - halfwidth)
        return true;

    if(position[1] < -2 + halfheight)
        return true;
    else if(position[1] > 2 - halfheight)
        return true;
    
    //Assume size.x is the radius of the circle
    //TODO: Player size is too big
    if(dist(position, player.position) <= size[0] + player.size[0])
        return true;
    
    return false;
}