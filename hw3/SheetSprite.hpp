#ifndef SHEETSPRITE_H
#define SHEETSPRITE_H

#include "ShaderProgram.h"

class SheetSprite {
public:
    //This x,y are the coordinates in the texture sheet, not the location in the game window
    SheetSprite(unsigned int textureID, float x, float y, float spritewidth, float spriteheight, float size, float sheetwidth, float sheetheight);


    void Draw(ShaderProgram *program, float x, float y, float rot);

    unsigned int textureID;
    float u;
    float v;
    float width;
    float height;
    float size;
};

#endif
