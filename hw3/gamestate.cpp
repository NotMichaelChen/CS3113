#include "gamestate.hpp"

#include "util.hpp"

GameState::GameState(ShaderProgram* p) {
    GLuint textureID = LoadTexture("./assets/sheet.png", GL_NEAREST);
    //playerShip3_blue.png
    SheetSprite playersprite(textureID, 325, 739, 98, 75, 0.35, 1024, 1024);
    player = std::make_shared<PlayerEntity>(playersprite);

    //Initialize keystate array
    keys = SDL_GetKeyboardState(NULL);
    program = p;
}

int GameState::processEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
        {
            return 0;
        }
        else if(event.type == SDL_KEYDOWN) {
        }
    }
    return 2;
}

void GameState::update(float elapsed) {
    if(keys[SDL_SCANCODE_LEFT])
        player->Move(-elapsed);
    if(keys[SDL_SCANCODE_RIGHT])
        player->Move(elapsed);
}

void GameState::render() {
    player->Draw(program);
}
