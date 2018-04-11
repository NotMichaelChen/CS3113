#include "menustate.hpp"

#include "util.hpp"

MenuState::MenuState(ShaderProgram* prg) {
    text_textureID = LoadTexture("./assets/font1.png", GL_LINEAR);
    program = prg;
}

int MenuState::processEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
        {
            return 0;
        }
        else if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                return 1;
            }
        }
    }
    return 1;
}

void MenuState::update() {

}

void MenuState::render() {
    DrawText(program, text_textureID, "SPACE INVADERS", 0.3, -0.1, -1.25, 1);
    program->SetAlphaMask(0.5);
    DrawText(program, text_textureID, "press enter to play", 0.2, -0.1, -0.9, 0);
    program->SetAlphaMask(1);
}
