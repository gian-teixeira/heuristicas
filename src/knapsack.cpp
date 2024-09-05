#include <knapsack.hpp>
#include <random.hpp>
#include <provider.hpp>

#include <algorithm>
#include <vector>
#include <set>
#include <utility>
#include <iostream>
#include <cmath>
#include <numeric>
#include <limits>
#include <functional>
#include <cassert>

KnapsackSolution::KnapsackSolution(std::size_t size) : 
    std::vector<bool>(size,0)
{}

KnapsackSolution KnapsackSolution::flip(std::size_t i)
{
    KnapsackSolution tmp = *this;
    tmp.at(i) = !tmp.at(i);
    return tmp;
}

double Knapsack::fitness(KnapsackSolution solution)
const {
    double value_sum = 0;
    double weight_sum = 0;
    for(std::size_t i = 0; i < this->size(); ++i) {
        value_sum += this->items.at(i).value*solution.at(i);
        weight_sum += this->items.at(i).weight*solution.at(i);
    }
    if(weight_sum > this->max_weight) return this->null_fitness();
    return value_sum;
}

double Knapsack::null_fitness()
const {
    return std::numeric_limits<double>().min();
}

bool Knapsack::best(
    double a, 
    double b)
const {
    return a > b;
}

bool Knapsack::valid(KnapsackSolution solution) 
const {
    double weight_sum = 0;
    for(std::size_t i = 0; i < this->size(); ++i) {
        weight_sum += solution[i]*this->items.at(i).weight;
    }
    return (weight_sum < this->max_weight);
}

std::vector<KnapsackSolution> Knapsack::neighborhood_all_flips(KnapsackSolution solution)
const {
    std::vector<KnapsackSolution> neighbors;
    for(std::size_t i = 0; i < solution.size(); ++i) {
        KnapsackSolution tmp = solution.flip(i);
        if(this->valid(tmp)) {
            neighbors.push_back(tmp);
            std::cout << this->fitness(tmp) << std::endl;
        }
    }
    return neighbors;
}

std::vector<KnapsackSolution> Knapsack::neighborhood_random_flip(KnapsackSolution solution)
const {
    Random rng;
    KnapsackSolution tmp(this->size());
    do {
        unsigned i = rng.randint(0, solution.size()-1);
        tmp = solution.flip(i);
    } while(!this->valid(tmp));
    return {tmp};
}

std::vector<Provider<KnapsackSolution,double>::neighbor_function> Knapsack::neighborhoods()
const {
    return std::vector<Provider<KnapsackSolution,double>::neighbor_function> {
        std::bind(&Knapsack::neighborhood_random_flip, this, std::placeholders::_1),
        std::bind(&Knapsack::neighborhood_all_flips, this, std::placeholders::_1),
    };
}

KnapsackSolution Knapsack::random_solution()
const {
    Random rng;
    std::vector<unsigned> candidates(this->items.size());
    std::iota(candidates.begin(), candidates.end(), 0);
    std::shuffle(candidates.begin(), candidates.end(), rng.get_generator());

    KnapsackSolution solution(this->size());
    double weight_sum = 0;

    for(unsigned c : candidates) {
        KnapsackItem item = this->items[c];
        if(weight_sum+item.weight > this->max_weight) break;
        weight_sum += item.weight;
        solution.at(c) = 1;
    }
    
    return solution;
}

std::size_t Knapsack::size()
const {
    return this->items.size();
}

KnapsackSolution Knapsack::randomized_greedy(double alpha)
const {
    Random rng;
    KnapsackSolution solution(this->size());
    std::set<int> candidates;
    double weight_sum = 0;

    for(unsigned i = 0; i < this->size(); ++i) candidates.insert(i);

    for(std::size_t i = 1; i < this->size(); ++i) {
        std::vector<std::pair<double,unsigned>> tmp;
        double bound;
        int k = 0;

        for(int c : candidates) {
            if(this->items[c].weight+weight_sum > this->max_weight) continue;
            double profit = this->items[c].value / this->items[c].weight;
            tmp.emplace_back(profit,c);
        }

        if(tmp.empty()) break;
        
        std::sort(tmp.rbegin(), tmp.rend());
        bound = tmp.begin()->first - alpha*(tmp.begin()->first - --tmp.end()->first);
        while(k < tmp.size() && tmp[k].first >= bound) ++k;

        unsigned next_id = rng.randint(0,k-1);
        unsigned next = tmp[next_id].second;
        solution[next] = 1;
        candidates.erase(next);
        weight_sum += this->items[next].weight;
    }

    return solution;
}

Knapsack Knapsack::read()
{
    std::size_t nitems;
    double max_weight;
    std::vector<KnapsackItem> items;

    std::cin >> nitems >> max_weight;
    items.resize(nitems);

    for(KnapsackItem &item : items) {
        std::cin >> item.value >> item.weight;
    }

    return Knapsack(items, max_weight);
}