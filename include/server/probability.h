#ifndef PROBABILITY_H
#define PROBABILITY_H

#include <random>

std::knuth_b rand_engine;

class Probability {
public:
    Probability() {}

    bool Probability::operator()(double prob) {
        std::bernoulli_distribution d(prob);
        return d(rand_engine);
    }

    ~Probability() {}
};

#endif // PROBABILITY_H