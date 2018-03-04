#include "gamestate.hpp"

#include "util.hpp"

GameState::GameState(ShaderProgram* p) {
    textureID = LoadTexture("./assets/sheet.png", GL_NEAREST);
    //playerShip3_blue.png
    SheetSprite playersprite(textureID, 325, 739, 98, 75, 0.35, 1024, 1024);
    player = std::make_shared<PlayerEntity>(playersprite);

    //enemyBlack1.png
    SheetSprite enemysprite(textureID, 423, 728, 93, 84, 0.35, 1024, 1024);
    float enemyy = 1.75;
    for(int i = 0; i < 5; i++) {
        float enemyx = -3;
        for(int j = 0; j < 5; j++) {
            enemies.emplace_back(enemysprite, enemyx, enemyy);
            enemyx += 0.7;
        }
        enemyy -= 0.45;
    }

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
                    SheetSprite newbulletsprite(textureID, 841, 647, 13, 37, 0.3, 1024, 1024);
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

    //Update bullets
    for(auto iter = bullets.begin(); iter != bullets.end();) {
        if(!iter->Step(elapsed))
            iter = bullets.erase(iter);
        else
            iter++;
    }

    bool is_shift = false;

    //Update enemies
    for(auto iter = enemies.begin(); iter != enemies.end();) {
        //Edge has been hit
        if(iter->MoveAcross(elapsed)) {
            //Delay shift until end of update to avoid desyncing enemies
            is_shift = true;
            iter++;
        }
        else {
            iter++;
        }
    }
    if(is_shift) {
        //Shift all enemies down
        for(auto shiftiter = enemies.begin(); shiftiter != enemies.end(); shiftiter++) {
            shiftiter->ShiftDown();
        }
    }
}

void GameState::render() {
    //Draw player
    player->Draw(program);

    //Draw bullets
    for(auto bulletiter = bullets.begin(); bulletiter != bullets.end(); bulletiter++) {
        bulletiter->Draw(program);
    }

    //Draw enemies
    for(auto enemyiter = enemies.begin(); enemyiter != enemies.end(); enemyiter++) {
        enemyiter->Draw(program);
    }
}
