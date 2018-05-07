#include "patterns.hpp"

#include <cmath>

#include "util.hpp"

double pi = 3.1415926535897;

std::vector<Bullet> generateCircle(SheetSprite& bsprite, Vec origin, float speed, int count, float rot) {
    std::vector<Bullet> bullets;
    
    for(int i = 0; i < count; i++) {

        float velx = speed * std::cos((pi/2) + (i+rot)*(2*pi/count));
        float vely = speed * std::sin((pi/2) + (i+rot)*(2*pi/count));
        Vec vel(velx, vely);
        Vec acc;

        bullets.emplace_back(bsprite, origin, vel, acc, 0);
    }

    return bullets;
}

std::vector<Bullet> generateFountain(SheetSprite& bsprite, Vec origin, float speed, int count) {
    std::vector<Bullet> bullets;

    for(int i = 0; i < count; i++) {
        float angle = randFloat(0, 2*pi);

        float velx = speed * std::cos(angle);
        float vely = speed * std::sin(angle);
        Vec vel(velx, vely);
        Vec acc;

        bullets.emplace_back(bsprite, origin, vel, acc, 0);
    }

    return bullets;
}

//Speed refers to vertical speed
std::vector<Bullet> generateLineSpread(SheetSprite& bsprite, Vec origin, Vec maxvel, int count) {

    std::vector<Bullet> bullets;

    for(int i = 0; i < count; i++) {
        float vely = maxvel.y;
        float velx = -maxvel.x + ((float)i / count)*2*(maxvel.x);
        Vec vel(velx, vely);
        Vec acc;
        
        bullets.emplace_back(bsprite, origin, vel, acc, 0);
    }

    return bullets;
}