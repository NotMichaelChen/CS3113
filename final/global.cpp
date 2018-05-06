#include "global.hpp"

#include "util.hpp"

namespace Global
{

GLuint bullet_spritesheet;
GLuint ship_spritesheet;
GLuint text_spritesheet;

void init() {
    bullet_spritesheet = LoadTexture("./assets/bullets.png", GL_NEAREST);
    ship_spritesheet = LoadTexture("./assets/sheet.png", GL_NEAREST);
    text_spritesheet = LoadTexture("./assets/font2.png", GL_LINEAR);
}

}