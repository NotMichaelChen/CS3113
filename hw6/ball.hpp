#ifndef BALL_HPP
#define BALL_HPP

#include "entity.hpp"
#include "paddle.hpp"

class Ball : public Entity {
public:
    Ball();
    bool Step(float amount);
    void CheckPaddle(Paddle& testpaddle);
};

#endif
