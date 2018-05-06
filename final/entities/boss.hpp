#ifndef BOSS_HPP
#define BOSS_HPP

#include <memory>
#include <vector>

#include "SheetSprite.hpp"
#include "entity.hpp"
#include "bullet.hpp"
#include "phases/phase_data.hpp"

class BossEntity : public Entity {
public:
    BossEntity(SheetSprite& nsprite, std::vector<Bullet>* b);
    void Update(float elapsed);

    void reset();

    std::vector<Bullet>* bullets;
    PhaseData data;
};

#endif