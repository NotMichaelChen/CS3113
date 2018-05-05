#include "patterns.hpp"

#include <cmath>

double pi = 3.1415926535897;

std::vector<Bullet> generateCircle(SheetSprite& bsprite, Vec origin, float speed, int count) {
    std::vector<Bullet> bullets;
    
    for(int i = 0; i < count; i++) {

        float velx = speed * std::cos((pi/2) + i*(2*pi/count));
        float vely = speed * std::sin((pi/2) + i*(2*pi/count));
        Vec vel(velx, vely);
        Vec acc;

        bullets.emplace_back(bsprite, origin, vel, acc, 0);
    }

    return bullets;
}