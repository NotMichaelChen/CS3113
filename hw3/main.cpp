#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include <vector>

#include "util.hpp"

#include "menu.hpp"

#include "ShaderProgram.h"

SDL_Window *displayWindow;

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    glewInit();

    glViewport(0, 0, 1280, 720);

    //Initialize keystate array
    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    //Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Load shader program
    ShaderProgram program;
    program.Load("vertex_textured.glsl", "fragment_textured.glsl");
    program.SetColor(1, 1, 1, 1);
    glUseProgram(program.programID);

    //Declare matrices
    Matrix projectionMatrix;
    Matrix viewMatrix;

    projectionMatrix.SetOrthoProjection(-3.55, 3.55, -2.0f, 2.0f, -1.0f, 1.0f);
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);

    MainMenu menu(&program);
    
    //Using int to track state so that I don't need to put an enum in a header file and include it everywhere
    int program_state = 1;

    float lastFrameTicks = 0.0f;
    SDL_Event event;
    bool done = false;
    while (!done)
    {
        float ticks = (float)SDL_GetTicks()/1000.0f;
        float elapsed = ticks - lastFrameTicks;
        lastFrameTicks = ticks;

        glClear(GL_COLOR_BUFFER_BIT);
        
        if(program_state == 1) {
            program_state = menu.processInput();
            if(program_state == 0)
                done = true;
            
            menu.render();
        }
        else if(program_state == 2) {
        }

        SDL_GL_SwapWindow(displayWindow);
    }

    SDL_Quit();
    return 0;
}
