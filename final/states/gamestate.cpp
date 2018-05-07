#include "gamestate.hpp"

#include "global.hpp"
#include "util.hpp"
#include "SheetSprite.hpp"

GameState::GameState(ShaderProgram* prg) : program(prg), ticksactive(0), is_paused(false), background_scroll(0) {
    keys = SDL_GetKeyboardState(NULL);

    SheetSprite player_hitdot(Global::bullet_spritesheet, 16, 49, 16, 16, 0.07, 1024, 1024);
    SheetSprite playeronesprite(Global::reimu_spritesheet, 0, 0, 32, 48, 0.3, 256, 256);
    lifeonesprite = std::make_unique<SheetSprite>(Global::reimu_spritesheet, 0, 0, 32, 48, 0.3, 256, 256);
    playerone = std::make_unique<PlayerEntity>(playeronesprite, player_hitdot, keys, Global::PLAYER_ONE_CONTROLS);

    lifetwosprite = std::make_unique<SheetSprite>(Global::byakuren_spritesheet, 0, 0, 32, 48, 0.3, 256, 256);
    SheetSprite playertwosprite(Global::byakuren_spritesheet, 0, 0, 32, 48, 0.3, 256, 256);
    playertwo = std::make_unique<PlayerEntity>(playertwosprite, player_hitdot, keys, Global::PLAYER_TWO_CONTROLS);

    //enemyBlack1.png
    SheetSprite bosssprite(Global::ship_spritesheet, 423, 728, 93, 84, 0.5, 1024, 1024);
    boss = std::make_unique<BossEntity>(bosssprite, &bullets, &generators);

    //Load background texture
    background = LoadTexture("./assets/background1.png", GL_NEAREST);

    Matrix blankMatrix;
    Matrix projectionMatrix;
    projectionMatrix.SetOrthoProjection(-Global::ORTHO_X, Global::ORTHO_X, -Global::ORTHO_Y, Global::ORTHO_Y, -1.0f, 1.0f);
    //Load background program
    background_program.Load("vertex_textured.glsl", "fragment_background.glsl");
    background_program.SetProjectionMatrix(projectionMatrix);
    background_program.SetViewMatrix(blankMatrix);
    background_program.SetModelMatrix(blankMatrix);
    background_program.SetAlphaMask(0.5);

    //SetAlphaMask ends up using the program, so re-set it
    glUseProgram(program->programID);
}

void GameState::init(bool singleplayer) {
    reset();
    is_singleplayer = singleplayer;
    ticksactive = 0;
    
    if(is_singleplayer) {
        playertwo->lives = 0;
    }
}

float GameState::getSeconds() {
    return ticksactive / 60;
}

Global::ProgramStates GameState::processEvents() {
    //If we reach zero lives, exit to score state
    //Checked here since this is the method that returns where to go next
    if(playerone->lives <= 0 && playertwo->lives <= 0) {
        
        return Global::ProgramStates::Score;
    }

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
        {
            return Global::ProgramStates::Quit;
        }
        else if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                //Allow escape to exit the pause menu
                is_paused = !is_paused;
                menu_state = 0;
            }
            else if(is_paused) {
                if(event.key.keysym.scancode == SDL_SCANCODE_UP) {
                    menu_state = 0;
                }
                else if(event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                    menu_state = 1;
                }
                else if(event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                    if(menu_state == 0)
                        is_paused = false;
                    else {
                        return Global::ProgramStates::Score;
                    }
                }
            }
        }
    }
    return is_singleplayer ? Global::ProgramStates::GameOne : Global::ProgramStates::GameTwo;
}

