#include "bullet.hpp"

Bullet::Bullet(SheetSprite& nsprite, float x, float y) : Entity(x, y, 0, nsprite) {}

//Returns whether bullet should continue existing or not
//Not responsible for collision detection
bool Bullet::Step(float amount) {
    y += amount*4;
    return y - getHeight()/2 < 2.0;
}
