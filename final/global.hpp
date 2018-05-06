#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

namespace Global
{

const float FIXED_TIMESTEP = 0.0166666;
const float ORTHO_X = 3.0;
const float ORTHO_Y = 2.25;
//In ticks (1/60 of a second)
const int PHASE_LENGTH = 1800;
// const int PHASE_LENGTH = 600;

enum ProgramStates {
    Menu,
    Game,
    Score,
    Quit
};

extern GLuint bullet_spritesheet;
extern GLuint ship_spritesheet;
extern GLuint text_spritesheet;

void init();

}

#endif