#ifndef ENTITY_H
#define ENTITY_H

#include "ShaderProgram.h"

class Entity {
public:
    Entity(float nx, float ny, float nr, float nw, float nh);
    void Draw(ShaderProgram& program);

    float x;
    float y;
    float rotation;

    float width;
    float height;
    
    float velocity_x;
    float velocity_y;
};

#endif