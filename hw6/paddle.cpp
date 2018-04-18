#include "paddle.hpp"

Paddle::Paddle(bool left) : Entity(3.3, 0, 0, 0.25, 1) {
    if(left)
        x = -x;
}

void Paddle::Move(float amount) {
    y += amount*1.5;
    if(y > 2 - height/2)
        y = 2 - height/2;
    else if(y < -2 + height/2)
        y = -2 + height/2;
}