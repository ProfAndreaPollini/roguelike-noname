//
// Created by pollini on 20/01/2022.
//

#ifndef RL_DA_ZERO_RNG_H
#define RL_DA_ZERO_RNG_H

#include <random>

class Rng
{
  public:
    static Rng &getInstance() {
        static Rng instance;
        return instance;
    }

    std::mt19937 &getGenerator() {
        return generator;
    }

    int getRandomInt(int min, int max) {
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(generator);
    }

    //    std::mt19937 rng(rd());

  private:
    Rng() {
        std::random_device rd;// only used once to initialise (seed) engine
        generator.seed(rd());
    }
    Rng(Rng const &) = delete;
    void operator=(Rng const &) = delete;
    std::mt19937 generator;
};


#endif// RL_DA_ZERO_RNG_H
