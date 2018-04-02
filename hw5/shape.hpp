#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <vector>

#include "ShaderProgram.h"

class Shape {
public:
    Shape(float nx, float ny, float nr, float nradius, int verts, float vx, float vy);
    std::vector<float> ComputeVertices();
    std::vector<std::pair<float, float>> ComputeVerticesWorldSpace();
    bool Collision(Shape& other, std::pair<float, float>& penetration);
    void Draw(ShaderProgram& program);
    void Update();

    float x;
    float y;
    float rotation;

    float radius;
    //Determines what kind of n-gon this shape is
    int vertices;

    float velocity_x;
    float velocity_y;
};

#endif