#ifndef __KANPSACK_H__
#define __KANPSACK_H__

#include <provider.hpp>
#include <iostream>
#include <vector>

class KnapsackSolution : public std::vector<bool>
{
public:
    KnapsackSolution(std::size_t size);
    KnapsackSolution flip(std::size_t i);
};

class KnapsackItem
{
public:
    double weight;
    double value;

    KnapsackItem() {};
    KnapsackItem(double weight, double value) :
        weight(weight),
        value(value)
    {}
};

class Knapsack : public Provider<KnapsackSolution,double>
{
private:
    std::vector<KnapsackItem> items;
    double max_weight;

public:
    Knapsack(std::vector<KnapsackItem> items, double max_weight) :
        items(items),
        max_weight(max_weight)
    {}

    inline std::vector<KnapsackItem> get_items() { return this->items; };


    bool best(double a, double b) const override;
    double null_fitness() const override;
    double fitness(KnapsackSolution solution) const override;
    std::size_t size() const;
    bool valid(KnapsackSolution solution) const override;
    std::vector<KnapsackSolution> neighborhood_random_flip(KnapsackSolution solution) const;
    std::vector<KnapsackSolution> neighborhood_all_flips(KnapsackSolution solution) const;
    std::vector<Provider<KnapsackSolution,double>::neighbor_function> 
        neighborhoods() const override;
    KnapsackSolution randomized_greedy(double alpha) const override;
    KnapsackSolution random_solution() const;
    static Knapsack read();
};

#endif