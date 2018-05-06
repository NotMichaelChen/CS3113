#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "global.hpp"
#include "ShaderProgram.h"

class MenuState {
public:
    MenuState(ShaderProgram* prg);

    Global::ProgramStates processEvents();
    void render();
    
private:

    void renderBackground();
    //Returns which state to go to based on the menu option selected
    Global::ProgramStates optionAction();

    const int MenuOptions_Entries = 2;
    enum MenuOptions {
        start,
        quit
    };

    int current_state;

    GLuint background;

    ShaderProgram* program;
};

#endif