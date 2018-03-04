#include "entity.hpp"

Entity::Entity(float nx, float ny, float nr, SheetSprite& nsprite) : x(nx), y(ny), rotation(nr), sprite(nsprite) {
    velocity_x = 0;
    velocity_y = 0;
}

void Entity::Draw(ShaderProgram* program) {
    sprite.Draw(program, x, y, rotation);
}

float Entity::getWidth() {
    return sprite.getRealWidth();
}

float Entity::getHeight() {
    return sprite.getRealHeight();
}
