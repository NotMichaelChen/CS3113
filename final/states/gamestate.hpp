#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include <memory>
#include <vector>

#include "global.hpp"
#include "ShaderProgram.h"
#include "entities/player.hpp"
#include "entities/boss.hpp"
#include "entities/generator.hpp"

class GameState {
public:
    GameState(ShaderProgram* prg);
    void init(bool singleplayer);
    Global::ProgramStates processEvents();
    void update(float elapsed);
    void render();

    void reset();
    void toNextLevel();
    float getSeconds();
    int getLevel();
    bool changeLevel();

private:

    void renderBackground();
    
    ShaderProgram* program;
    ShaderProgram background_program;
    const Uint8* keys;
    bool is_paused;
    //0=no, 1=yes
    int menu_state;
    float background_scroll;
    bool is_singleplayer;

    //Making player a smart pointer allows me to defer construction until the constructor body. This lets me load the sprite
    //before constructing the player
    std::unique_ptr<PlayerEntity> playerone;
    std::unique_ptr<PlayerEntity> playertwo;
    std::unique_ptr<BossEntity> boss;
    std::vector<Bullet> bullets;
    std::vector<GeneratorEntity> generators;

    GLuint background;
    std::unique_ptr<SheetSprite> lifeonesprite;
    std::unique_ptr<SheetSprite> lifetwosprite;
};

#endif