#ifndef PATTERNS_HPP
#define PATTERNS_HPP

#include "entities/bullet.hpp"
#include "SheetSprite.hpp"

#include <vector>

std::vector<Bullet> generateCircle(SheetSprite& bsprite, float origin[2], float speed, int count);


#endif