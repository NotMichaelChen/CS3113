#include "generator.hpp"

GeneratorEntity::GeneratorEntity(SheetSprite& nsprite, Vec pos, float rot, int fadein, int lifespan) :
    Entity(pos.x, pos.y, rot, nsprite), updateticks(0), fadein_ticks(fadein), lifetime(lifespan)
{
}

void GeneratorEntity::Update(float elapsed) {
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