#include "bullet.hpp"

Bullet::Bullet(SheetSprite& nsprite, float x, float y, bool up) : Entity(x, y, 0, nsprite) {
    velocity_y = up ? 3.5 : -3.5;
}

//Returns whether bullet should continue existing or not
//Not responsible for collision detection
bool Bullet::Step(float amount) {
    y += amount*velocity_y;
    return y - getHeight()/2 < 2.0 || y + getHeight()/2 < 2.0;
}
