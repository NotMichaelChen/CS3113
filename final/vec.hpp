#ifndef VEC_HPP
#define VEC_HPP

struct Vec {
    //Constructors
    Vec();
    Vec(float a, float b);

    //Operator overloads
    Vec operator+(const Vec& arg);
    Vec operator-(const Vec& arg);
    Vec operator*(const Vec& arg);
    Vec operator/(const Vec& arg);

    Vec operator+=(const Vec& arg);

    //Variables
    float x;
    float y;
};

Vec operator+(const Vec& lhs, const float rhs);
Vec operator+(const float lhs, const Vec& rhs);
Vec operator-(const Vec& lhs, const float rhs);
Vec operator-(const float lhs, const Vec& rhs);
Vec operator*(const Vec& lhs, const float rhs);
Vec operator*(const float lhs, const Vec& rhs);
Vec operator/(const Vec& lhs, const float rhs);
Vec operator/(const float lhs, const Vec& rhs);

#endif