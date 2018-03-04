#include "bullet.hpp"

Bullet::Bullet(SheetSprite& nsprite, float x, float y) : Entity(x, y, 0, nsprite) {}

//Not responsible for collision detection
bool Bullet::Step(float amount) {
    y += amount*4;
    return y < 2.0;
}
