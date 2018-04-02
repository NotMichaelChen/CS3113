#include "shape.hpp"

#include <vector>
#include <cmath>

#include "SatCollision.h"

double pi = 3.1415926535897;

//https://math.stackexchange.com/a/13263
//Given an incident vector (x,y) and a reflection vector (rx, ry), reflect the incident vector about the reflection vector
std::pair<float, float> reflect(float x, float y, float rx, float ry) {
    //Normalize reflection vector
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

//Computes the object-space coordinates of the vertices of the polygon
//https://math.stackexchange.com/a/1990548: Generalized this result
std::vector<float> Shape::ComputeVertices() {

    std::vector<float> shape_vertices;

    for(int i = 0; i < vertices; i++) {
        shape_vertices.push_back(radius * std::cos((pi/2) + i*(2*pi/vertices)));
        shape_vertices.push_back(radius * std::sin((pi/2) + i*(2*pi/vertices)));
    }

    return shape_vertices;
}

//Computes the world-space coordinates of the vertices of the polygon
std::vector<std::pair<float, float>> Shape::ComputeVerticesWorldSpace() {
    //Get object-space vertices
    std::vector<std::pair<float, float>> finalvertices;
    std::vector<float> objectvertices = ComputeVertices();

    //Apply transformations to vertices
    //Scale transformations should be controlled through the radius variable
    for(size_t i = 0; i < objectvertices.size(); i += 2) {
        finalvertices.push_back(std::make_pair(
            (objectvertices[i] * std::cos(rotation) + objectvertices[i+1] * -std::sin(rotation)) + x,
            (objectvertices[i] * std::sin(rotation) + objectvertices[i+1] * std::cos(rotation)) + y
        ));
    }

    return finalvertices;
}

//Resolves collisions with another shape
void Shape::Collision(Shape& other) {
    std::pair<float, float> penetration;

    //Get world-space vertices of both shapes
    std::vector<std::pair<float, float>> s1points = ComputeVerticesWorldSpace();
    std::vector<std::pair<float, float>> s2points = other.ComputeVerticesWorldSpace();

    bool collided = CheckSATCollision(s1points, s2points, penetration);

    if(collided) {
        //Reflect velocity vector around penetration vector
        std::pair<float, float> newvel = reflect(velocity_x, velocity_y, penetration.first, penetration.second);

        //Set computed vector
        velocity_x = newvel.first;
        velocity_y = newvel.second;

        //Move shape away from other shape
        x += penetration.first * 0.5;
        y += penetration.second * 0.5;

        //Repeat for other shape
        std::pair<float, float> othervel = reflect(other.velocity_x, other.velocity_y, penetration.first, penetration.second);

        other.velocity_x = othervel.first;
        other.velocity_y = othervel.second;

        other.x -= penetration.first * 0.5;
        other.y -= penetration.second * 0.5;
    }
}

//Updates shape and checks for collisions with walls
void Shape::Update() {
    x += velocity_x;
    y += velocity_y;

    //Check collisions
    std::vector<std::pair<float, float>> worldverts = ComputeVerticesWorldSpace();
    
    //Construct 1-d shapes to represent the walls
    std::vector<std::pair<float, float>> rightwallverts = {{3.55, 2}, {3.55, -2}};
    std::vector<std::pair<float, float>> leftwallverts = {{-3.55, 2}, {-3.55, -2}};
    std::vector<std::pair<float, float>> topwallverts = {{-3.55, 2}, {3.55, 2}};
    std::vector<std::pair<float, float>> bottomwallverts = {{-3.55, -2}, {3.55, -2}};

    std::pair<float, float> penetration;
    
    //Check every wall
    if(CheckSATCollision(worldverts, rightwallverts, penetration)) {
        //Reflect velocity about wall vector: we know this vector because wall vectors always point in the same direction
        std::pair<float, float> newvel = reflect(velocity_x, velocity_y, -1, 0);

        //Set velocity vector
        velocity_x = newvel.first;
        velocity_y = newvel.second;

        //Move shape away from wall
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
    //Inserts the (0,0) vertex in between the shape vertices: this constructs triangles that can form the polygon
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