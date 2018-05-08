#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "global.hpp"
#include "states/menustate.hpp"
#include "states/gamestate.hpp"
#include "states/scorestate.hpp"

SDL_Window* displayWindow;
Global::ProgramStates fadingstate;

//Handle state transitions
//Returns if there was any transition
bool handleStateTransitions(Global::ProgramStates& state, Global::ProgramStates& next_state, MenuState& menu, GameState& game,
    ScoreState& score)
{
    bool did_transition = false;
    if(state == Global::ProgramStates::Menu && Global::isGameState(next_state)) {
        game.init(next_state == Global::ProgramStates::GameOne);
        fadingstate = state;
        did_transition = true;
    }

    if(Global::isGameState(state) && next_state == Global::ProgramStates::Score) {
        score.setSeconds(game.getSeconds());
        fadingstate = state;
        did_transition = true;
    }

    if(state == Global::ProgramStates::Score && next_state == Global::ProgramStates::Menu) {
        fadingstate = state;
        did_transition = true;
    }
    
    state = next_state;
    return did_transition;
}

void fadeOut(ShaderProgram& program, float secs, MenuState& menu, GameState& game, ScoreState& score)
{
    float alpha = 0;
    float begin = (float)SDL_GetTicks()/1000.0f;
    SDL_Event event;
    while(alpha <= 1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                exit(0);
            }
        }

        if(fadingstate == Global::ProgramStates::Menu)
            menu.render();
        else if(Global::isGameState(fadingstate))
            game.render();
        else if(fadingstate == Global::ProgramStates::Score)
            score.render();
        
        float vertices[] = {-3, -2.25, 3, -2.25, 3, 2.25, -3, -2.25, 3, 2.25, -3, 2.25};
        glUseProgram(program.programID);

        float now = (float)SDL_GetTicks()/1000.0f;
        alpha = (now - begin) / secs;
        program.SetAlphaMask(alpha);

        Matrix center;
        program.SetModelMatrix(center);

        glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
        glEnableVertexAttribArray(program.positionAttribute);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDisableVertexAttribArray(program.positionAttribute);

        SDL_GL_SwapWindow(displayWindow);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Bullet Hell Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    glewInit();

    Global::init();

    glViewport(0, 0, 1024, 768);

    //Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Load shader programs
    ShaderProgram program;
    program.Load("vertex_textured.glsl", "fragment_textured.glsl");
    glUseProgram(program.programID);

    ShaderProgram untextured_program;
    untextured_program.Load("vertex.glsl", "fragment.glsl");
    untextured_program.SetColor(0, 0, 0, 1);

    //Declare matrices
    Matrix projectionMatrix;
    Matrix viewMatrix;

    //Set matrices
    projectionMatrix.SetOrthoProjection(-Global::ORTHO_X, Global::ORTHO_X, -Global::ORTHO_Y, Global::ORTHO_Y, -1.0f, 1.0f);
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    untextured_program.SetProjectionMatrix(projectionMatrix);
    untextured_program.SetViewMatrix(viewMatrix);

    //Create state objects
    MenuState menu(&program);
    GameState game(&program);
    ScoreState score(&program);

    //Main game loop
    bool isfading = false;
    Global::ProgramStates state = Global::ProgramStates::Menu;
    bool done = false;
    float last_frame_ticks = 0;
    float accumulator = 0;
    while (!done) {
        //Begin fadeOut if needed
        if(isfading) {
            fadeOut(untextured_program, 1, menu, game, score);
            glUseProgram(program.programID);
            isfading = false;
            //Set last_frame_ticks to pretend like no time has passed
            last_frame_ticks = (float)SDL_GetTicks()/1000.0f;
        }

        //Process Events
        //assign state after updating
        Global::ProgramStates next_state;
        if(state == Global::ProgramStates::Menu)
            next_state = menu.processEvents();
        else if(Global::isGameState(state))
            next_state = game.processEvents();
        else if(state == Global::ProgramStates::Score)
            next_state = score.processEvents();
        
        //Compute Timesteps
        float ticks = (float)SDL_GetTicks()/1000.0f;
        accumulator += ticks - last_frame_ticks;
        last_frame_ticks = ticks;

        if(accumulator < Global::FIXED_TIMESTEP) {
            //Handle state transitions
            bool transition = handleStateTransitions(state, next_state, menu, game, score);
            if(transition) {
                isfading = true;
            }
            continue;
        }
        
        //Update
        while(accumulator >= Global::FIXED_TIMESTEP) {

            if(Global::isGameState(state)) {
                game.update(Global::FIXED_TIMESTEP);
                if(game.changeLevel()) {
                    isfading = true;
                    fadingstate = state;
                }
            }

            accumulator -= Global::FIXED_TIMESTEP;
        }
        
        //Render
        if(state == Global::ProgramStates::Menu)
            menu.render();
        else if(Global::isGameState(state))
            game.render();
        else if(state == Global::ProgramStates::Score)
            score.render();

        //Handle state transitions
        bool transition = handleStateTransitions(state, next_state, menu, game, score);
        if(transition) {
            isfading = true;
        }

        //Check if done
        if(next_state == Global::ProgramStates::Quit)
            done = true;

        SDL_GL_SwapWindow(displayWindow);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    SDL_Quit();
    return 0;
}
