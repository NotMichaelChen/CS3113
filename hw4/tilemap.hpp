#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <vector>

#include "ShaderProgram.h"

class TileMap {
public:
    TileMap(std::vector<std::vector<unsigned int>> data, unsigned int tID, float tsize, unsigned int countx, unsigned int county, unsigned int sizex, unsigned int sizey);
    void Draw(ShaderProgram *program);

private:
    std::vector<std::vector<unsigned int>> levelData;
    unsigned int textureID;
    float tilesize;
    //The amount of sprites in the x/y dimension in the tilemap
    unsigned int spritecountX;
    unsigned int spritecountY;

    unsigned int sheetx;
    unsigned int sheety;
};

#endif