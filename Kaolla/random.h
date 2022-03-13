#pragma once
#include <cstdlib>

float GetProb() {
    return (std::rand() % (100 + 1)) / 100.f;
}

int RandomRange(int start, int end) {
    return start + (std::rand() % (end - start + 1));
}
