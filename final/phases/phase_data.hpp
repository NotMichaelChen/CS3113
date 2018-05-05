#ifndef PHASE_DATA_HPP
#define PHASE_DATA_HPP

struct PhaseData {
    //Used during movement to store where the boss began moving from
    float origin[2];
    float destination[2];
    bool is_moving;
    int ticks;
};

#endif