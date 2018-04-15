#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "ShaderProgram.h"
#include "SheetSprite.hpp"

class Entity {
public:
    //This x,y are the actual locations in the window
    Entity(float nx, float ny, float nr, SheetSprite& nsprite);
    virtual void Update(float elapsed);
    void Draw(ShaderProgram* program);

    float position[2];
    float size[2];
    float velocity[2];

    float rotation;
private:
    SheetSprite sprite;
};

#endif
