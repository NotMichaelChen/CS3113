#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "ShaderProgram.h"
#include "SheetSprite.hpp"
#include "vec.hpp"

class Entity {
public:
    //This x,y are the actual locations in the window
    Entity(float nx, float ny, float nr, SheetSprite& nsprite);
    void Update(float elapsed);
    void Draw(ShaderProgram* program);

    Vec position;
    Vec size;
    Vec velocity;
    Vec acceleration;

    float rotation;
private:
    SheetSprite sprite;
};

#endif
