#ifndef __VNS_H__
#define __VNS_H__

#include <methods/ls.hpp>
#include <provider.hpp>
#include <random.hpp>

#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>

template<class SolutionType, typename FitnessType>
class VNSManager
{
private:
    Provider<SolutionType,FitnessType> *provider;

public:
    VNSManager(Provider<SolutionType,FitnessType> *provider) :
        provider(provider)
    {}

    SolutionType search(
        SolutionType initial,
        std::vector<typename Provider<SolutionType,FitnessType>::neighbor_function> neighborhoods)
    {
        Random rng;
        LSManager<SolutionType,FitnessType> ls(this->provider);

        SolutionType solution = initial;
        FitnessType solution_fitness = this->provider->fitness(solution);
        std::size_t k = 0;

        while(k < neighborhoods.size()) {
            SolutionType shaked = this->shake(solution, neighborhoods[k]);
            SolutionType neighbor = ls.search(shaked, neighborhoods[k]);
            FitnessType neighbor_fitness = this->provider->fitness(neighbor);
            
            if(this->provider->best(neighbor_fitness, solution_fitness)) {
                solution_fitness = neighbor_fitness;
                solution = neighbor;
                k = 0;
            }
            else k += 1;
        }

        return solution;
    }
    
    SolutionType shake(
        const SolutionType solution,
        typename Provider<SolutionType,FitnessType>::neighbor_function neighborhood)
    {
        Random rng;
        std::vector<SolutionType> neighbors = neighborhood(solution);
        unsigned i = rng.randint(0,neighbors.size()-1);
        return neighbors.at(i);
    }
};

#endif