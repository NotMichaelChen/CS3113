#ifndef PATTERNS_HPP
#define PATTERNS_HPP

#include "entities/bullet.hpp"
#include "SheetSprite.hpp"
#include "vec.hpp"

#include <vector>

std::vector<Bullet> generateCircle(SheetSprite& bsprite, Vec origin, float speed, int count);


#endif