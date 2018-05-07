#include "global.hpp"

#include "util.hpp"

namespace Global
{

GLuint bullet_spritesheet;
GLuint ship_spritesheet;
GLuint text_spritesheet;
GLuint reimu_spritesheet;
GLuint byakuren_spritesheet;

void init() {
    bullet_spritesheet = LoadTexture("./assets/bullets.png", GL_NEAREST);
    ship_spritesheet = LoadTexture("./assets/sheet.png", GL_NEAREST);
    text_spritesheet = LoadTexture("./assets/font2.png", GL_LINEAR);
    reimu_spritesheet = LoadTexture("./assets/reimu.png", GL_NEAREST);
    byakuren_spritesheet = LoadTexture("./assets/byakuren.png", GL_NEAREST);
}

bool isGameState(ProgramStates& state) {
    return state == ProgramStates::GameOne || state == ProgramStates::GameTwo;
}

}