#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <random>
#include <cstdint>

class Random
{
private:
    std::random_device device;
    std::mt19937_64 generator; 

public:
    Random() : 
        device(),
        generator(device())
    {}

    /*
        Generates a random double on interval [0,1).
    */
    double rand()
    {
        std::uniform_real_distribution<double> dist {0,1};
        return dist(this->generator);
    }

    /*
        Generates a 64 bit random integer on closed interval [a,b].
    */
    uint64_t randint(uint64_t low,
                        uint64_t high)
    {
        std::uniform_int_distribution<uint64_t> dist {low,high};
        return dist(this->generator);
    }

    std::mt19937_64 get_generator()
    {
        return this->generator;
    }      

};

#endif