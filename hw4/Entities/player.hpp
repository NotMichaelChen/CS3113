#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include "entity.hpp"

class PlayerEntity : public Entity {
public:
    PlayerEntity(SheetSprite& nsprite);
    void Move(float amount);
};

#endif
