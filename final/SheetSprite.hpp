#ifndef SHEETSPRITE_H
#define SHEETSPRITE_H

#include "ShaderProgram.h"
#include "vec.hpp"

class SheetSprite {
public:
    //This x,y are the coordinates in the texture sheet, not the location in the game window
    SheetSprite(unsigned int textureID, float x, float y, float spwidth, float spheight, float size, float shwidth, float shheight);

    unsigned int getTextureID();
    float getRealWidth();
    float getRealHeight();

    //This x,y are coordinates in texture sheet
    void setTexCoords(float x, float y);

    void Draw(ShaderProgram *program, Vec& position, float rot);

    unsigned int textureID;
    Vec texcoord;
    Vec texsize;
    float scaling;

    //represented as pixels
    Vec spritecoord;
    Vec spritesize;
    Vec sheetsize;
};

#endif
