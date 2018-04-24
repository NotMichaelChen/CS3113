#ifndef BOSS_HPP
#define BOSS_HPP

#include <memory>
#include <vector>

#include "SheetSprite.hpp"
#include "entity.hpp"
#include "bullet.hpp"

class BossEntity : public Entity {
public:
    BossEntity(SheetSprite& nsprite, std::vector<Bullet>* b);
    void Update(float elapsed);
    int getTicks();

    std::vector<Bullet>* bullets;

private:
    int ticks;
};

#endif