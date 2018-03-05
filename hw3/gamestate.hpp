#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <memory>
#include <vector>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "./Entities/player.hpp"
#include "./Entities/bullet.hpp"
#include "./Entities/enemy.hpp"

class GameState {
public:
    GameState(ShaderProgram* p);

    int processEvents();
    //Returns whether the player won or lost, or nothing happened
    //0 = nothing, 1 = win, 2 = lose
    int update(float elapsed);
    void render();

    void reset();
    
private:
    //A little overkill for this homework, but making player a smart pointer allows me to defer construction until the
    //constructor body. This lets me load the sprite before constructing the player
    std::shared_ptr<PlayerEntity> player;
    //Two vectors for bullets to distinguish enemy bullets from player bullets
    std::vector<Bullet> bullets;
    std::vector<Bullet> enemybullets;
    std::vector<EnemyEntity> enemies;

    GLuint textureID;
    const Uint8 *keys;
    ShaderProgram* program;
};

#endif
