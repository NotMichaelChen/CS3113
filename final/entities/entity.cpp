#include "entity.hpp"

Entity::Entity(float nx, float ny, float nr, SheetSprite& nsprite) : rotation(nr), sprite(nsprite) {
    position[0] = nx;
    position[1] = ny;

    size[0] = sprite.getRealWidth();
    size[1] = sprite.getRealHeight();

    velocity[0] = 0;
    velocity[1] = 0;
}

void Entity::Update(float elapsed) {
    position[0] += velocity[0] * elapsed;
    position[1] += velocity[1] * elapsed;
}

void Entity::Draw(ShaderProgram* program) {
    sprite.Draw(program, position[0], position[1], rotation);
}
