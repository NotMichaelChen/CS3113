#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <vector>

#include "ShaderProgram.h"
#include "SheetSprite.hpp"
#include "entity.hpp"
#include "bullet.hpp"

class GeneratorEntity : public Entity {
public:
    GeneratorEntity(SheetSprite& nsprite, SheetSprite bsprite, Vec pos, float rot, int fadein, int lifespan, int rate,
        std::vector<Bullet>* b);
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
    //How often the generator activates (how many ticks between activations)
    int firerate;

    std::vector<Bullet>* bullets;

    SheetSprite bulletsprite;
};

#endif