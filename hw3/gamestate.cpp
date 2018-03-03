#include "gamestate.hpp"

#include "util.hpp"

GameState::GameState(ShaderProgram* p) {
    textureID = LoadTexture("./assets/sheet.png", GL_NEAREST);
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
            if(event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                if(bullets.size() < 2) {
                    //laserBlue02.png
                    SheetSprite newbulletsprite(textureID, 841, 647, 13, 37, 0.5, 1024, 1024);
                    bullets.emplace_back(newbulletsprite, player->x, player->y + 0.2);
                }
            }
        }
    }
    return 2;
}

void GameState::update(float elapsed) {
    if(keys[SDL_SCANCODE_LEFT])
        player->Move(-elapsed);
    if(keys[SDL_SCANCODE_RIGHT])
        player->Move(elapsed);

    for(auto iter = bullets.begin(); iter != bullets.end();) {
        if(!iter->Step())
            iter = bullets.erase(iter);
        else
            iter++;
    }
}

void GameState::render() {
    player->Draw(program);
    
    for(auto iter = bullets.begin(); iter != bullets.end(); iter++) {
        iter->Draw(program);
    }
}
