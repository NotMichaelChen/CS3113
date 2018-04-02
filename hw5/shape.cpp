#include "shape.hpp"

#include <vector>
#include <cmath>

#include "SatCollision.h"

double pi = 3.1415926535897;

Shape::Shape(float nx, float ny, float nr, float nradius, int verts) : x(nx), y(ny), rotation(nr), radius(nradius), vertices(verts) {
    velocity_x = 0;
    velocity_y = 0;
}

std::vector<float> Shape::ComputeVertices() {
    std::vector<float> shape_vertices;

    for(int i = 0; i < vertices; i++) {
        shape_vertices.push_back(radius * std::cos((pi/2) + i*(2*pi/vertices)));
        shape_vertices.push_back(radius * std::sin((pi/2) + i*(2*pi/vertices)));
    }

    return shape_vertices;
}

std::vector<std::pair<float, float>> Shape::ComputeVerticesWorldSpace() {
    std::vector<std::pair<float, float>> finalvertices;
    std::vector<float> objectvertices = ComputeVertices();

    for(size_t i = 0; i < objectvertices.size(); i += 2) {
        finalvertices.push_back(std::make_pair(
            (objectvertices[i] * std::cos(rotation) + objectvertices[i+1] * -std::sin(rotation)) + x,
            (objectvertices[i] * std::sin(rotation) + objectvertices[i+1] * std::cos(rotation)) + y
        ));
    }

    return finalvertices;
}

bool Shape::Collision(Shape& other, std::pair<float, float>& penetration) {
    auto s1points = ComputeVerticesWorldSpace();
    auto s2points = other.ComputeVerticesWorldSpace();

    bool collided = CheckSATCollision(s1points, s2points, penetration);
    return collided;
}

void Shape::Draw(ShaderProgram& program) {
    std::vector<float> draw_vertices;

    std::vector<float> shape_vertices = ComputeVertices();
    for(size_t i = 0; i < shape_vertices.size(); i += 2) {
        if(i+2 >= shape_vertices.size()) {
            draw_vertices.push_back(shape_vertices[0]);
            draw_vertices.push_back(shape_vertices[1]);
        }
        else {
            draw_vertices.push_back(shape_vertices[i+2]);
            draw_vertices.push_back(shape_vertices[i+3]);
        }
        draw_vertices.push_back(0);
        draw_vertices.push_back(0);
        draw_vertices.push_back(shape_vertices[i]);
        draw_vertices.push_back(shape_vertices[i+1]);
    }
    
    Matrix modelMatrix;
    modelMatrix.Translate(x, y, 0);
    modelMatrix.Rotate(rotation);
    program.SetModelMatrix(modelMatrix);

    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, draw_vertices.data());
    glEnableVertexAttribArray(program.positionAttribute);
    glDrawArrays(GL_TRIANGLES, 0, draw_vertices.size()/2);
    glDisableVertexAttribArray(program.positionAttribute);
}