#include "vec.hpp"

Vec::Vec() {
    x = y = 0;
}

Vec::Vec(float a, float b) {
    x = a;
    y = b;
}

Vec Vec::operator+(const Vec& arg) {
    return Vec(
        x + arg.x,
        y + arg.y
    );
}

Vec Vec::operator-(const Vec& arg) {
    return Vec(
        x - arg.x,
        y - arg.y
    );
}

Vec Vec::operator*(const Vec& arg) {
    return Vec(
        x * arg.x,
        y * arg.y
    );
}

Vec Vec::operator/(const Vec& arg) {
    return Vec(
        x / arg.x,
        y / arg.y
    );
}

Vec Vec::operator+=(const Vec& arg) {
    *this = *this + arg;
    return *this;
}

Vec operator+(const Vec& lhs, const float rhs) {
    return Vec(
        lhs.x + rhs,
        lhs.y + rhs
    );
}

Vec operator+(const float lhs, const Vec& rhs) {
    return rhs + lhs;
}

Vec operator-(const Vec& lhs, const float rhs) {
    return Vec(
        lhs.x - rhs,
        lhs.y - rhs
    );
}

Vec operator-(const float lhs, const Vec& rhs) {
    return rhs - lhs;
}

Vec operator*(const Vec& lhs, const float rhs) {
    return Vec(
        lhs.x * rhs,
        lhs.y * rhs
    );
}

Vec operator*(const float lhs, const Vec& rhs) {
    return rhs * lhs;
}

Vec operator/(const Vec& lhs, const float rhs) {
    return Vec(
        lhs.x / rhs,
        lhs.y / rhs
    );
}

Vec operator/(const float lhs, const Vec& rhs) {
    return rhs / lhs;
}