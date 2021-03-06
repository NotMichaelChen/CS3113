#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "paddle.hpp"
#include "ball.hpp"

#include "ShaderProgram.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

SDL_Window *displayWindow;

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
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
    program.Load("vertex.glsl", "fragment.glsl");
    program.SetColor(1, 1, 1, 1);
    glUseProgram(program.programID);

    //Declare matrices
    Matrix projectionMatrix;
    Matrix viewMatrix;

    projectionMatrix.SetOrthoProjection(-3.55, 3.55, -2.0f, 2.0f, -1.0f, 1.0f);
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);

    //Create entities
    Paddle leftpaddle(true);
    Paddle rightpaddle(false);
    Ball ball;

    float lastFrameTicks = 0.0f;
    SDL_Event event;
    bool done = false;
    while (!done)
    {
        float ticks = (float)SDL_GetTicks()/1000.0f;
        float elapsed = ticks - lastFrameTicks;
        lastFrameTicks = ticks;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
            {
                done = true;
            }
        }

        if(keys[SDL_SCANCODE_UP])
            rightpaddle.Move(elapsed);
        if(keys[SDL_SCANCODE_DOWN])
            rightpaddle.Move(-elapsed);
        if(keys[SDL_SCANCODE_W])
            leftpaddle.Move(elapsed);
        if(keys[SDL_SCANCODE_S])
            leftpaddle.Move(-elapsed);
        
        bool success = ball.Step(elapsed);
        if(!success)
            glClearColor(1, 0, 0, 1);
        ball.CheckPaddle(leftpaddle);
        ball.CheckPaddle(rightpaddle);

        glClear(GL_COLOR_BUFFER_BIT);

        leftpaddle.Draw(program);
        rightpaddle.Draw(program);
        ball.Draw(program);

        SDL_GL_SwapWindow(displayWindow);
    }

    SDL_Quit();
    return 0;
}
