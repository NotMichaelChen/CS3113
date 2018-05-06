#ifndef BULLET_HPP
#define BULLET_HPP

#include "entity.hpp"
#include "player.hpp"
#include "SheetSprite.hpp"

class Bullet : public Entity {
public:
    Bullet(SheetSprite& nsprite, Vec pos, Vec vel, Vec acc, float rot);
    //0 = none, 1 = wall, 2 = player
    int checkCollision(PlayerEntity& player);
};

#endif