#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include <SDL.h>

#include "entity.hpp"

class PlayerEntity : public Entity {
public:
    PlayerEntity(SheetSprite& nsprite, SheetSprite dotsprite, const Uint8* k, std::vector<unsigned int> c);
    void Update(float elapsed);
    void Draw(ShaderProgram* program);

    float getRadius();
    
    void setInvinc();
    bool isInvinc();

    void reset();

    int lives;

private:
    const float fast_speed = 2.2;
    const float slow_speed = 0.7;
    const Uint8* keys;
    //Left, Down, Up, Right, Slow
    std::vector<unsigned int> controls;
    unsigned int updatecounter;
    //Used to track grace period after death
    int invinc_counter;

    SheetSprite hit_dot;
};

#endif
