#include "menustate.hpp"

#include "util.hpp"

MenuState::MenuState(ShaderProgram* prg) : current_state(0) {
    background = LoadTexture("./assets/title.jpg", GL_LINEAR);
    program = prg;
}

Global::ProgramStates MenuState::processEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
        {
            return Global::ProgramStates::Quit;
        }
        else if(event.type == SDL_KEYDOWN) {
            if(event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                return optionAction();
            }
            else if(event.key.keysym.scancode == SDL_SCANCODE_UP) {
                current_state--;
                clamp(current_state, 0, MenuOptions_Entries-1);
            }
            else if(event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                current_state++;
                clamp(current_state, 0, MenuOptions_Entries-1);
            }
        }
    }
    return Global::ProgramStates::Menu;
}

void MenuState::render() {
    renderBackground();

    //Draw title
    DrawText(program, Global::text_spritesheet, "BULLET HELL DEMO", 0.3, -0.1, -1.5, 1.8);

    float textsize = 0.3;
    float textwidth = -0.125;

    if(current_state != MenuOptions::oneplayer)
        program->SetAlphaMask(0.5);
    DrawText(program, Global::text_spritesheet, "Single Player", textsize, textwidth, -2.5, 0);
    program->SetAlphaMask(1);

    if(current_state != MenuOptions::twoplayer)
        program->SetAlphaMask(0.5);
    DrawText(program, Global::text_spritesheet, "Two Player", textsize, textwidth, -2.5, -0.3);
    program->SetAlphaMask(1);

    if(current_state != MenuOptions::quit)
        program->SetAlphaMask(0.5);
    DrawText(program, Global::text_spritesheet, "Quit", textsize, textwidth, -2.5, -0.6);
    program->SetAlphaMask(1);
}

void MenuState::renderBackground() {
    program->SetAlphaMask(0.5);

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

Global::ProgramStates MenuState::optionAction() {
    switch(current_state) {

    case MenuOptions::oneplayer:
        return Global::ProgramStates::GameOne;

    case MenuOptions::twoplayer:
        return Global::ProgramStates::GameTwo;

    case MenuOptions::quit:
        return Global::ProgramStates::Quit;
    //Quit if menu state is invalid
    default:
        return Global::ProgramStates::Quit;
    }
}