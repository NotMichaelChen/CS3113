#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "global.hpp"
#include "states/menustate.hpp"

SDL_Window* displayWindow;

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Bullet Hell Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    glewInit();

    glViewport(0, 0, 1024, 768);

    //Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Load shader program
    ShaderProgram program;
    program.Load("vertex_textured.glsl", "fragment_textured.glsl");
    glUseProgram(program.programID);

    //Declare matrices
    Matrix projectionMatrix;
    Matrix viewMatrix;

    //Set matrices
    projectionMatrix.SetOrthoProjection(-3.55, 3.55, -2.0f, 2.0f, -1.0f, 1.0f);
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);

    MenuState menu(&program);
    bool done = false;
    while (!done) {

        Global::ProgramStates next_state = menu.processEvents();
        
        if(next_state == Global::ProgramStates::Quit)
            done = true;

        menu.render();

        SDL_GL_SwapWindow(displayWindow);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    SDL_Quit();
    return 0;
}
