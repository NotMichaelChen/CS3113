#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "ShaderProgram.h"
#include "Matrix.h"

#include "Entities/player.hpp"
#include "util.hpp"

SDL_Window* displayWindow;

const float FIXED_TIMESTEP = 0.0166666;

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Platformer Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
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

    //Create textures from sprite sheets
    GLuint playertextureID = LoadTexture("./assets/p1_spritesheet.png", GL_NEAREST);

    //Create sprites
    SheetSprite playersprite(playertextureID, 67, 196, 66, 92, 1, 512, 512);

    //Create entities
    PlayerEntity player(playersprite);

    SDL_Event event;
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    float lastFrameTicks = 0;
    bool done = false;
    float accumulator = 0;

    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                done = true;
            }
        }
        
        glClear(GL_COLOR_BUFFER_BIT);

        float ticks = (float)SDL_GetTicks()/1000.0f;
        accumulator += ticks - lastFrameTicks;
        lastFrameTicks = ticks;

        if(accumulator < FIXED_TIMESTEP)
            continue;

        //UPDATE
        while(accumulator >= FIXED_TIMESTEP) {
            if(keys[SDL_SCANCODE_LEFT]) {
                player.Move(-FIXED_TIMESTEP);
            }
            if(keys[SDL_SCANCODE_RIGHT]) {
                player.Move(FIXED_TIMESTEP);
            }
            accumulator -= FIXED_TIMESTEP;
        }

        player.Draw(&program);

        SDL_GL_SwapWindow(displayWindow);
    }

    SDL_Quit();
    return 0;
}
