#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include <SDL.h>

#include "entity.hpp"

class PlayerEntity : public Entity {
public:
    PlayerEntity(SheetSprite& nsprite, const Uint8* k);
    virtual void Update(float elapsed);

private:
    const float fast_speed = 2.5;
    const float slow_speed = 0.7;
    const Uint8* keys;
};

#endif
