#include "gamestate.hpp"

#include "global.hpp"
#include "util.hpp"
#include "SheetSprite.hpp"

GameState::GameState(ShaderProgram* prg) : program(prg), ticks(0), is_paused(false), background_scroll(0) {
    keys = SDL_GetKeyboardState(NULL);

    SheetSprite player_hitdot(Global::bullet_spritesheet, 16, 49, 16, 16, 0.07, 1024, 1024);
    //playerShip3_blue.png
    // SheetSprite playersprite(Global::ship_spritesheet, 325, 739, 98, 75, 0.3, 1024, 1024);
    SheetSprite playersprite(Global::reimu_spritesheet, 0, 0, 32, 48, 0.3, 256, 256);
    player = std::make_unique<PlayerEntity>(playersprite, player_hitdot, keys);

    //enemyBlack1.png
    SheetSprite bosssprite(Global::ship_spritesheet, 423, 728, 93, 84, 0.5, 1024, 1024);
    boss = std::make_unique<BossEntity>(bosssprite, &bullets);

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
}

int GameState::getTicks() {
    return ticks;
}

Global::ProgramStates GameState::processEvents() {
    //If we reach zero lives, exit to score state
    //Checked here since this is the method that returns where to go next
    if(player->getLives() <= 0)
        return Global::ProgramStates::Score;

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
                        reset();
                        return Global::ProgramStates::Score;
                    }
                }
            }
        }
    }
    return Global::ProgramStates::Game;
}

void GameState::update(float elapsed) {
    if(is_paused)
        return;

    player->Update(elapsed);
    boss->Update(elapsed);

    for(size_t i = 0; i < bullets.size(); ) {
        bullets[i].Update(elapsed);

        int collision_status = bullets[i].checkCollision(*player);

        //Collision with player
        if(collision_status == 2 && !player->isInvinc()) {
            player->decLife();
            //Reset player position
            player->position.x = 1;
            player->position.y = -0.5;

            player->setInvinc();
        }
        
        //Always delete bullet if it collided with something
        if(collision_status) {
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

    background_scroll += elapsed/5;
    ticks++;
}

void GameState::render() {
    renderBackground();

    if(player->isInvinc())
        program->SetAlphaMask(0.5);

    player->Draw(program);
    program->SetAlphaMask(1);

    boss->Draw(program);
    for(size_t i = 0; i < bullets.size(); i++) {
        bullets[i].Draw(program);
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
    player->position.x = 1;
    player->position.y = -0.5;
    boss->reset();
    bullets.clear();

    is_paused = false;
    menu_state = 0;
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