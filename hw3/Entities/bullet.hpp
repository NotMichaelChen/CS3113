#ifndef BULLET_HPP
#define BULLET_HPP

#include "entity.hpp"

class Bullet : public Entity {
public:
    Bullet(SheetSprite& nsprite, float x, float y, bool up);
    //Returns whether bullet should continue existing or not
    bool Step(float amount);
};

#endif
