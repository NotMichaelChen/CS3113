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

    int processEvents();
    void render();

private:
    GLuint textureID;
    ShaderProgram* program;
};

#endif
