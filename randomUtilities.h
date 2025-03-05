#ifndef RANDOMUTILITIES_H
#define RANDOMUTILITIES_H


#include <random>

// Global namespace for random utilities
namespace RandomUtils {

    static std::random_device rd;
    static std::mt19937 gen(rd()); // Shared generator

    // Function to access the generator
    inline std::mt19937& getGenerator() {
        return gen;
    }
}

#endif // RANDOMUTILITIES_H
