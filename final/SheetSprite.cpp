#include "SheetSprite.hpp"

#include "Matrix.h"

SheetSprite::SheetSprite(unsigned int textureID, float x, float y, float spritewidth, float spriteheight, float size, float sheetwidth, float sheetheight) :
    textureID(textureID),
    size(size)
{
    u = x / sheetwidth;
    v = y / sheetheight;
    width = spritewidth / sheetwidth;
    height = spriteheight / sheetheight;
}

unsigned int SheetSprite::getTextureID() {
    return textureID;
}

float SheetSprite::getRealWidth() {
    float aspect = width / height;
    return size * aspect;
}

float SheetSprite::getRealHeight() {
    return size;
}

void SheetSprite::Draw(ShaderProgram *program, float x, float y, float rot) {
    GLfloat texCoords[] = {
        u, v+height,
        u+width, v,
        u, v,
        u+width, v,
        u, v+height,
        u+width, v+height
    };

    float aspect = width / height;
    float vertices[] = {
        -0.5f * size * aspect, -0.5f * size,
        0.5f * size * aspect, 0.5f * size,
        -0.5f * size * aspect, 0.5f * size,
        0.5f * size * aspect, 0.5f * size,
        -0.5f * size * aspect, -0.5f * size ,
        0.5f * size * aspect, -0.5f * size};


    glBindTexture(GL_TEXTURE_2D, textureID);

    Matrix modelMatrix;
    modelMatrix.Translate(x, y, 0);
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
