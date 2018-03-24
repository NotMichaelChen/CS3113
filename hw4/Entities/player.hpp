#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include <SDL.h>

#include "../tilemap.hpp"
#include "entity.hpp"

class PlayerEntity : public Entity {
public:
    PlayerEntity(SheetSprite& nsprite, const Uint8* k);
    virtual void Update(float elapsed);
    void CheckCollision(TileMap& tilemap);

private:
    const Uint8* keys;
};

#endif
