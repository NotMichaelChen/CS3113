#ifndef BALL_HPP
#define BALL_HPP

#include <SDL_mixer.h>

#include "entity.hpp"
#include "paddle.hpp"

class Ball : public Entity {
public:
    Ball();
    bool Step(float amount);
    void CheckPaddle(Paddle& testpaddle);

private:
    bool valid;

    Mix_Chunk* paddle_hit;
    Mix_Chunk* wall_hit;
    Mix_Chunk* finish;
    Mix_Music* music;
};

#endif
