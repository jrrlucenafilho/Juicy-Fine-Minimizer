#include "Instance.hpp"
#include "NeighborhoodOperations.hpp"
#include "Solution.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  if ((argc > 2) || (argc < 2)) {
    std::cerr << "Wrong input. Please write './main <instance_filepath>'";
    return 1;
  }

  Instance instance(argv[1]);
  Solution solution;

  // ILS-used vars
  int max_iters = 50;
  int max_iters_ILS;
  int iters_costs_sum = 0;

  // Define upper limit for ILS execs (used same rule as ILS for TSP here)
  if (instance.getQuantityOfRequests() >= 150) {
    max_iters_ILS = (int)instance.getQuantityOfRequests() / 2;
  } else {
    max_iters_ILS = (int)instance.getQuantityOfRequests();
  }

  // Doing 10 execs as specified
  for (int i = 0; i < 10; i++) {
    srand(static_cast<unsigned int>(time(0)));

    solution = IteratedLocalSearch(max_iters, max_iters_ILS, instance);

    iters_costs_sum += solution.getSolutionFee();

    cout << "Current Solution Fee (iter " << i + 1
         << "): " << solution.getSolutionFee() << '\n';
  }

  return 0;
}
