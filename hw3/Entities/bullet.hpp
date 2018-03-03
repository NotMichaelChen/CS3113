#ifndef BULLET_HPP
#define BULLET_HPP

#include "entity.hpp"

class Bullet : public Entity {
public:
    Bullet(SheetSprite& nsprite, float x, float y);
    bool Step();
};

#endif
