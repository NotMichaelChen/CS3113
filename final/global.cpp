#include "global.hpp"

#include "util.hpp"

namespace Global
{

GLuint bullet_spritesheet;
GLuint ship_spritesheet;
GLuint text_spritesheet;
GLuint reimu_spritesheet;
GLuint byakuren_spritesheet;

Mix_Music *title_music;
Mix_Music *beginner_music;
Mix_Music *intermediate_music;
Mix_Music *advanced_music;

void init() {
    bullet_spritesheet = LoadTexture("./assets/bullets.png", GL_NEAREST);
    ship_spritesheet = LoadTexture("./assets/sheet.png", GL_NEAREST);
    text_spritesheet = LoadTexture("./assets/font2.png", GL_LINEAR);
    reimu_spritesheet = LoadTexture("./assets/reimu.png", GL_NEAREST);
    byakuren_spritesheet = LoadTexture("./assets/byakuren.png", GL_NEAREST);

    title_music = Mix_LoadMUS("./assets/title.ogg");
    beginner_music = Mix_LoadMUS("./assets/stageone.ogg");
    intermediate_music = Mix_LoadMUS("./assets/stagetwo.ogg");
    advanced_music = Mix_LoadMUS("./assets/stagethree.ogg");
}

bool isGameState(ProgramStates& state) {
    return state == ProgramStates::GameOne || state == ProgramStates::GameTwo;
}

}