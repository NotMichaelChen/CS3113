#ifndef BULLET_HPP
#define BULLET_HPP

#include "entity.hpp"
#include "player.hpp"
#include "SheetSprite.hpp"

class Bullet : public Entity {
public:
    Bullet(SheetSprite& nsprite);
    bool shouldDelete(PlayerEntity& player);
};

#endif