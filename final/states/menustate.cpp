#include "menustate.hpp"

#include "util.hpp"

MenuState::MenuState(ShaderProgram* prg) : current_state(0) {
    text_textureID = LoadTexture("./assets/font2.png", GL_LINEAR);
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
    //Draw title
    DrawText(program, text_textureID, "BULLET HELL DEMO", 0.3, -0.1, -1.5, 1.8);

    float textsize = 0.3;
    float textwidth = -0.125;

    if(current_state != MenuOptions::start)
        program->SetAlphaMask(0.5);
    DrawText(program, text_textureID, "Start", textsize, textwidth, -3, 0);
    program->SetAlphaMask(1);

    if(current_state != MenuOptions::quit)
        program->SetAlphaMask(0.5);
    DrawText(program, text_textureID, "Quit", textsize, textwidth, -3, -0.3);
    program->SetAlphaMask(1);
}

Global::ProgramStates MenuState::optionAction() {
    switch(current_state) {

    case MenuOptions::start:
        return Global::ProgramStates::Game;

    case MenuOptions::quit:
        return Global::ProgramStates::Quit;
    //Quit if menu state is invalid
    default:
        return Global::ProgramStates::Quit;
    }
}