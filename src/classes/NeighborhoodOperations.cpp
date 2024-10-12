#include "NeighborhoodOperations.hpp"
#include "vector"
#include <algorithm>
#include <limits>

using namespace std;

// Neighborhood structures best improvement calc
bool BestImprovementSwap(Instance &instance, Solution &curr_solution) {
  bool optimized = false;
  int32_t curr_solution_fee = curr_solution.getSolutionFee();
  int32_t new_solution_fee;

  size_t first_index_swap = 0;
  size_t last_index_swap = 0;
  int32_t best_solution_fee = curr_solution_fee;

  for (size_t i = 0; i < curr_solution.getSolution().size(); i++) {
    for (size_t j = i + 1; j < curr_solution.getSolution().size(); j++) {
      std::swap(curr_solution.fruit_order[i], curr_solution.fruit_order[j]);

      curr_solution.recalculateSolution(instance);

      new_solution_fee = curr_solution.getSolutionFee();

      if (new_solution_fee < best_solution_fee) {
        first_index_swap = i;
        last_index_swap = j;
        best_solution_fee = new_solution_fee;

        optimized = true;
      }

      std::swap(curr_solution.fruit_order[i], curr_solution.fruit_order[j]);
    }
  }

  if (first_index_swap != last_index_swap) {
    std::swap(curr_solution.fruit_order[first_index_swap], curr_solution.fruit_order[last_index_swap]);
    curr_solution.setSolutionFee(best_solution_fee);
  }

  return optimized;
}

bool BestImprovementOrOpt(Instance &instance, Solution &curr_solution) {
  bool optimized = false;

  size_t index_to_remove = 0;
  size_t index_to_reinsert = 0;
  uint32_t optimum_value_to_change = 0;

  int32_t curr_solution_fee = curr_solution.getSolutionFee();

  int32_t optimum_solution_fee = curr_solution_fee;

  for (size_t i = 0; i < curr_solution.fruit_order.size(); i++) {
    for (size_t j = 0; j < curr_solution.fruit_order.size() - 1; j++) {
      size_t reinsertion_insert_index = j;
      uint32_t value_to_change = curr_solution.fruit_order[i];

      curr_solution.fruit_order.erase(curr_solution.fruit_order.begin() + i);
      curr_solution.fruit_order.insert(curr_solution.fruit_order.begin() +
                                           reinsertion_insert_index,
                                       value_to_change);

      curr_solution.recalculateSolution(instance);

      if (curr_solution.getSolutionFee() < optimum_solution_fee) {
        index_to_remove = i;
        index_to_reinsert = reinsertion_insert_index;
        optimum_value_to_change = value_to_change;
        optimum_solution_fee = curr_solution.getSolutionFee();

        optimized = true;
      }

      curr_solution.fruit_order.erase(curr_solution.fruit_order.begin() +
                                      reinsertion_insert_index);
      curr_solution.fruit_order.insert(curr_solution.fruit_order.begin() + i,
                                       value_to_change);
    }
  }

  if (index_to_remove != index_to_reinsert) {
    curr_solution.fruit_order.erase(curr_solution.fruit_order.begin() +
                                    index_to_remove);
    curr_solution.fruit_order.insert(curr_solution.fruit_order.begin() +
                                         index_to_reinsert,
                                     optimum_value_to_change);

    curr_solution.setSolutionFee(optimum_solution_fee);
  }

  return optimized;
}

/**
 * @brief exhaustively compares current solution against all possible 2-opt
 * neighborhood structure movements
 *
 * @param instance instance file
 * @param solution current solution that'll be evaluated
 * @returns is_optimized bool that indicates if solution has been optimized
 */
