#include "entity.hpp"

Entity::Entity(float nx, float ny, float nr, float nw, float nh, SheetSprite& nsprite) : x(nx), y(ny), rotation(nr), width(nw), height(nh), sprite(nsprite) {
    velocity_x = 0;
    velocity_y = 0;
}

void Entity::Draw(ShaderProgram& program) {
    float vertices[] = {-width/2, -height/2, width/2, -height/2, width/2, height/2, -width/2, -height/2, width/2, height/2,
                        -width/2, height/2};

    Matrix modelMatrix;
    modelMatrix.Translate(x, y, 0);
    modelMatrix.Rotate(rotation);
    program.SetModelMatrix(modelMatrix);

    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program.positionAttribute);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(program.positionAttribute);
}
