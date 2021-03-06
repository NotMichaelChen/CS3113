#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <vector>

namespace Global
{

//Constants

const float FIXED_TIMESTEP = 0.0166666;
const float ORTHO_X = 3.0;
const float ORTHO_Y = 2.25;
//In ticks (1/60 of a second)
const int PHASE_LENGTH = 1200;
// const int PHASE_LENGTH = 600;
const double PI = 3.141592653589793;
const std::vector<unsigned int> PLAYER_ONE_CONTROLS = {
    SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_LSHIFT
};
const std::vector<unsigned int> PLAYER_TWO_CONTROLS = {
    SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_RSHIFT
};

//Program State enum

enum ProgramStates {
    Menu,
    GameOne,
    GameTwo,
    Score,
    Quit
};

//Sprite Sheets

extern GLuint bullet_spritesheet;
extern GLuint ship_spritesheet;
extern GLuint text_spritesheet;
extern GLuint reimu_spritesheet;
extern GLuint byakuren_spritesheet;

//Music/sound
extern Mix_Music *title_music;
extern Mix_Music *beginner_music;
extern Mix_Music *intermediate_music;
extern Mix_Music *advanced_music;

extern Mix_Chunk *dead;
extern Mix_Chunk *attack1;
extern Mix_Chunk *attack2;
extern Mix_Chunk *attack3;

//Functions

void init();
bool isGameState(ProgramStates& state);

}

#endif