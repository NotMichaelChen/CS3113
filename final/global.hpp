#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

namespace Global
{

const float FIXED_TIMESTEP = 0.0166666;

enum ProgramStates {
    Menu,
    Game,
    Score,
    Quit
};

extern GLuint bullet_spritesheet;
extern GLuint ship_spritesheet;

void init();

}

#endif