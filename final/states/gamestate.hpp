#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include <memory>
#include <vector>

#include "global.hpp"
#include "ShaderProgram.h"
#include "entities/player.hpp"
#include "entities/boss.hpp"

class GameState {
public:
    GameState(ShaderProgram* prg);
    Global::ProgramStates processEvents();
    void update(float elapsed);
    void render();

    void reset();

private:

    void renderBackground();
    
    ShaderProgram* program;
    ShaderProgram background_program;
    const Uint8* keys;

    //Making player a smart pointer allows me to defer construction until the constructor body. This lets me load the sprite
    //before constructing the player
    std::unique_ptr<PlayerEntity> player;
    std::unique_ptr<BossEntity> boss;
    std::vector<Bullet> bullets;

    GLuint background;
};

#endif