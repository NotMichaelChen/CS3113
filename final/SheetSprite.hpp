#ifndef SHEETSPRITE_H
#define SHEETSPRITE_H

#include "ShaderProgram.h"
#include "vec.hpp"

class SheetSprite {
public:
    //This x,y are the coordinates in the texture sheet, not the location in the game window
    SheetSprite(unsigned int textureID, float x, float y, float spritewidth, float spriteheight, float size, float sheetwidth, float sheetheight);

    unsigned int getTextureID();
    float getRealWidth();
    float getRealHeight();

    void Draw(ShaderProgram *program, Vec& position, float rot);

    unsigned int textureID;
    float u;
    float v;
    float width;
    float height;
    float size;
};

#endif
