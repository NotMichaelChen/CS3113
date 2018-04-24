#ifndef BULLET_HPP
#define BULLET_HPP

#include "entity.hpp"
#include "player.hpp"
#include "SheetSprite.hpp"

class Bullet : public Entity {
public:
    Bullet(SheetSprite& nsprite, float x, float y, float velx, float vely, float accx, float accy, float rot);
    bool shouldDelete(PlayerEntity& player);
};

#endif