#include "tilemap.hpp"

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

#include "Matrix.h"

TileMap::TileMap(std::vector<std::vector<unsigned int>> data, unsigned int tID, float tsize, unsigned int countx, unsigned int county, unsigned int sizex, unsigned int sizey) :
    levelData(data),
    textureID(tID),
    tilesize(tsize),
    spritecountX(countx),
    spritecountY(county),
    sheetx(sizex),
    sheety(sizey)
{
}

void TileMap::Draw(ShaderProgram *program) {
    unsigned int tiles = 0;

    std::vector<float> vertexData;
    std::vector<float> texCoordData;
    for(int y=0; y < levelData.size(); y++) {
        for(int x=0; x < levelData[y].size(); x++) {
            //if(levelData[y][x] != 0) {

                float u = (levelData[y][x] % spritecountX) * tilesize / sheetx;
                float v = (levelData[y][x] / spritecountX) * tilesize / sheety;
                
                //float u = (float)(((int)levelData[y][x]) % spritecountX) / (float) spritecountX;
                //float v = (float)(((int)levelData[y][x]) / spritecountX) / (float) spritecountY;

                float spriteHeight = tilesize / sheetx;
                float spriteWidth = tilesize / sheety;

                // float spriteWidth = 1.0f/(float)spritecountX;
                // float spriteHeight = 1.0f/(float)spritecountY;

                float scale = 0.5;
                vertexData.insert(vertexData.end(), {
                    // tilesize * x, -tilesize * y,
                    // tilesize * x, (-tilesize * y)-tilesize,
                    // (tilesize * x)+tilesize, (-tilesize * y)-tilesize,

                    // tilesize * x, -tilesize * y,
                    // (tilesize * x)+tilesize, (-tilesize * y)-tilesize,
                    // (tilesize * x)+tilesize, -tilesize * y
                    scale * x, -scale * y,
                    scale * x, (-scale * y)-scale,
                    (scale * x)+scale, (-scale * y)-scale,

                    scale * x, -scale * y,
                    (scale * x)+scale, (-scale * y)-scale,
                    (scale * x)+scale, -scale * y
                });

                texCoordData.insert(texCoordData.end(), {
                    u, v,
                    u, v+(spriteHeight),
                    u+spriteWidth, v+(spriteHeight),
                    
                    u, v,
                    u+spriteWidth, v+(spriteHeight),
                    u+spriteWidth, v
                });

                tiles++;
            //}
        }
    }
    Matrix modelMatrix;
    modelMatrix.Identity();
    program->SetModelMatrix(modelMatrix);

    glBindTexture(GL_TEXTURE_2D, textureID);

    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertexData.data());
    glEnableVertexAttribArray(program->positionAttribute);

    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoordData.data());
    glEnableVertexAttribArray(program->texCoordAttribute);
    glDrawArrays(GL_TRIANGLES, 0, tiles*6);
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}