void GameState::update(float elapsed) {
    if(is_paused)
        return;

    if(playerone->lives > 0)
        playerone->Update(elapsed);
    if(playertwo->lives > 0)
        playertwo->Update(elapsed);
    boss->Update(elapsed);

    for(size_t i = 0; i < bullets.size(); ) {
        bullets[i].Update(elapsed);

        bool collision_status_one = false;
        bool collision_status_two = false;
        bool wall_collision = bullets[i].checkWalls();

        //Collision check with playerone
        if(playerone->lives > 0) {
            collision_status_one = bullets[i].checkPlayer(*playerone);

            if(collision_status_one && !playerone->isInvinc()) {
                playerone->lives--;
                //Reset playerone position
                playerone->position.x = -1;
                playerone->position.y = -0.5;

                playerone->setInvinc();
            }
        }

        //Collision check with playertwo
        if(playertwo->lives > 0) {
            collision_status_two = bullets[i].checkPlayer(*playertwo);

            if(collision_status_two && !playertwo->isInvinc()) {
                playertwo->lives--;
                //Reset playertwo position
                playertwo->position.x = 1;
                playertwo->position.y = -0.5;

                playertwo->setInvinc();
            }
        }
        
        //Always delete bullet if it collided with something
        if(collision_status_one || collision_status_two || wall_collision) {
            //Swap index with back
            std::swap(bullets[i], bullets.back());
            //pop back
            bullets.pop_back();
            //Don't increment since there is a new element in the current index
        }
        else {
            i++;
        }
    }

    for(size_t i = 0; i < generators.size(); ) {
        generators[i].Update(elapsed);
        if(!generators[i].isAlive()) {
            //Swap index with back
            std::swap(generators[i], generators.back());
            //pop back
            generators.pop_back();
            //Don't increment since there is a new element in the current index
        }
        else
            i++;
    }

    background_scroll += elapsed/5;
    ticksactive++;
}

void GameState::render() {
    renderBackground();

    //Draw lives
    for(int i = 0; i < playerone->lives; i++) {
        Vec lifeposition(-2.8 + i*0.3, 2);
        lifeonesprite->Draw(program, lifeposition, 0);
    }

    for(int i = 0; i < playertwo->lives; i++) {
        Vec lifeposition(2.8 - i*0.3, 2);
        lifetwosprite->Draw(program, lifeposition, 0);
    }

    if(playerone->lives > 0) {
        if(playerone->isInvinc())
            program->SetAlphaMask(0.5);

        playerone->Draw(program);
        program->SetAlphaMask(1);
    }
    if(playertwo->lives > 0) {
        if(playertwo->isInvinc())
            program->SetAlphaMask(0.5);

        playertwo->Draw(program);
        program->SetAlphaMask(1);
    }

    boss->Draw(program);
    for(size_t i = 0; i < bullets.size(); i++) {
        bullets[i].Draw(program);
    }

    for(size_t i = 0; i < generators.size(); i++) {
        generators[i].Draw(program);
    }

    //Render background before rendering pause menu
    if(is_paused) {
        //Draw the menu options
        program->SetAlphaMask(1);
        DrawText(program, Global::text_spritesheet, "Give Up?", 0.3, -0.1, -0.5, 1);

        float textsize = 0.3;
        float textwidth = -0.125;

        if(menu_state != 0)
            program->SetAlphaMask(0.5);
        DrawText(program, Global::text_spritesheet, "No", textsize, textwidth, -0.5, 0);
        program->SetAlphaMask(1);

        if(menu_state != 1)
            program->SetAlphaMask(0.5);
        DrawText(program, Global::text_spritesheet, "Yes", textsize, textwidth, -0.5, -0.3);
        program->SetAlphaMask(1);
    }
}

void GameState::reset() {
    playerone->position.x = -1;
    playerone->position.y = -0.5;
    playerone->reset();
    playertwo->position.x = 1;
    playertwo->position.y = -0.5;
    playertwo->reset();

    boss->reset();
    bullets.clear();
    generators.clear();

    is_paused = false;
    menu_state = 0;
    background_scroll = 0;
}

void GameState::renderBackground() {
    GLfloat texCoords[] = {0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0};

    float vertices[] = {-3, -2.25, 3, -2.25, 3, 2.25, -3, -2.25, 3, 2.25, -3, 2.25};

    glUseProgram(background_program.programID);
    glBindTexture(GL_TEXTURE_2D, background);

    GLint scrollUniform = glGetUniformLocation(background_program.programID, "scroll");
    glUniform2f(scrollUniform, 0.0f, -background_scroll);

    glVertexAttribPointer(background_program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(background_program.positionAttribute);

    glVertexAttribPointer(background_program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(background_program.texCoordAttribute);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(background_program.positionAttribute);
    glDisableVertexAttribArray(background_program.texCoordAttribute);

    glUseProgram(program->programID);
}