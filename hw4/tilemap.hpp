#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <vector>

#include "ShaderProgram.h"

class TileMap {
public:
    TileMap(std::vector<std::vector<int>> data, unsigned int tID, float tsize, unsigned int countx, unsigned int county);
    void Draw(ShaderProgram *program);

private:
    std::vector<std::vector<int>> levelData;
    unsigned int textureID;
    float tilesize;
    //The amount of sprites in the x/y dimension in the tilemap
    unsigned int spritecountX;
    unsigned int spritecountY;
};

#endif