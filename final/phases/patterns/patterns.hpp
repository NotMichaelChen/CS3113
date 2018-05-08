#ifndef PATTERNS_HPP
#define PATTERNS_HPP

#include "entities/bullet.hpp"
#include "SheetSprite.hpp"
#include "vec.hpp"

#include <vector>

std::vector<Bullet> generateCircle(SheetSprite& bsprite, Vec origin, float speed, int count, float rot);
std::vector<Bullet> generateFountain(SheetSprite& bsprite, Vec origin, float speed, int count);
std::vector<Bullet> generateLineSpread(SheetSprite& bsprite, Vec origin, Vec maxvel, int count);
Bullet generateSingle(SheetSprite& bsprite, Vec origin, float angle, float speed);
std::vector<Bullet> generateStaticCircle(SheetSprite& bsprite, Vec origin, float radius, float angle, float speed, int count);

#endif