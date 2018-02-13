#include "paddle.hpp"

Paddle::Paddle(bool left) : Entity(3.3, 0, 0, 0.25, 1) {
    if(left)
        x = -x;
}

void Paddle::MovePaddle(float amount) {
    y += amount;
}