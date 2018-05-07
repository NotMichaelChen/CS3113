#include "generator.hpp"

#include "phases/patterns/patterns.hpp"

GeneratorEntity::GeneratorEntity(SheetSprite& nsprite, SheetSprite bsprite, Vec pos, float rot, int fadein, int lifespan,
    int rate, std::vector<Bullet>* b) :
    Entity(pos.x, pos.y, rot, nsprite), updateticks(0), fadein_ticks(fadein), lifetime(lifespan), firerate(rate),
    bullets(b), bulletsprite(bsprite)
{
}

void GeneratorEntity::Update(float elapsed) {
    if(updateticks > fadein_ticks) {
        if(updateticks % firerate == 0) {
            std::vector<Bullet> generated = generateFountain(bulletsprite, position, 0.5, 4);
            bullets->insert(bullets->end(), generated.begin(), generated.end());
        }
    }
    
    updateticks++;
}

void GeneratorEntity::Draw(ShaderProgram* program) {
    if(updateticks < fadein_ticks) {
        program->SetAlphaMask((float)updateticks/fadein_ticks);
    }

    Entity::Draw(program);

    program->SetAlphaMask(1);
}

bool GeneratorEntity::isAlive() {
    return updateticks <= lifetime + fadein_ticks;
}