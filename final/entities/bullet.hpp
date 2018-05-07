#ifndef BULLET_HPP
#define BULLET_HPP

#include "entity.hpp"
#include "player.hpp"
#include "SheetSprite.hpp"

class Bullet : public Entity {
public:
    Bullet(SheetSprite& nsprite, Vec pos, Vec vel, Vec acc, float rot);
    bool checkWalls();
    bool checkPlayer(PlayerEntity& player);
};

#endif