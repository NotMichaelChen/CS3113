#include "enemy.hpp"

EnemyEntity::EnemyEntity(SheetSprite& nsprite, float x, float y) : Entity(x, y, 0, nsprite) {
    velocity_x = 0.5;
}

bool EnemyEntity::MoveAcross(float amount) {
    x += amount * velocity_x;
    
    if(x < -3) {
        x = -3;
        return true;
    }
    if(x > 3) {
        x = 3;
        return true;
    }

    return false;
}

void EnemyEntity::ShiftDown() {
    y -= 0.2;
    velocity_x = -velocity_x;
}