bool BestImprovement2Opt(Instance &instance, Solution &solution) {
  vector<size_t> new_sequence = solution.getSolution();
  vector<size_t> best_sequence;

  // Save first solution cost
  int32_t first_cost = solution.getSolutionFee();
  int32_t old_cost = first_cost;
  int32_t new_cost;

  // Change from first element because it's the first arc, exhaustive in that it
  // tries every single combination
  for (size_t i = 1; i < instance.getQuantityOfRequests(); i++) {
    for (size_t j = i + 2; j < instance.getQuantityOfRequests(); j++) {
      // Reverse subsequence in fruit order
      reverse(new_sequence.begin() + i, new_sequence.begin() + j);

      // Calculate new cost
      new_cost = solution.recalculateSolution(instance, new_sequence);

      // Compare costs, and attribute new_cost and new_sequence if new_cost is
      // lower
      if (new_cost < old_cost) {
        old_cost = new_cost;
        best_sequence = new_sequence;
      } else {
        // So i always compare it to the input solution, and not last iter's
        // 2-opt'ed solution
        new_sequence = solution.getSolution();
      }
    }
  }

  // After testing, change solution to the lowest cost found, if it got any
  // lower than when the solution came in as input
  if (old_cost < first_cost) {
    solution.updateSolution(instance, best_sequence, old_cost);

    return true;
  }

  return false;
}

// Each BestImprovement changes the solution itself and returns as bool if the
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
  vector<int> neighborhood_structures = {SWAP, TWO_OPT, OR_OPT};
  bool has_solution_improved = false;

  // All this is relative to n60C instance
  // TODO(Fix): Cost that gets here from the greedy algorithm is
  // always 4.15766077e+10 And elapsed_time is always -933778592

  // TODO(Fix): And no matter which bestImprovement() (except swap, and now
  // except 2-opt) it goes into on the first iter The solution_fee always
  // becomes -763126528 and elapsed_time stays as -933778592 on the firts iter

  while (!neighborhood_structures.empty()) {
    int rand_nh_num = rand() % neighborhood_structures.size();

    switch (neighborhood_structures[rand_nh_num]) {
    case SWAP:
      has_solution_improved = BestImprovementSwap(instance, curr_solution);
      break;
    case TWO_OPT:
      has_solution_improved = BestImprovement2Opt(instance, curr_solution);
      break;
    case OR_OPT:
      has_solution_improved = BestImprovementOrOpt(instance, curr_solution);
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

/**
 * @brief Disturbs the solution so as to make it not fall into a local best
 * pitfall
 *
 * @param instance  instance object
 * @param solution  solution object
 * @return disturbed solution
 */
Solution Disturbance(Instance &instance, Solution &solution) {
  // Swaps
  int swap_index_i, swap_index_j;
  vector<size_t> new_sequence = solution.getSolution();

  swap_index_i = rand() % new_sequence.size();

  while (true) {
    swap_index_j = rand() % new_sequence.size();

    if (swap_index_i != swap_index_j) {
      break;
    }
  }

  std::swap(new_sequence[swap_index_i], new_sequence[swap_index_j]);

  // Recalc cost with disturbed solution
  solution.updateSolution(instance, new_sequence);

  return solution;
}

// ILS metaheuristic func
/**
 * @brief ILS Metaheuristic function. Run Iterated Local Search on a
 * greedy-algorithm-built viable solution
 *
 * @param max_iters Times a solution will be built put through ILS
 * @param max_iters_ILS Times ILS will be executed on given viable solution
 * @param instance instance object
 * @return Best-of-All Solution found
 */
Solution IteratedLocalSearch(int max_iters, int max_iters_ILS,
                             Instance &instance) {
  Solution best_of_all_solution;
  best_of_all_solution.setSolutionFee(std::numeric_limits<int32_t>::max());
  int32_t previous_solution_fee = std::numeric_limits<int32_t>::max();

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
      if (curr_iter_solution.getSolutionFee() == previous_solution_fee) {
        curr_iter_solution = Disturbance(instance, curr_iter_solution);
      }

      previous_solution_fee = curr_iter_solution.getSolutionFee();
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
