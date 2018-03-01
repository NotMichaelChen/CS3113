#include "gamestate.hpp"

#include "util.hpp"

GameState::GameState() {
    GLuint textureID = LoadTexture("./assets/sheet.png", GL_NEAREST);
    //playerShip3_blue.png
    SheetSprite playersprite(textureID, 325, 739, 98, 75, 0.2, 1024, 1024);
    player = std::make_shared<PlayerEntity>(playersprite);
}
