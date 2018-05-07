#ifndef LERPFUNCS_HPP
#define LERPFUNCS_HPP

#include "vec.hpp"

Vec easeIn(Vec from, Vec to, float time);
Vec easeInOut(Vec from, Vec to, float time);
Vec linearInterpolation(Vec from, Vec to, float time);

#endif