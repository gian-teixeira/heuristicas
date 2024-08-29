#ifndef __LS_H__
#define __LS_H__

#include <random.hpp>
#include <provider.hpp>
#include <iostream>

template<typename SolutionType, typename FitnessType>
class LSManager
{
private:
    Provider<SolutionType,FitnessType> *provider;

public:
    LSManager(Provider<SolutionType,FitnessType> *provider) :
        provider(provider)
    {}

    SolutionType search(
        SolutionType initial,
        typename Provider<SolutionType,FitnessType>::neighbor_function neighborhood)
    {
        Random rng;
        SolutionType solution = initial;
        SolutionType best_solution = initial;
        FitnessType solution_fitness = this->provider->fitness(solution);
        FitnessType best_fitness = solution_fitness;

        while(true) {
            std::vector<SolutionType> neighbors = neighborhood(solution);
            FitnessType neighbor_fitness = this->provider->fitness(neighbors.at(0));
            SolutionType neighbor = neighbors[0];
            bool stop = true;

            for(SolutionType candidate : neighbors) {
                FitnessType candidate_fitness = this->provider->fitness(candidate);
                if(this->provider->best(candidate_fitness, neighbor_fitness)) {
                    neighbor_fitness = candidate_fitness;
                    neighbor = candidate;
                }
            }

            if(this->provider->best(neighbor_fitness, solution_fitness)) {
                solution_fitness = neighbor_fitness;
                solution = neighbor;
                stop = false;
                if(this->provider->best(solution_fitness, best_fitness)) {
                    best_fitness = solution_fitness;
                    best_solution = solution;
                }
            }

            if(stop) break;
        }

        return best_solution;
    }
};

#endif