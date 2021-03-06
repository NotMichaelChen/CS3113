#include "lerpfuncs.hpp"

Vec easeIn(Vec from, Vec to, float time) {
    float tVal = time*time*time*time*time;
    return (1.0f-tVal)*from + tVal*to;
}

Vec easeInOut(Vec from, Vec to, float time) {
    float tVal;
    if(time > 0.5) {
        float oneMinusT = 1.0f-((0.5f-time)*-2.0f);
        tVal = 1.0f - ((oneMinusT * oneMinusT * oneMinusT * oneMinusT * oneMinusT) * 0.5f);
    } else {
        time *= 2.0;
        tVal = (time*time*time*time*time)/2.0;
    }

    return (1.0f-tVal)*from + tVal*to;
}

Vec linearInterpolation(Vec from, Vec to, float time) {
    return (1.0f-time)*from + time*to;
}