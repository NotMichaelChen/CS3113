#include "SheetSprite.hpp"

#include "Matrix.h"

SheetSprite::SheetSprite(unsigned int textureID, float x, float y, float spwidth, float spheight, float size, float shwidth, float shheight) :
    textureID(textureID),
    scaling(size),
    spritecoord(x,y),
    spritesize(spwidth, spheight),
    sheetsize(shwidth, shheight)
{
    texcoord = Vec(x / sheetsize.x, y / sheetsize.y);
    texsize = Vec(spritesize.x / sheetsize.x, spritesize.y / sheetsize.y);
}

unsigned int SheetSprite::getTextureID() {
    return textureID;
}

float SheetSprite::getRealWidth() {
    float aspect = texsize.x / texsize.y;
    return scaling * aspect;
}

float SheetSprite::getRealHeight() {
    return scaling;
}

void SheetSprite::setTexCoords(float x, float y) {
    spritecoord = Vec(x, y);
    texcoord = Vec(x / sheetsize.x, y / sheetsize.y);
}

void SheetSprite::Draw(ShaderProgram *program, Vec& position, float rot) {
    GLfloat texCoords[] = {
        texcoord.x, texcoord.y+texsize.y,
        texcoord.x+texsize.x, texcoord.y,
        texcoord.x, texcoord.y,
        texcoord.x+texsize.x, texcoord.y,
        texcoord.x, texcoord.y+texsize.y,
        texcoord.x+texsize.x, texcoord.y+texsize.y
    };

    float aspect = texsize.x / texsize.y;
    float vertices[] = {
        -0.5f * scaling * aspect, -0.5f * scaling,
        0.5f * scaling * aspect, 0.5f * scaling,
        -0.5f * scaling * aspect, 0.5f * scaling,
        0.5f * scaling * aspect, 0.5f * scaling,
        -0.5f * scaling * aspect, -0.5f * scaling ,
        0.5f * scaling * aspect, -0.5f * scaling};


    glBindTexture(GL_TEXTURE_2D, textureID);

    Matrix modelMatrix;
    modelMatrix.Translate(position.x, position.y, 0);
    modelMatrix.Rotate(rot);
    program->SetModelMatrix(modelMatrix);

    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);

    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}
