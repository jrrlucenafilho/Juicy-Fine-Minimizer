#include "Instance.hpp"
#include "NeighborhoodOperations.hpp"
#include "Solution.hpp"
#include "Benchmarker.hpp"
#include <cstdlib>
#include <map>
#include <regex>
#include <string>
#include <iostream>

using namespace std;

std::string ExtractInstanceName(const std::string& text) {
    std::regex instance_regex(R"(.*\\(n.*)\.txt)");
    std::smatch match;

    if (std::regex_search(text, match, instance_regex)) {
        return match[1];
    }

    return "";
}

// Print current iteration's solution and cost
void PrintCurrentIteration(int iteration, const vector<size_t>& current_solution, int32_t current_cost) {
  std::cout << "============================================================================\n";
  std::cout << "Iteration: " << iteration << '\n';
  std::cout << "Current Solution Sequence: ";

  for (size_t element : current_solution) {
      std::cout << element << ", ";
  }

  std::cout << '\n';
  std::cout << "Current Solution Cost: " << current_cost << '\n';
  std::cout << "============================================================================\n";
}

benchmarker_t benchmarker;

int main(int argc, char *argv[]) {
  if ((argc > 2) || (argc < 2)) {
    std::cerr << "Wrong input. Please write './main <instance_filepath>'";
    return 1;
  }

  std::map<std::string, int32_t> optimal_values_map = {
      {"n60A", 453},
      {"n60B", 1757},
      {"n60C", 0},
      {"n60D", 69102},
      {"n60E", 58935},
      {"n60F", 93045},
      {"n60G", 64632}, // May be lower
      {"n60H", 145007},
      {"n60I", 43286},
      {"n60J", 53555},
      {"n60K", 458752},
      {"n60L", 332941},
      {"n60M", 516926},
      {"n60N", 492572},
      {"n60O", 527459}, // May be lower
      {"n60P", 396183}
  };

  Instance instance(argv[1]);
  Solution solution;
  std::string instance_name = ExtractInstanceName(argv[1]);

  // ILS-used vars
  int max_iters = 50;
  int max_iters_ILS;
  int iters_costs_sum = 0;

  // Define upper limit for ILS execs (used same rule as ILS for TSP here)
  if (instance.getQuantityOfRequests() >= 150) {
    max_iters_ILS = instance.getQuantityOfRequests() / 2;
  } else {
    max_iters_ILS = instance.getQuantityOfRequests();
  }

  // Doing 10 execs as specified
  for (int i = 0; i < 10; i++) {
    srand(static_cast<unsigned int>(time(0)));

    solution = IteratedLocalSearch(max_iters, max_iters_ILS, instance);

    iters_costs_sum += solution.getSolutionFee();

    // if (i == 0) {
    //   best_solution_cost = solution.getSolutionFee();
    //   best_solution_sequence = solution.getSolution();
    //   best_solution_iteration = i;
    // } else {
    //   if (solution.getSolutionFee() < best_solution_cost) {
    //     best_solution_cost = solution.getSolutionFee();
    //     best_solution_sequence = solution.getSolution();
    //     best_solution_iteration = i;
    //   }
    // }

    PrintCurrentIteration(i + 1, solution.getSolution(), solution.getSolutionFee());
  }

  benchmarker.printResults(instance_name, optimal_values_map[instance_name]);

  return 0;
}
