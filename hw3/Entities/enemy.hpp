#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <vector>

#include "entity.hpp"
#include "bullet.hpp"

class EnemyEntity : public Entity {
public:
    EnemyEntity(SheetSprite& nsprite, float x, float y);
    //Returns whether an edge has been hit
    bool MoveAcross(float amount);
    void ShiftDown();
    //Technically doesn't need to be a method, but associates chance of generating bullets with the enemy class
    bool GenerateBullet();

    //Returns which bullet to erase
    std::vector<Bullet>::iterator CheckCollision(std::vector<Bullet>& bullets);
};

#endif
