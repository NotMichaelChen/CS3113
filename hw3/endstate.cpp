#include "endstate.hpp"

#include "util.hpp"

EndState::EndState(ShaderProgram* prg) : program(prg) {
    textureID = LoadTexture("./assets/font1.png", GL_LINEAR);
}

int EndState::processEvents() {
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
    return 3;
}

void EndState::render(bool won) {
    if(won)
        DrawText(program, textureID, "YOU WIN", 0.3, -0.1, -0.65, 1);
    else
        DrawText(program, textureID, "YOU LOSE", 0.3, -0.1, -0.7, 1);
        
    DrawText(program, textureID, "press enter to play again", 0.2, -0.1, -1.25, 0);
}
