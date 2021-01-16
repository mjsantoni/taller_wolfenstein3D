#ifndef PROBABILITY_H
#define PROBABILITY_H

#include <random>

class Probability {
public:
    Probability() {}

    bool operator()(double prob) {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist10(0,100); // distribution in range [1, 10]
        return dist10(rng) < (prob * 100);
    }

    ~Probability() {}
};

#endif // PROBABILITY_H