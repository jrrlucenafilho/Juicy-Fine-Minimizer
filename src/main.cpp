#include "Instance.hpp"
#include "Solution.hpp"
#include <iostream>

using namespace std;

//TODO: Change last two to what nh structures you'd prefer, may add more (or_opt 2 and 3)
enum NeighborhoodStructure {SWAP, TWO_OPT, OR_OPT};

// Neighborhood structures best improvement calc
bool BestImprovementSwap(Instance& instance, Solution& curr_solution)
{
    return true;
}

/*
bool BestImprovementSwap(Instance& instance, Solution& curr_solution)
{

}

bool BestImprovementSwap(Instance& instance, Solution& curr_solution)
{

}
*/

// Each BestImprovement changes the solution itself and rturns as bool if the cost is lower
void LocalSearchRVND(Instance& instance, Solution& curr_solution)
{
    vector<int> neighborhood_structures = {SWAP, TWO_OPT, OR_OPT};    // Iterating through vec is O(n) but n = nh structures quantity
    bool has_solution_improved = false;

    while(!neighborhood_structures.empty()){
        int rand_nh_num = rand() % neighborhood_structures.size();

        switch(neighborhood_structures[rand_nh_num]){
            case SWAP:
                has_solution_improved = BestImprovementSwap(instance, curr_solution);
                break;
            case TWO_OPT:
                //has_solution_improved = BestImprovement2Opt(); //TODO: Change to what you'll prefer for this problem
                break;
            case OR_OPT:
                //has_solution_improved = BestImprovementOrOpt();   //TODO: here too
                break;
        }
    
        // If sol has improved on any of these structures, it means there might still be room for it to improve more
        if(has_solution_improved){
            neighborhood_structures = {SWAP, TWO_OPT, OR_OPT};
        }else{
            neighborhood_structures.erase(neighborhood_structures.begin() + rand_nh_num);
        }
    }
}

int main(int argc, char* argv[])
{
    if((argc > 2) || (argc < 2)){
        std::cerr << "Wrong input. Please write './main <instance_filepath>'";
        return 1;
    }

    Instance instance(argv[1]);
    Solution solution;

    solution.createSolution(instance);

    std::cout << "Current Solution Fee: " << solution.getSolutionFee() << "\n";
}