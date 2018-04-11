#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "ShaderProgram.h"

class MenuState {
public:
    MenuState(ShaderProgram* prg);

    int processEvents();
    void update();
    void render();
    
private:
    GLuint text_textureID;
    ShaderProgram* program;
};

#endif