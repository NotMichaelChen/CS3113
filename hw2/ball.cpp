#include "ball.hpp"

#include <cstdlib>
#include <ctime>

Ball::Ball() : Entity(0, 0, 0, 0.15, 0.15) {
    //https://stackoverflow.com/a/686373
    srand (static_cast <unsigned> (time(0)));
    float LO = -4.0;
    float HI = 4.0;
    velocity_y = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
    velocity_x = 2;
}

bool Ball::Step(float amount) {
    y += amount*velocity_y;
    x += amount*velocity_x;

    if(y > 1.85 || y < -1.85) {
        velocity_y = -velocity_y;
        //Reset y to correct boundary depending on if y is positive or negative
        y = y > 0 ? 1.85 : -1.85;
    }

    //lol so bad
    if(x > 3.7 || x < -3.7) {
        return false;
    }
    return true;
}

void Ball::CheckPaddle(Paddle& testpaddle) {
// is R1’s bottom higher than R2’s top?
// is R1’s top lower than R2’s bottom?
// is R1’s left larger than R2’s right?
// is R1’s right smaller than R2’s left?
// If ANY of the above are true, then the two
// rectangles are NOT intersecting!
    if(y-height/2 > testpaddle.y+testpaddle.height/2 ||
        y+height/2 < testpaddle.y-testpaddle.height/2 ||
        x-width/2 > testpaddle.x+width/2 ||
        x+width/2 < testpaddle.x-width/2) {

        return;
    }
    velocity_x = -velocity_x;
}