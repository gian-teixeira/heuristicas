#ifndef __GRASP_H__
#define __GRASP_H__

#include <methods/ls.hpp>
#include <provider.hpp>
#include <random.hpp>

#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>

template<class SolutionType, typename FitnessType>
class GRASPManager
{
private:
    Provider<SolutionType,FitnessType> *provider;

public:
    GRASPManager(Provider<SolutionType,FitnessType> *provider) :
        provider(provider)
    {}

    SolutionType search(
        SolutionType initial,
        typename Provider<SolutionType,FitnessType>::neighbor_function neighborhood,
        double alpha,
        unsigned max)
    {
        Random rng;
        LSManager<SolutionType,FitnessType> ls(this->provider);

        SolutionType best_solution = initial;
        FitnessType best_fitness = this->provider->fitness(best_solution);
        
        while(max--) {
            SolutionType greedy = this->provider->randomized_greedy(alpha);
            SolutionType solution = ls.search(greedy, neighborhood);
            FitnessType solution_fitness = this->provider->fitness(solution);

            if(this->provider->best(solution_fitness, best_fitness)) {
                best_fitness = solution_fitness;
                best_solution = solution;
            }
        }

        return best_solution;
    }
};

#endif