#include "paddle.hpp"

Paddle::Paddle(bool left) : Entity(3.3, 0, 0, 0.25, 1) {
    if(left)
        x = -x;
}

void Paddle::Move(float amount) {
    y += amount*1.5;
    if(y > 1.5)
        y = 1.5;
    else if(y < -1.5)
        y = -1.5;
}