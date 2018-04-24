#include "phase_inventory.hpp"

#include <vector>

#include "global.hpp"
#include "patterns/patterns.hpp"
#include "entities/bullet.hpp"
#include "SheetSprite.hpp"

void beginnerBoss(BossEntity* boss, float elapsed) {
    if(boss->getTicks() % 60 == 0) {
        SheetSprite bulletsprite(Global::bullet_spritesheet, 16, 49, 16, 16, 0.1, 1024, 1024);
        std::vector<Bullet> newbullets = generateCircle(bulletsprite, boss->position, 0.5, 25);
        boss->bullets->insert(boss->bullets->end(), newbullets.begin(), newbullets.end());
    }
}