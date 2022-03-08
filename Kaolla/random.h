#pragma once
#include <cstdlib>

float GetProb() {
    return (std::rand() % 100 + 1) / 100.f;
}

int RandomRange(int start, int end) {
    float prob = GetProb();
    int ret = int(prob * (end - start) + start);
    return ret;
}
