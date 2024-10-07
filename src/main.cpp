#include "Instance.hpp"
#include "Solution.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

// TODO: Change last two to what nh structures you'd prefer, may add more
// (or_opt 2 and 3)
enum NeighborhoodStructure { SWAP, TWO_OPT, OR_OPT };

// Neighborhood structures best improvement calc
bool BestImprovementSwap(Instance &instance, Solution &curr_solution) {
  return true;
}

bool BestImprovementOrOpt(Instance &instance, Solution &curr_solution) {
  std::vector<size_t> copy_curr_solution = curr_solution.getSolution();
  bool optimized = false;
  double curr_solution_fee = curr_solution.getSolutionFee();

  for (int i = 0; i < copy_curr_solution.size(); i++) {
    size_t random_insert_index = rand() % (copy_curr_solution.size());
    std::swap(copy_curr_solution[i], copy_curr_solution[random_insert_index]);

    double new_solution_fee =
        curr_solution.recalculateSolution(instance, copy_curr_solution) / 100.0;

    if (new_solution_fee < curr_solution_fee) {
      curr_solution.updateSolution(instance, copy_curr_solution);
      optimized = true;
    } else {
      std::swap(copy_curr_solution[random_insert_index], copy_curr_solution[i]);
    }
  }

  return optimized;
}

/*
bool BestImprovementSwap(Instance& instance, Solution& solution)   // John
{

}

bool BestImprovementOrOpt(Instance& instance, Solution& solution)   // Rick
{
    return true;
}
*/

// Each BestImprovement changes the solution itself and rturns as bool if the
// cost is lower
/**
 * @brief Random Variant Neighborhood Descent Local Search. Checks multiple
 * different neighborhood structures from a prebuilt solution and only returns
 * after none of the neighborhodd tests have lowered the solution's cost
 *
 * @param instance instance object
 * @param curr_solution pre-built solution
 */
void LocalSearchRVND(Instance &instance, Solution &curr_solution) {
  vector<int> neighborhood_structures = {
      SWAP, TWO_OPT,
      OR_OPT}; // Iterating through vec is O(n) but n = nh structures quantity
  bool has_solution_improved = false;

  while (!neighborhood_structures.empty()) {
    int rand_nh_num = rand() % neighborhood_structures.size(); // O(1)

    switch (neighborhood_structures[rand_nh_num]) {
    case SWAP:
      // has_solution_improved = BestImprovementSwap(instance, curr_solution);
      break;
    case TWO_OPT:
      // has_solution_improved = BestImprovement2Opt(); //TODO: Change to what
      // you'll prefer for this problem
      break;
    case OR_OPT:
      has_solution_improved =
          BestImprovementOrOpt(instance, curr_solution); // TODO: here too
      break;
    }

    // If sol has improved on any of these structures, it means there might
    // still be room for it to improve more
    if (has_solution_improved) {
      neighborhood_structures = {SWAP, TWO_OPT, OR_OPT};
    } else {
      neighborhood_structures.erase(neighborhood_structures.begin() +
                                    rand_nh_num);
    }
  }
}

// ILS metaheuristic func
/**
 * @brief ILS Metaheuristic function. Run Iterated Local Search on a
 * greedy-algorithm-built viable solution
 *
 * @param max_iters Times a solution will be built put through ILS
 * @param max_iters_ILS Times ILS will be executed on  given viable solution
 * @param instance instance object
 * @return Best-of-All Solution found
 */
Solution IteratedLocalSearch(int max_iters, int max_iters_ILS,
                             Instance &instance) {
  Solution best_of_all_solution;
  best_of_all_solution.setSolutionFee(INFINITY);

  for (int i = 0; i < max_iters; i++) {
    // First build a viable solution
    Solution curr_iter_solution;
    Solution curr_best_solution;

    curr_iter_solution.createSolution(instance);
    curr_best_solution = curr_iter_solution; // In the beginning, first sol is
                                             // currently the best one

    int curr_iter_counter_ILS = 0;

    while (curr_iter_counter_ILS <= max_iters_ILS) {
      // Do the local search, small modifs to current iteration's solution
      LocalSearchRVND(instance, curr_iter_solution);

      // Compare curr iter's solution post-local-search to current
      // all-ILS-up-to-now execs best solution If it's lower, make it the new
      // best solution and restart ILS Same logic as the RVND. If it's improved
      // within current ILS, it has more room to improve Means it only doesn't
      // become the new best if it doesn't improve AT ALL once in all
      // max_iters_ILS execs
      if (curr_iter_solution.getSolutionFee() <
          curr_best_solution.getSolutionFee()) {
        curr_best_solution = curr_iter_solution;
        curr_iter_counter_ILS = 0;
      }

      // Disturbance to help solution not fall into a local best pitfall
      // Preferably disturb the curr_best_solution, disturbing from
      // curr_iter_solution causes fluctuations in the final solution on big and
      // heavy instances (gets always close to optimal answer, but never quite
      // so)
      // curr_iter_solution.Disturbance(curr_best_solution) or
      // curr_iter_solution = Disturbance(instance, curr_best_solution) //TODO
      curr_iter_counter_ILS++;
    }

    // Now after after 1 full ILS execution (Executing LocalSearchRVND()
    // max_iters_ILS times) Check if it produced a better solution than previous
    // ILS execution, attributing if so
    if (curr_best_solution.getSolutionFee() <
        best_of_all_solution.getSolutionFee()) {
      best_of_all_solution = curr_best_solution;
    }
  }

  return best_of_all_solution;
}

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
  // TODO: Check research papers to see if there's a better rule on choosing
  // max_iters_ILS for this specific problem
  if (instance.getQuantityOfRequests() >= 150) {
    max_iters_ILS = (int)instance.getQuantityOfRequests() / 2;
  } else {
    max_iters_ILS = (int)instance.getQuantityOfRequests();
  }

  // Doing 10 execs as specified
  for (int i = 0; i < 10; i++) {
    srand(static_cast<unsigned int>(time(0)));

    solution = IteratedLocalSearch(max_iters, max_iters_ILS, instance);

    // solution.calculateFeeValue(); //TODO: Might not be needed. Just to make
    // sure the cost is updated as of here
    iters_costs_sum += solution.getSolutionFee();

    cout << "Current Solution Fee (iter " << i + 1
         << "): " << solution.getSolutionFee() << '\n';
  }

  return 0;
}
