#ifndef PHASE_DATA_HPP
#define PHASE_DATA_HPP

#include "vec.hpp"

struct PhaseData {
    PhaseData() : is_moving(false), ticks(0), phaseticks(0) {}

    //Used during movement to store where the boss began moving from
    Vec origin;
    Vec destination;
    bool is_moving;
    int ticks;

    int phaseticks;
    int phasenum;
};

#endif