#include "entity.hpp"

Entity::Entity(float nx, float ny, float nr, bool isstat, SheetSprite& nsprite) : rotation(nr), isStatic(isstat), sprite(nsprite) {
    position[0] = nx;
    position[1] = ny;

    size[0] = sprite.getRealWidth();
    size[1] = sprite.getRealHeight();

    velocity[0] = 0;
    velocity[1] = 0;
    //Should be changed later if necessary
    acceleration[0] = 0;
    acceleration[1] = 0;
}

void Entity::Draw(ShaderProgram* program) {
    sprite.Draw(program, position[0], position[1], rotation);
}
