#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <memory>

#include "player.hpp"

class GameState {
public:
    GameState();
private:
    //A little overkill for this homework, but making player a smart pointer allows me to defer construction until the
    //constructor body. This lets me load the sprite before constructing the player
    std::shared_ptr<PlayerEntity> player;
};

#endif
