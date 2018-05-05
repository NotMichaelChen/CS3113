#include "entity.hpp"

Entity::Entity(float nx, float ny, float nr, SheetSprite& nsprite) :
    position(nx, ny),
    rotation(nr),
    sprite(nsprite)
{
    size.x = sprite.getRealWidth();
    size.y = sprite.getRealHeight();
}

void Entity::Update(float elapsed) {
    velocity += acceleration;

    position += velocity * elapsed;
}

void Entity::Draw(ShaderProgram* program) {
    sprite.Draw(program, position, rotation);
}
