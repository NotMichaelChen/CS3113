#include "player.hpp"

#include "../util.hpp"

PlayerEntity::PlayerEntity(SheetSprite& nsprite, const Uint8* k) : Entity(1, -0.5, 0, false, nsprite), keys(k) {
    velcap[0] = 25;
    velcap[1] = 25;
    friction[0] = 4;
    acceleration[1] = -10;
    onground = false;
}

void PlayerEntity::Update(float elapsed) {
    if(keys[SDL_SCANCODE_LEFT]) {
        acceleration[0] = -15;
    }
    else if(keys[SDL_SCANCODE_RIGHT]) {
        acceleration[0] = 15;
    }
    else {
        acceleration[0] = 0;
    }

    if(keys[SDL_SCANCODE_SPACE]) {
        if(onground)
            velocity[1] = 6;
    }

    Entity::Update(elapsed);
}

void PlayerEntity::CheckCollision(TileMap& tilemap) {
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
            onground = true;
        }
        else {
            onground = false;
        }
    }
    else {
        onground = false;
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
            velocity[0] = 0;
        }
    }
    //Collision on right
    inbounds = inBoundsTilemap(tileright.second, tileright.first, dataref);
    if(inbounds && dataref[tileright.second][tileright.first] >= 0) {
        if(position[0] + size[0]/2 > tilesize * tileright.first) {
            float diff = (position[0] + size[0]/2) - (tilesize * tileright.first);
            position[0] -= diff;
            velocity[0] = 0;
        }
    }
}