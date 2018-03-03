#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../ShaderProgram.h"
#include "../SheetSprite.hpp"

class Entity {
public:
    //This x,y are the actual locations in the window
    Entity(float nx, float ny, float nr, SheetSprite& nsprite);
    void Draw(ShaderProgram* program);

    float x;
    float y;
    float rotation;
    
    float velocity_x;
    float velocity_y;
private:
    SheetSprite sprite;
};

#endif
