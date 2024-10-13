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

    if (text == ".\\instances\\ex_instance.txt"){
      return "ex_instance";
    }

    return "";
}

// Print current iteration's solution and cost
void PrintCurrentIteration(int iteration, const vector<size_t>& curr_solution_sequence, int32_t current_cost) {
  std::cout << "============================================================================\n";
  std::cout << "Iteration: " << iteration << '\n';
  std::cout << "Solution Cost: " << current_cost << '\n';
  std::cout << "Solution Sequence: ";

  for (size_t i = 0; i < curr_solution_sequence.size(); i++) {
      std::cout << curr_solution_sequence[i];

      if (i != curr_solution_sequence.size() - 1) {
          std::cout << ", ";
      }
  }

  std::cout << '\n';
  std::cout << "============================================================================\n";
}

benchmarker_t benchmarker;

int main(int argc, char *argv[]) {
  if ((argc > 2) || (argc < 2)) {
    std::cerr << "Wrong input. Please write './main <instance_filepath>'";
    return 1;
  }

  std::map<std::string, int32_t> optimal_values_map = {
      {"ex_instance", 360},
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

  // Define upper limit for ILS execs (used same rule as ILS for TSP here)
  if (instance.getQuantityOfRequests() >= 150) {
    max_iters_ILS = instance.getQuantityOfRequests() / 2;
  } else {
    max_iters_ILS = instance.getQuantityOfRequests();
  }

  // Doing 10 execs as specified
  for (int i = 0; i < 10; i++) {
    srand(static_cast<unsigned int>(time(0)));

    benchmarker.metaheuristic_start_time = std::chrono::high_resolution_clock::now();
    solution = IteratedLocalSearch(max_iters, max_iters_ILS, instance);
    benchmarker.metaheuristic_end_time = std::chrono::high_resolution_clock::now();

    benchmarker.metaheuristic_avg_elapsed_time += (benchmarker.metaheuristic_end_time - benchmarker.metaheuristic_start_time);

    benchmarker.metaheuristic_solution_avg_cost += solution.getSolutionFee();

    // Keep track of best solution
    if (i == 0) {
      benchmarker.best_solution_cost = solution.getSolutionFee();
      benchmarker.best_solution_sequence = solution.getSolution();
      benchmarker.best_solution_iter = i;
    } else {
      if (solution.getSolutionFee() < benchmarker.best_solution_cost) {
        benchmarker.best_solution_cost = solution.getSolutionFee();
        benchmarker.best_solution_sequence = solution.getSolution();
        benchmarker.best_solution_iter = i;
      }
    }

    PrintCurrentIteration(i, solution.getSolution(), solution.getSolutionFee());
  }

  benchmarker.printResults(instance_name, optimal_values_map[instance_name]);

  return 0;
}
