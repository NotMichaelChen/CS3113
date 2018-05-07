#include "scorestate.hpp"

#include "util.hpp"

ScoreState::ScoreState(ShaderProgram* prg) : seconds(0), is_win(false), program(prg) {
    background = LoadTexture("./assets/gameover.jpg", GL_LINEAR);
}

void ScoreState::setSeconds(float t) {
    if(t < 0) {
        is_win = true;
    }
    else {
        seconds = (int)t;
    }
}

Global::ProgramStates ScoreState::processEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
        {
            return Global::ProgramStates::Quit;
        }
        else if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                return Global::ProgramStates::Menu;
            }
        }
    }
    return Global::ProgramStates::Score;
}

void ScoreState::render() {
    renderBackground();

    if(is_win) {
        DrawText(program, Global::text_spritesheet, "YOU WIN", 0.3, -0.1, 0, 0);
    }
    else {
        DrawText(program, Global::text_spritesheet, "GAME OVER", 0.3, -0.1, -0.8, 1);

        std::string message = "You lasted " + std::to_string(seconds) + " seconds";
        DrawText(program, Global::text_spritesheet, message, 0.25, -0.11, -1.4, 0.3);
    }

    DrawText(program, Global::text_spritesheet, "Press Enter to return to the menu", 0.25, -0.11, -2.2, -0.5);
}

void ScoreState::renderBackground() {
    program->SetAlphaMask(0.3);

    GLfloat texCoords[] = {0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0};

    float vertices[] = {-3, -2.25, 3, -2.25, 3, 2.25, -3, -2.25, 3, 2.25, -3, 2.25};

    glBindTexture(GL_TEXTURE_2D, background);

    Matrix blankMatrix;
    program->SetModelMatrix(blankMatrix);

    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);

    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);

    program->SetAlphaMask(1);
}