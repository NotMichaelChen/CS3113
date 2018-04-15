#include "gamestate.hpp"

#include "util.hpp"
#include "SheetSprite.hpp"

GameState::GameState(ShaderProgram* prg) : program(prg) {
    keys = SDL_GetKeyboardState(NULL);

    ship_spritesheet = LoadTexture("./assets/sheet.png", GL_NEAREST);
    //playerShip3_blue.png
    SheetSprite playersprite(ship_spritesheet, 325, 739, 98, 75, 0.35, 1024, 1024);
    player = std::make_shared<PlayerEntity>(playersprite, keys);
}

Global::ProgramStates GameState::processEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
        {
            return Global::ProgramStates::Quit;
        }
        else if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                return Global::ProgramStates::Menu;
            }
        }
    }
    return Global::ProgramStates::Game;
}

void GameState::update(float elapsed) {
    player->Update(elapsed);
}

void GameState::render() {
    player->Draw(program);
}