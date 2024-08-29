#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <functional>
#include <map>
#include <fstream>

#include <random.hpp>
#include <tsp.hpp>
#include <knapsack.hpp>
#include <methods/ls.hpp>
#include <methods/ils.hpp>
#include <methods/grasp.hpp>
#include <methods/vns.hpp>

void print_file(std::string path)
{
    std::ifstream file(path);
    std::string line;
    while(std::getline(file, line)) {
        std::cout << line << std::endl;
    }
}

template<typename SolutionType, typename FitnessType>
class Solver
{
private:
    Provider<SolutionType,FitnessType> *provider;
    LSManager<SolutionType,FitnessType> *ls;
    ILSManager<SolutionType,FitnessType> *ils;
    GRASPManager<SolutionType,FitnessType> *grasp;
    VNSManager<SolutionType,FitnessType> *vns;

public:
    Solver(Provider<SolutionType,FitnessType> *provider)
    {
        this->ls = new LSManager<SolutionType,FitnessType>(provider);
        this->ils = new ILSManager<SolutionType,FitnessType>(provider);
        this->grasp = new GRASPManager<SolutionType,FitnessType>(provider);
        this->vns = new VNSManager<SolutionType,FitnessType>(provider);
        this->provider = provider;
    }

    SolutionType solve(
        SolutionType initial,
        std::vector<std::string> args)
    {
        unsigned n = std::stoul(args.at(0));
        std::string method = args.at(1);

        if(method == "ILS") return ils->search(
            initial,
            provider->neighborhoods()[n],
            std::stoul(args.at(2)));
        else if(method == "GRASP") return grasp->search(
            initial,
            provider->neighborhoods()[n],
            std::stoul(args.at(2)),
            std::stoul(args.at(3)));
        else if(method == "VNS") return vns->search(
            initial, 
            provider->neighborhoods());
        return ls->search(
            initial, 
            provider->neighborhoods()[n]);
    }

    ~Solver()
    {
        delete this->ls;
        delete this->ils;
    }
};

int main(int argc, char *argv[])
{
    std::string problem, method;
    std::vector<std::string> args;

    try {
        args = std::vector<std::string>(argv,argv+argc);
        problem = args.at(1);
        args = std::vector<std::string>(args.begin()+2,args.end());
    }
    catch(...) {
        goto out_args;
    } 

    if(problem == "TSP") {
        TSP instance = TSP::read();
        Solver<TSP::solution_type,TSP::fitness_type> solver(&instance);

        TSPSolution answer = solver.solve(
            TSPSolution(instance.size()),
            args);

        std::cout << instance.fitness(answer) << std::endl;
    }
    else if(problem == "KNAPSACK") {
        Knapsack instance = Knapsack::read();
        Solver<Knapsack::solution_type,Knapsack::fitness_type> solver(&instance);
        KnapsackSolution initial = instance.random_solution();
        
        KnapsackSolution answer = solver.solve(
            initial,
            args);

        std::cout << instance.fitness(answer) << std::endl;
    }

    return 0;
    
    out_args:
    print_file("args.txt");
    
    return 0;
}