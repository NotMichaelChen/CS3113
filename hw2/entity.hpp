#ifndef ENTITY_HPP
#define ENTITY_HPP

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