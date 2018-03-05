#include "player.hpp"

PlayerEntity::PlayerEntity(SheetSprite& nsprite) : Entity(0, -1.7, 0, nsprite) {};

void PlayerEntity::Move(float amount) {
    x += amount*1.7;

    float halfwidth = getWidth()/2;
    
    if(x < -3.55 + halfwidth)
        x = -3.55 + halfwidth;
    else if(x > 3.55 - halfwidth)
        x = 3.55 - halfwidth;
}

//Returns which bullet to erase
std::vector<Bullet>::iterator PlayerEntity::CheckCollision(std::vector<Bullet>& bullets) {
    for(auto iter = bullets.begin(); iter != bullets.end(); iter++) {
        //~ is R1’s bottom higher than R2’s top?
        //~ is R1’s top lower than R2’s bottom?
        //~ is R1’s left larger than R2’s right?
        //~ is R1’s right smaller than R2’s left
        //~ If ANY of the above are true, then the two
        //~ rectangles are NOT intersecting!
        if(y - getHeight()/2 > iter->y + iter->getHeight()/2 ||
            y + getHeight()/2 < iter->y - iter->getHeight()/2 ||
            x - getWidth()/2 > iter->x + iter->getWidth()/2 ||
            x + getWidth()/2 < iter->x - iter->getWidth()/2)
        {
            continue;
        }
        else {
            return iter;
        }
    }

    return bullets.end();
}
