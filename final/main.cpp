#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "global.hpp"
#include "states/menustate.hpp"
#include "states/gamestate.hpp"

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

    //Create state objects
    MenuState menu(&program);
    GameState game(&program);

    //Main game loop
    Global::ProgramStates state = Global::ProgramStates::Menu;
    bool done = false;
    float last_frame_ticks = 0;
    float accumulator = 0;
    while (!done) {
        //Process Events
        //assign state after updating
        Global::ProgramStates next_state;
        if(state == Global::ProgramStates::Menu)
            next_state = menu.processEvents();
        else if(state == Global::ProgramStates::Game)
            next_state = game.processEvents();
        
        //Compute Timesteps
        float ticks = (float)SDL_GetTicks()/1000.0f;
        accumulator += ticks - last_frame_ticks;
        last_frame_ticks = ticks;

        if(accumulator < Global::FIXED_TIMESTEP) {
            state = next_state;
            continue;
        }
        
        //Update
        while(accumulator >= Global::FIXED_TIMESTEP) {

            if(state == Global::ProgramStates::Game)
                game.update(Global::FIXED_TIMESTEP);

            accumulator -= Global::FIXED_TIMESTEP;
        }
        
        //Render
        if(state == Global::ProgramStates::Menu)
            menu.render();
        else if(state == Global::ProgramStates::Game)
            game.render();

        //Check if done, update state
        if(next_state == Global::ProgramStates::Quit)
            done = true;
        state = next_state;

        SDL_GL_SwapWindow(displayWindow);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    SDL_Quit();
    return 0;
}
