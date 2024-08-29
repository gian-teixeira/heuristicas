#ifndef __ILS_H__
#define __ILS_H__

#include <methods/ls.hpp>
#include <provider.hpp>
#include <random.hpp>

template<typename SolutionType, typename FitnessType>
class ILSManager
{
private:
    Provider<SolutionType,FitnessType> *provider;

public:
    ILSManager(Provider<SolutionType,FitnessType> *provider) :
        provider(provider)
    {}

    SolutionType search(
        SolutionType initial,
        typename Provider<SolutionType,FitnessType>::neighbor_function neighborhood,
        unsigned max)
    {
        LSManager<SolutionType,FitnessType> ls(this->provider);
        SolutionType solution = initial;
        FitnessType solution_fitness = this->provider->fitness(solution);
        unsigned d = 0;

        for(unsigned i = 0; i < max; ++i) {
            SolutionType shaked = this->shake(solution, neighborhood, d);
            SolutionType neighbor = ls.search(shaked, neighborhood);
            FitnessType neighbor_fitness = this->provider->fitness(neighbor);

            if(this->provider->best(neighbor_fitness, solution_fitness)) {
                solution_fitness = neighbor_fitness;
                solution = neighbor;
                d = 0;
            }

            d += 1;
        }

        return solution;
    }

    SolutionType shake(
        const SolutionType solution,
        typename Provider<SolutionType,FitnessType>::neighbor_function neighborhood,
        unsigned d)
    {
        Random rng;
        SolutionType tmp = solution;
        while(d--) {
            std::vector<SolutionType> neighbors = neighborhood(solution);
            uint64_t i = rng.randint(0,neighbors.size()-1);
            tmp = neighbors.at(i);
        }
        return tmp;
    }
};

#endif