#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "ShaderProgram.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "shape.hpp"

SDL_Window* displayWindow;

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("Collision Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    glewInit();

    glViewport(0, 0, 1280, 720);

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

    Shape square(-2, 0, 3.1415926/4, 0.3, 4, 0.01, -0);
    Shape hexagon(2, 0, 4.013492, 0.5, 6, -0.01, 0);

    SDL_Event event;
    bool done = false;
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
                done = true;
            }
        }

        square.Update();
        hexagon.Update();

        std::pair<float, float> penetration;
        bool result = square.Collision(hexagon, penetration);

        square.Draw(program);
        hexagon.Draw(program);

        SDL_GL_SwapWindow(displayWindow);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    SDL_Quit();
    return 0;
}
