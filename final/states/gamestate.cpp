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

    background = LoadTexture("./assets/background1.png", GL_NEAREST);
    background_program.Load("vertex_textured.glsl", "fragment_background.glsl");

    Matrix projectionMatrix;
    Matrix blankMatrix;

    projectionMatrix.SetOrthoProjection(-Global::ORTHO_X, Global::ORTHO_X, -Global::ORTHO_Y, Global::ORTHO_Y, -1.0f, 1.0f);
    background_program.SetProjectionMatrix(projectionMatrix);
    background_program.SetViewMatrix(blankMatrix);
    background_program.SetModelMatrix(blankMatrix);
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

    for(size_t i = 0; i < bullets.size(); ) {
        bullets[i].Update(elapsed);
        bool delete_bullet = bullets[i].shouldDelete(*player);
        if(delete_bullet) {
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
}

void GameState::render() {
    renderBackground();

    player->Draw(program);
    boss->Draw(program);
    for(size_t i = 0; i < bullets.size(); i++) {
        bullets[i].Draw(program);
    }
}

void GameState::renderBackground() {
    GLfloat texCoords[] = {0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0};

    float vertices[] = {-3, -2.25, 3, -2.25, 3, 2.25, -3, -2.25, 3, 2.25, -3, 2.25};

    glUseProgram(background_program.programID);
    glBindTexture(GL_TEXTURE_2D, background);

    GLint scrollUniform = glGetUniformLocation(background_program.programID, "scroll");
    float ticks = (float)SDL_GetTicks()/5000.0f;
    glUniform2f(scrollUniform, 0.0f, -ticks);

    glVertexAttribPointer(background_program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(background_program.positionAttribute);

    glVertexAttribPointer(background_program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(background_program.texCoordAttribute);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(background_program.positionAttribute);
    glDisableVertexAttribArray(background_program.texCoordAttribute);

    glUseProgram(program->programID);
}