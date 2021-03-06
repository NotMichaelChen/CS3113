#include "enemy.hpp"

#include <cstdlib>

EnemyEntity::EnemyEntity(SheetSprite& nsprite, float x, float y) : Entity(x, y, 0, nsprite) {
    velocity_x = 0.75;
}

bool EnemyEntity::MoveAcross(float amount) {
    x += amount * velocity_x;

    //Do not "fix" position to avoid desyncing enemies in vector

    float halfwidth = getWidth()/2;
    
    if(x < -3.55 + halfwidth) {
        return true;
    }
    if(x > 3.55 - halfwidth) {
        return true;
    }

    return false;
}

void EnemyEntity::ShiftDown() {
    y -= 0.2;
    velocity_x = -velocity_x;
}

bool EnemyEntity::GenerateBullet() {
    return rand() % 1000 == 0;
}

//Returns which bullet to erase
std::vector<Bullet>::iterator EnemyEntity::CheckCollision(std::vector<Bullet>& bullets) {
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
