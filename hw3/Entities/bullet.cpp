#include "bullet.hpp"

Bullet::Bullet(SheetSprite& nsprite, float x, float y) : Entity(x, y, 0, nsprite) {}

//Not responsible for collision detection
bool Bullet::Step() {
    y += 0.1;
    return y < 2.2;
}
