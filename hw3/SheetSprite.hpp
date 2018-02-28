#ifndef SHEETSPRITE_H
#define SHEETSPRITE_H

#include "ShaderProgram.h"

class SheetSprite {
public:
    SheetSprite(unsigned int textureID, float u, float v, float width, float height, float size);

    void Draw(ShaderProgram *program, float x, float y, float rot);

    float size;
    unsigned int textureID;
    float u;
    float v;
    float width;
    float height;
};

#endif