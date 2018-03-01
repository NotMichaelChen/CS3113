#include "menu.hpp"

#include "util.hpp"

MainMenu::MainMenu(ShaderProgram* prg) : program(prg) {
    textureID = LoadTexture("./assets/font1.png", GL_LINEAR);
}

int MainMenu::processInput() {
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
        {
            return 0;
        }
        else if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                return 2;
            }
        }
    }
    return 1;
}

void MainMenu::render() {
    DrawText(program, textureID, "SPACE INVADERS", 0.3, -0.1, -1.2, 1);
    DrawText(program, textureID, "press enter to play", 0.2, -0.1, -0.9, 0);
}
