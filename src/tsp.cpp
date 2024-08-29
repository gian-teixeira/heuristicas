#include <tsp.hpp>
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

TSPSolution::TSPSolution(std::size_t size) : 
    std::vector<unsigned>(size)
{
    Random rng;
    std::iota(this->begin(), this->end(), 0);
    std::shuffle(this->begin(), this->end(), rng.get_generator());
}

TSPSolution TSPSolution::swap(std::size_t i, std::size_t j)
{
    TSPSolution tmp = *this;
    std::swap(tmp.at(i), tmp.at(j));
    return tmp;
}

TSP::TSP(std::size_t ncities, std::vector<std::vector<double>> distances) :
    ncities(ncities),
    distances(distances)
{}

double TSP::fitness(TSPSolution solution)
const {
    assert(solution.size());
    double cost = 0;
    for(std::size_t i = 0; i < this->size(); ++i) {
        cost += this->distances[solution[i]][solution[(i+1)%this->size()]];
    }
    return cost;
}

double TSP::null_fitness()
const {
    return std::numeric_limits<double>().max();
}

bool TSP::best(double a, 
               double b)
const {
    return a < b;
}

std::vector<TSPSolution> TSP::neighborhood_all_swaps(TSPSolution solution)
const {
    std::vector<TSPSolution> neighbors;

    for(std::size_t i = 0; i < this->ncities; ++i) {
        for(std::size_t j = i+1; j < this->ncities; ++j) {
            neighbors.push_back(solution.swap(i,j));
        }
    }

    return neighbors;
}

std::vector<TSPSolution> TSP::neighborhood_random_swap(TSPSolution solution)
const {
    Random rng;
    unsigned i = rng.randint(0, solution.size()-1);
    unsigned j = rng.randint(0, solution.size()-1);
    return { solution.swap(i,j) };
}

std::vector<Provider<TSPSolution,double>::neighbor_function> TSP::neighborhoods()
const {
    return std::vector<Provider<TSPSolution,double>::neighbor_function> {
        std::bind(&TSP::neighborhood_random_swap, this, std::placeholders::_1),
        std::bind(&TSP::neighborhood_all_swaps, this, std::placeholders::_1),
    };
}

bool TSP::valid(TSPSolution solution) 
const {
    return solution.size() == this->size();
};

TSPSolution TSP::randomized_greedy(double alpha)
const {
    Random rng;
    TSPSolution solution;
    std::set<int> candidates;

    solution.push_back(0);
    for(unsigned i = 1; i < this->size(); ++i) candidates.insert(i);

    for(std::size_t i = 1; i < this->size(); ++i) {
        std::vector<std::pair<int,int>> tmp;
        double bound;
        int k = 0;

        for(int c : candidates) {
            tmp.emplace_back(this->distances[solution[i-1]][c],c);
        }
        
        std::sort(tmp.begin(), tmp.end());
        bound = tmp.begin()->first + alpha*(--tmp.end()->first - tmp.begin()->first);
        while(k < tmp.size() && tmp[k].first <= bound) ++k;

        unsigned next = tmp[rng.randint(0,k-1)].second;
        solution.push_back(next);
        candidates.erase(next);
    }

    return solution;
}

std::size_t TSP::size()
const {
    return this->ncities;
}

TSP TSP::read()
{
    std::size_t ncities;
    std::vector<std::vector<double>> distances;
    std::vector<std::pair<double,double>> coordinates;

    std::cin >> ncities;
    distances.assign(ncities, std::vector<double>(ncities,0));
    coordinates.resize(ncities);

    for(std::pair<double,double> &coordinate : coordinates) {
        std::cin >> coordinate.first >> coordinate.second;
    }

    for(std::size_t i = 0; i < ncities; ++i) {
        for(std::size_t j = i+1; j < ncities; ++j) {
            double distance = std::sqrt(
                std::pow(coordinates[i].first - coordinates[j].first, 2)
                + std::pow(coordinates[i].second - coordinates[j].second, 2));
            distances[i][j] = distances[j][i] = distance;
        }    
    }

    return TSP(ncities, distances);
}