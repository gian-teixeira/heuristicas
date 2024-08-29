#ifndef __PROVIDER_H__
#define __PROVIDER_H__

#include <vector>
#include <functional>

template<class SolutionType, class FitnessType>
class Provider
{
public:
    using neighbor_function = std::function<std::vector<SolutionType>(SolutionType)>;
    using solution_type = SolutionType;
    using fitness_type = FitnessType;
    
    virtual std::vector<Provider<SolutionType,FitnessType>::neighbor_function> 
        neighborhoods() const = 0;
    virtual bool best(FitnessType a, FitnessType b) const = 0;
    virtual FitnessType fitness(SolutionType solution) const = 0;
    virtual FitnessType null_fitness() const = 0;
    virtual bool valid(SolutionType solution) const = 0;
    virtual SolutionType randomized_greedy(double alpha) const = 0;
};

#endif