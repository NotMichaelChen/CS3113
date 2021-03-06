#include "star.hpp"

#include "../util.hpp"

StarEntity::StarEntity(SheetSprite& nsprite, int x, int y) : Entity(x, y, 0, false, nsprite) {
    velocity[0] = 1;
    velcap[0] = 25;
    velcap[1] = 25;
    acceleration[1] = -10;
    show = true;
}

void StarEntity::CheckTileCollision(TileMap& tilemap) {
    float tilesize = tilemap.GetTileSize();

    //Get grid coordinates for the player's top, left, right, and bottom
    std::vector<std::pair<int, int>> gridcoords;
    //top
    std::pair<int, int> tiletop = worldToTileCoordinates(position[0], position[1] + size[1]/2, tilesize);
    //bottom
    std::pair<int, int> tilebottom = worldToTileCoordinates(position[0], position[1] - size[1]/2, tilesize);
    //left
    std::pair<int, int> tileleft = worldToTileCoordinates(position[0] - size[0]/2, position[1], tilesize);
    //right
    std::pair<int, int> tileright = worldToTileCoordinates(position[0] + size[0]/2, position[1], tilesize);

    auto dataref = tilemap.GetData();
    bool inbounds;

    //Collision on bottom
    inbounds = inBoundsTilemap(tilebottom.second, tilebottom.first, dataref);
    if(inbounds && dataref[tilebottom.second][tilebottom.first] >= 0) {
        if(position[1] - size[1]/2 < -tilesize * tilebottom.second) {
            float diff = (-tilesize * tilebottom.second) - (position[1] - size[1]/2);
            position[1] += diff;
            velocity[1] = 0;
        }
    }
    //Collision on top
    inbounds = inBoundsTilemap(tiletop.second, tiletop.first, dataref);
    if(inbounds && dataref[tiletop.second][tiletop.first] >= 0) {
        if(position[1] + size[1]/2 > (-tilesize * tiletop.second) - tilesize) {
            float diff = (position[1] + size[1]/2) - ((-tilesize * tiletop.second) - tilesize);
            position[1] -= diff;
            velocity[1] = 0;
        }
    }
    //Collision on left
    inbounds = inBoundsTilemap(tileleft.second, tileleft.first, dataref);
    if(inbounds && dataref[tileleft.second][tileleft.first] >= 0) {
        if(position[0] - size[0]/2 < (tilesize * tileleft.first) + tilesize) {
            float diff = ((tilesize * tileleft.first) + tilesize) - (position[0] - size[0]/2);
            position[0] += diff;
            velocity[0] = -velocity[0];
        }
    }
    //Collision on right
    inbounds = inBoundsTilemap(tileright.second, tileright.first, dataref);
    if(inbounds && dataref[tileright.second][tileright.first] >= 0) {
        if(position[0] + size[0]/2 > tilesize * tileright.first) {
            float diff = (position[0] + size[0]/2) - (tilesize * tileright.first);
            position[0] -= diff;
            velocity[0] = -velocity[0];
        }
    }
}