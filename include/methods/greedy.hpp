#ifndef __GREEDY_H__
#define __GREEDY_H__

#include <provider.hpp>
#include <random.hpp>

#include <vector>
#include <algorithm>
#include <utility>

template<class SolutionType, typename FitnessType>
class GreedyManager
{
private:
    Provider<SolutionType,FitnessType> *provider;

public:
    GreedyManager(Provider<SolutionType,FitnessType> *provider) :
        provider(provider)
    {}

    SolutionType build()
    {
        SolutionType solution;
        std::vector<SolutionType::part_type> candidates;
        
        while(!this->provider->valid(solution)) {
            std::vector<FitnessType> cost = this->provider->greedy_eval(solution, candidates);
            std::vector<std::pair<FitnessType,int>> indexed(candidates.size());

            for(std::size_t i = 0; i < candidates.size(); ++i) {
                indexed[i] = {cost[i], i};
            }
            std::sort(indexed.begin(), indexed.end());
            
            solution::part_type next = candidates[indexed[0].second];
            solution.include(next);
        }

        return solution;
    }
};

#endif