#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include <vector>
#include <cstdlib>
#include <ctime>

#include "util.hpp"

#include "menu.hpp"
#include "gamestate.hpp"
#include "endstate.hpp"

#include "ShaderProgram.h"

SDL_Window *displayWindow;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    glewInit();

    glViewport(0, 0, 1280, 720);

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

    //Set matrices
    projectionMatrix.SetOrthoProjection(-3.55, 3.55, -2.0f, 2.0f, -1.0f, 1.0f);
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);

    //Create Game objects
    MainMenu menu(&program);
    GameState gamestate(&program);
    EndState endstate(&program);
    
    //Using int to track state so that I don't need to put an enum in a header file and include it everywhere
    //0 = exit, 1 = menu, 2 = game, 3 = end
    int program_state = 1;

    float lastFrameTicks = 0.0f;
    bool done = false;
    bool won = false;
    while (!done)
    {
        float ticks = (float)SDL_GetTicks()/1000.0f;
        float elapsed = ticks - lastFrameTicks;
        lastFrameTicks = ticks;

        glClear(GL_COLOR_BUFFER_BIT);

        //Start Menu State
        if(program_state == 1) {
            program_state = menu.processEvents();
            if(program_state == 0)
                done = true;
            //No need to reset game; cannot come back to start menu state
            
            menu.render();
        }
        //Game State
        else if(program_state == 2) {
            program_state = gamestate.processEvents();
            if(program_state == 0)
                done = true;

            int status = gamestate.update(elapsed);
            if(status != 0) {
                program_state = 3;
                won = (status == 1);
            }
            gamestate.render();
        }
        //End Game State
        else if(program_state == 3) {
            program_state = endstate.processEvents();
            if(program_state == 0)
                done = true;
            //Reset game before entering
            else if(program_state == 2)
                gamestate.reset();
                
            endstate.render(won);
        }

        SDL_GL_SwapWindow(displayWindow);
    }

    SDL_Quit();
    return 0;
}
