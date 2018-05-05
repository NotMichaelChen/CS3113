#ifndef PHASE_DATA_HPP
#define PHASE_DATA_HPP

#include "vec.hpp"

struct PhaseData {
    //Used during movement to store where the boss began moving from
    Vec origin;
    Vec destination;
    bool is_moving;
    int ticks;
};

#endif