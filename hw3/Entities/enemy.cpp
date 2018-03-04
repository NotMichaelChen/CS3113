#include "enemy.hpp"

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

int EnemyEntity::CheckCollision(std::vector<Bullet>& bullets) {
    int returnindex = 0;
    
    for(int i = 0; i < bullets.size(); ++i) {
        //~ is R1’s bottom higher than R2’s top?
        //~ is R1’s top lower than R2’s bottom?
        //~ is R1’s left larger than R2’s right?
        //~ is R1’s right smaller than R2’s left
        //~ If ANY of the above are true, then the two
        //~ rectangles are NOT intersecting!
    }

    return returnindex;
}
