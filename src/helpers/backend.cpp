/**
 *
 */

#include "../../include/helpers/backend.hpp"
#include <random>

int randomInt(int start, int end) {
    static std::random_device rd; // Obtain a random number from hardware
    static std::mt19937 eng(rd()); // Seed the generator
    std::uniform_int_distribution<> dist(start, end);
    return dist(eng);
}
