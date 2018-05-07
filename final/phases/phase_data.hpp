#ifndef PHASE_DATA_HPP
#define PHASE_DATA_HPP

#include "vec.hpp"

struct PhaseData {
    PhaseData() : is_moving(false), localticks(0), statenum(0), phaseticks(0), phasenum(0) {}

    //Used during movement to store where the boss began moving from
    Vec origin;
    Vec destination;
    bool is_moving;
    //"Local" ticks used to track changes within phases
    int localticks;

    //Used if keeping track of state is required inside of a boss's phase
    int statenum;

    //"Global" ticks used to track phase changes
    int phaseticks;
    //Indicates which phase the boss is on
    int phasenum;
};

#endif