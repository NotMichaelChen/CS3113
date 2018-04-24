#include "gamestate.hpp"

#include "global.hpp"
#include "util.hpp"
#include "SheetSprite.hpp"

GameState::GameState(ShaderProgram* prg) : program(prg) {
    keys = SDL_GetKeyboardState(NULL);

    SheetSprite player_hitdot(Global::bullet_spritesheet, 16, 49, 16, 16, 0.1, 1024, 1024);
    //playerShip3_blue.png
    SheetSprite playersprite(Global::ship_spritesheet, 325, 739, 98, 75, 0.3, 1024, 1024);
    player = std::make_unique<PlayerEntity>(playersprite, player_hitdot, keys);

    //enemyBlack1.png
    SheetSprite bosssprite(Global::ship_spritesheet, 423, 728, 93, 84, 0.5, 1024, 1024);
    boss = std::make_unique<BossEntity>(bosssprite, &bullets);
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
    boss->Update(elapsed);
    for(size_t i = 0; i < bullets.size(); i++) {
        bullets[i].Update(elapsed);
    }
}

void GameState::render() {
    player->Draw(program);
    boss->Draw(program);
    for(size_t i = 0; i < bullets.size(); i++) {
        bullets[i].Draw(program);
    }
}