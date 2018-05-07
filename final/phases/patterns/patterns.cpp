#include "patterns.hpp"

#include <cmath>

#include "util.hpp"
#include "global.hpp"

std::vector<Bullet> generateCircle(SheetSprite& bsprite, Vec origin, float speed, int count, float rot) {
    std::vector<Bullet> bullets;
    
    for(int i = 0; i < count; i++) {

        float velx = speed * std::cos((Global::PI/2) + (i+rot)*(2*Global::PI/count));
        float vely = speed * std::sin((Global::PI/2) + (i+rot)*(2*Global::PI/count));
        Vec vel(velx, vely);
        Vec acc;

        bullets.emplace_back(bsprite, origin, vel, acc, 0);
    }

    return bullets;
}

std::vector<Bullet> generateFountain(SheetSprite& bsprite, Vec origin, float speed, int count) {
    std::vector<Bullet> bullets;

    for(int i = 0; i < count; i++) {
        float angle = randFloat(0, 2*Global::PI);

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

//Angle is in radians
Bullet generateSingle(SheetSprite& bsprite, Vec origin, float angle, float speed) {

    Vec vel(speed * std::cos(angle), speed * std::sin(angle));
    Vec acc;

    Bullet b(bsprite, origin, vel, acc, 0);

    return b;
}