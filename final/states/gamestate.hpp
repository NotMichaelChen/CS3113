#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "ShaderProgram.h"

class GameState {
public:
    GameState(ShaderProgram* prg);

private:
    ShaderProgram* program;
};

#endif