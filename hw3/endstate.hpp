#ifndef ENDSTATE_HPP
#define ENDSTATE_HPP

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "ShaderProgram.h"

class EndState {
public:
    EndState(ShaderProgram* prg);

    int processEvents();
    void render(bool won);

private:
    GLuint textureID;
    ShaderProgram* program;
};

#endif
