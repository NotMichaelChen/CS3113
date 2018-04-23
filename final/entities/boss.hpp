#ifndef BOSS_HPP
#define BOSS_HPP

#include <memory>

#include "SheetSprite.hpp"
#include "entity.hpp"

class BossEntity : public Entity {
public:
    BossEntity(SheetSprite& nsprite);
    void Update(float elapsed);
};

#endif