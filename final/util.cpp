#include "util.hpp"

#include <vector>
#include <cmath>
#include <random>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint LoadTexture(const char *filepath, GLint filtering) {
    int w,h,comp;
    unsigned char* image = stbi_load(filepath, &w, &h, &comp, STBI_rgb_alpha);
    if(image == NULL) {
        std::cout << "Unable to load image. Make sure the path is correct\n";
        assert(false);
    }
    GLuint retTexture;
    glGenTextures(1, &retTexture);
    glBindTexture(GL_TEXTURE_2D, retTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);

    stbi_image_free(image);
    return retTexture;
}

void DrawText(ShaderProgram *program, int fontTexture, std::string text, float size, float spacing, float x, float y) {
    float texture_size = 1.0/16.0f;

    std::vector<float> vertexData;
    std::vector<float> texCoordData;

    for(size_t i=0; i < text.size(); i++) {

        int spriteIndex = (int)text[i];

        float texture_x = (float)(spriteIndex % 16) / 16.0f;
        float texture_y = (float)(spriteIndex / 16) / 16.0f;

        vertexData.insert(vertexData.end(), {
            ((size+spacing) * i) + (-0.5f * size), 0.5f * size,
            ((size+spacing) * i) + (-0.5f * size), -0.5f * size,
            ((size+spacing) * i) + (0.5f * size), 0.5f * size,
            ((size+spacing) * i) + (0.5f * size), -0.5f * size,
            ((size+spacing) * i) + (0.5f * size), 0.5f * size,
            ((size+spacing) * i) + (-0.5f * size), -0.5f * size,
        });
        texCoordData.insert(texCoordData.end(), {
            texture_x, texture_y,
            texture_x, texture_y + texture_size,
            texture_x + texture_size, texture_y,
            texture_x + texture_size, texture_y + texture_size,
            texture_x + texture_size, texture_y,
            texture_x, texture_y + texture_size,
        });
    }
    glBindTexture(GL_TEXTURE_2D, fontTexture);

    Matrix modelMatrix;
    modelMatrix.Translate(x, y, 0);
    program->SetModelMatrix(modelMatrix);
    
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertexData.data());
    glEnableVertexAttribArray(program->positionAttribute);

    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoordData.data());
    glEnableVertexAttribArray(program->texCoordAttribute);
    glDrawArrays(GL_TRIANGLES, 0, text.length() * 6);
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}

void clamp(int& test, int lo, int hi) {
    test = test < lo ? lo : test > hi ? hi : test;
}

float dist(Vec a, Vec b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

float randFloat(float lo, float hi) {
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_real_distribution<> distr(lo, hi);

    return distr(engine);
}

int randInt(int lo, int hi) {
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<> distr(lo, hi);

    return distr(engine);
}