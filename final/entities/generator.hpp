#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "ShaderProgram.h"
#include "SheetSprite.hpp"
#include "entity.hpp"

class GeneratorEntity : public Entity {
public:
    GeneratorEntity(SheetSprite& nsprite, Vec pos, float rot, int fadein, int lifespan);
    void Update(float elapsed);
    void Draw(ShaderProgram* program);

    bool isAlive();

private:
    //How many updates have happened since object initialization
    int updateticks;
    //How many ticks it takes to fade in
    int fadein_ticks;
    //How many ticks until generator should disappear (not including fadein)
    int lifetime;
};

#endif