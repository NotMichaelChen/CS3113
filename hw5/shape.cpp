#include "shape.hpp"

#include <vector>
#include <cmath>

#include "SatCollision.h"

double pi = 3.1415926535897;

//TODO: Comment

//https://math.stackexchange.com/a/13263
std::pair<float, float> reflect(float x, float y, float rx, float ry) {
    //Normalize penetration
    float r_mag = std::sqrt(rx*rx + ry*ry);
    float r_norm_x = rx / r_mag;
    float r_norm_y = ry / r_mag;

    //Multiply by 2(d . n)
    float multiplier = 2 * (x*r_norm_x + y*r_norm_y);
    float x2 = r_norm_x * multiplier;
    float y2 = r_norm_y * multiplier;

    //Subtract vectors
    float resultx = x - x2;
    float resulty = y - y2;

    return std::make_pair(resultx, resulty);
}

Shape::Shape(float nx, float ny, float nr, float nradius, int verts, float vx, float vy) : 
    x(nx), y(ny), rotation(nr), radius(nradius), vertices(verts), velocity_x(vx), velocity_y(vy) {}

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

//TODO: remove penetration from args
void Shape::Collision(Shape& other) {
    std::pair<float, float> penetration;

    std::vector<std::pair<float, float>> s1points = ComputeVerticesWorldSpace();
    std::vector<std::pair<float, float>> s2points = other.ComputeVerticesWorldSpace();

    bool collided = CheckSATCollision(s1points, s2points, penetration);

    if(collided) {
        std::pair<float, float> newvel = reflect(velocity_x, velocity_y, penetration.first, penetration.second);

        velocity_x = newvel.first;
        velocity_y = newvel.second;

        std::pair<float, float> othervel = reflect(other.velocity_x, other.velocity_y, penetration.first, penetration.second);

        other.velocity_x = othervel.first;
        other.velocity_y = othervel.second;
    }
}

void Shape::Update() {
    x += velocity_x;
    y += velocity_y;

    //Check collisions
    std::vector<std::pair<float, float>> worldverts = ComputeVerticesWorldSpace();
    
    std::vector<std::pair<float, float>> rightwallverts = {{3.55, 2}, {3.55, -2}};
    std::vector<std::pair<float, float>> leftwallverts = {{-3.55, 2}, {-3.55, -2}};
    std::vector<std::pair<float, float>> topwallverts = {{-3.55, 2}, {3.55, 2}};
    std::vector<std::pair<float, float>> bottomwallverts = {{-3.55, -2}, {3.55, -2}};

    std::pair<float, float> penetration;
    if(CheckSATCollision(worldverts, rightwallverts, penetration)) {
        std::pair<float, float> newvel = reflect(velocity_x, velocity_y, -1, 0);

        velocity_x = newvel.first;
        velocity_y = newvel.second;

        x += penetration.first;
        y += penetration.second;
    }
    else if(CheckSATCollision(worldverts, leftwallverts, penetration)) {
        std::pair<float, float> newvel = reflect(velocity_x, velocity_y, 1, 0);

        velocity_x = newvel.first;
        velocity_y = newvel.second;

        x += penetration.first;
        y += penetration.second;
    }
    else if(CheckSATCollision(worldverts, topwallverts, penetration)) {
        std::pair<float, float> newvel = reflect(velocity_x, velocity_y, 0, -1);

        velocity_x = newvel.first;
        velocity_y = newvel.second;

        x += penetration.first;
        y += penetration.second;
    }
    else if(CheckSATCollision(worldverts, bottomwallverts, penetration)) {
        std::pair<float, float> newvel = reflect(velocity_x, velocity_y, 0, 1);

        velocity_x = newvel.first;
        velocity_y = newvel.second;

        x += penetration.first;
        y += penetration.second;
    }
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