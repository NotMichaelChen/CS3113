#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include <memory>

#include "global.hpp"
#include "ShaderProgram.h"
#include "entities/player.hpp"

class GameState {
public:
    GameState(ShaderProgram* prg);
    Global::ProgramStates processEvents();
    void update(float elapsed);
    void render();

private:
    ShaderProgram* program;
    const Uint8* keys;

    GLuint ship_spritesheet;

    //Making player a smart pointer allows me to defer construction until the constructor body. This lets me load the sprite
    //before constructing the player
    std::shared_ptr<PlayerEntity> player;
};

#endif