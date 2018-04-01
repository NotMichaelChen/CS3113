#include "shape.hpp"

#include <vector>
#include <iostream>
#include <cmath>

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

void Shape::Draw(ShaderProgram& program) {
    std::vector<float> draw_vertices;

    std::vector<float> shape_vertices = ComputeVertices();
    for(size_t i = 0; i < shape_vertices.size(); i += 2) {
        draw_vertices.push_back(shape_vertices[i]);
        draw_vertices.push_back(shape_vertices[i+1]);
        draw_vertices.push_back(0);
        draw_vertices.push_back(0);
        if(i+2 >= shape_vertices.size()) {
            draw_vertices.push_back(shape_vertices[0]);
            draw_vertices.push_back(shape_vertices[1]);
        }
        else {
            draw_vertices.push_back(shape_vertices[i+2]);
            draw_vertices.push_back(shape_vertices[i+3]);
        }
    }
    
    //float vertices[] = {-width/2, -height/2, width/2, -height/2, width/2, height/2, -width/2, -height/2, width/2, height/2,-width/2, height/2};

    Matrix modelMatrix;
    modelMatrix.Translate(x, y, 0);
    modelMatrix.Rotate(rotation);
    program.SetModelMatrix(modelMatrix);

    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, draw_vertices.data());
    glEnableVertexAttribArray(program.positionAttribute);
    glDrawArrays(GL_TRIANGLES, 0, draw_vertices.size()/2);
    glDisableVertexAttribArray(program.positionAttribute);
}