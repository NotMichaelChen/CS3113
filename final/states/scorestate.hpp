#ifndef SCORESTATE_HPP
#define SCORESTATE_HPP

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "ShaderProgram.h"
#include "global.hpp"

class ScoreState {
public:
    ScoreState(ShaderProgram* prg);

    void setTicks(int t);

    Global::ProgramStates processEvents();
    void render();
    
private:

    void renderBackground();

    int seconds;
    bool is_win;

    GLuint background;
    ShaderProgram* program;
};

#endif