#ifndef __TSP_H__
#define __TSP_H__

#include <provider.hpp>
#include <iostream>
#include <vector>

class TSPSolution : public std::vector<unsigned>
{
public:
    TSPSolution() {};
    TSPSolution(std::size_t size);
    TSPSolution swap(std::size_t i, std::size_t j);
};

class TSP : public Provider<TSPSolution,double>
{
private:
    std::size_t ncities;
    std::vector<std::vector<double>> distances;

public:
    TSP(std::size_t ncities, std::vector<std::vector<double>> distances);
    bool best(double a, double b) const override;
    std::vector<Provider<TSPSolution,double>::neighbor_function> 
        neighborhoods() const override;
    std::vector<TSPSolution> neighborhood_all_swaps(TSPSolution solution) const;
    std::vector<TSPSolution> neighborhood_random_swap(TSPSolution solution) const;
    double fitness(TSPSolution solution) const override;
    double null_fitness() const override;
    bool valid(TSPSolution solution) const override;
    TSPSolution randomized_greedy(double alpha) const override;
    std::size_t size() const;
    static TSP read();
};

#endif