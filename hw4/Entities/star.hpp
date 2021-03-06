#ifndef STAR_HPP
#define STAR_HPP

#include "entity.hpp"
#include "../tilemap.hpp"

class StarEntity : public Entity {
public:
    StarEntity(SheetSprite& nsprite, int x, int y);
    void CheckTileCollision(TileMap& tilemap);

    bool show;
};

#endif