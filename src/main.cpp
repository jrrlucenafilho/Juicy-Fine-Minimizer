#include "Instance.hpp"
#include "Solution.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    Instance instance("instances/ex_instance");
    Solution solution;

    solution.createSolution(instance);

    std::cout << "Current Solution Fee: " << solution.getSolutionFee() << "\n";
}
