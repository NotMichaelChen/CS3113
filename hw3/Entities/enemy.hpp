#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "entity.hpp"

class EnemyEntity : public Entity {
public:
    EnemyEntity(SheetSprite& nsprite, float x, float y);
    //Returns whether an edge has been hit
    bool MoveAcross(float amount);
    void ShiftDown();
};

#endif
