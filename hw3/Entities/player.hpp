#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include "entity.hpp"
#include "bullet.hpp"

class PlayerEntity : public Entity {
public:
    PlayerEntity(SheetSprite& nsprite);
    void Move(float amount);
    std::vector<Bullet>::iterator CheckCollision(std::vector<Bullet>& bullets);
};

#endif
