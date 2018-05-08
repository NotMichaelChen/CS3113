#ifndef BOSS_HPP
#define BOSS_HPP

#include <memory>
#include <vector>

#include "SheetSprite.hpp"
#include "entity.hpp"
#include "bullet.hpp"
#include "phases/phase_data.hpp"
#include "generator.hpp"

class BossEntity : public Entity {
public:
    BossEntity(SheetSprite& nsprite, std::vector<Bullet>* b, std::vector<GeneratorEntity>* g);
    void Update(float elapsed);

    void reset();
    //Check every frame
    bool isDone();

    std::vector<Bullet>* bullets;
    std::vector<GeneratorEntity>* generators;
    PhaseData data;

private:
    //0=beginner, 1=intermediate, 2=advanced
    int bosstype;
    bool done;
};

#endif