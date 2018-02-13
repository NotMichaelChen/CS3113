#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "entity.hpp"

class Paddle : public Entity {
public:
    //must pass in what side of the screen the paddle exists on
    Paddle(bool left);
    void MovePaddle(float amount);
};

#endif