#ifndef MENU_HPP
#define MENU_HPP

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "ShaderProgram.h"

class MainMenu {
public:
    MainMenu(ShaderProgram* prg);

    //0 = exit, 1 = current state, 2 = game state
    int processInput();
    void render();

private:
    GLuint textureID;
    ShaderProgram* program;
};

#endif
