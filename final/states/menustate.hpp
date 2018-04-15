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
    void render();
    
private:
    const int MenuOptions_Entries = 2;
    enum MenuOptions {
        start,
        quit
    };

    int current_state;

    GLuint text_textureID;
    ShaderProgram* program;
};

#endif