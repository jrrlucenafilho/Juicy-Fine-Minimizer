#include "Instance.hpp"
#include "Solution.hpp"
#include <cstdlib>
#include <experimental/filesystem>
#include <iostream>
#include <algorithm>

using namespace std;

enum NeighborhoodStructure { SWAP, TWO_OPT, OR_OPT };

// Neighborhood structures best improvement calc
bool BestImprovementSwap(Instance &instance, Solution &curr_solution) {
    std::vector<size_t> copy_curr_solution = curr_solution.getSolution();
    bool optimized = false;
    double curr_solution_fee = curr_solution.getSolutionFee();

    for (int i = 0; i < copy_curr_solution.size(); i++) {
        for (int j = i + 1; j < copy_curr_solution.size(); j++) {
            std::swap(copy_curr_solution[i], copy_curr_solution[j]);

            double new_solution_fee = curr_solution.recalculateSolution(instance, copy_curr_solution);

            if (new_solution_fee < curr_solution_fee) {
                curr_solution.updateSolution(instance, copy_curr_solution);
                optimized = true;
                curr_solution_fee = new_solution_fee;
            } else {
                std::swap(copy_curr_solution[i], copy_curr_solution[j]);
            }
        }
    }

    return optimized;
}

bool BestImprovementOrOpt(Instance &instance, Solution &curr_solution) {
  std::vector<size_t> copy_curr_solution = curr_solution.getSolution();
  bool optimized = false;
  double curr_solution_fee = curr_solution.getSolutionFee();

  for (int i = 0; i < copy_curr_solution.size(); i++) {
    for (int j = 0; j < copy_curr_solution.size() - 1; j++) { 
      size_t reinsertion_insert_index = j;
      uint32_t value_to_change = copy_curr_solution[i];

      copy_curr_solution.erase(copy_curr_solution.begin() + i);
      copy_curr_solution.insert(copy_curr_solution.begin() + reinsertion_insert_index, value_to_change);

    double new_solution_fee =
        curr_solution.recalculateSolution(instance, copy_curr_solution);

      if (new_solution_fee < curr_solution_fee) {
        curr_solution.updateSolution(instance, copy_curr_solution, new_solution_fee);
        curr_solution_fee = curr_solution.getSolutionFee();

        optimized = true;
      }

      copy_curr_solution.erase(copy_curr_solution.begin() + reinsertion_insert_index);
      copy_curr_solution.insert(copy_curr_solution.begin() + i, value_to_change);
    }
  }

  return optimized;
}

/**
 * @brief exhaustively compares current solution against all possible 2-opt neighborhood structure movements
 * 
 * @param instance instance file
 * @param solution current solution that'll be evaluated
 * @returns is_optimized bool that indicates if solution has been optimized
 */
bool BestImprovement2Opt(Instance& instance, Solution& solution)
{
/*  Slightly more efficient way
  // Deltas regarding cost/fee
  double best_cost = 0;
  double previous_cost, curr_cost, reversed_subseq_cost = 0;
  int best_i = 0; // Iter for the leftmost point to be cut int the seq
  int best_j = 0; // Iter for the rightmost point of the cut in the seq

  int conclusion_time_tracker = 0;

  // First cost is just the input sequence one
  previous_cost = solution.getSolutionFee();

  // Iters through the sequence element by element
  // Beginning from the second element cause the sequence has to start from an arc at least 
  for(int i = 1; i < (int)solution.getSolution().size(); i++){
    // And this iters as the second point-of-cut-for-sequence-reversal
    for(int j = i + 1; i < (int)solution.getSolution().size(); j++){
      // Here goes the calc that gets the reversal cost for current "i -> ... -> k -> ... -> j" 2-opt-reversed sequence
      // f' = f - (prev_i_and_j_edge_arcs_costs) + (new_i_and_j_edge_arc_costs); (inbetween costs are the same among sequences)
      // (prev_i_and_j_edge_arcs_costs) = cost_to_transition_to_fruit + cost_to_produce_fruit + cost_to_transition_to_next_fruit
      // TODO: Check if instance.getProductionTime()'s index is refers to the fruit's sequence position index

      // Doing it like this because, at least for small 2-opt subsequences (fairly common), it's cheaper than making a copy of the solution
      // Iterates throught the subsequence, calc'ing cost for each node as it's needed
      for(int k = i; k <= j; k++){
        // Get the time passed up to first element of to-be-reversed subseq
        conclusion_time_tracker += solution.
        reversed_subseq_cost += solution.calculateFeeValue(instance.getLateFee(solution.getSolution()[k]), instance., )
      }

      if(curr_cost < previous_cost){
        best_cost = curr_cost;
        best_i = i;
        best_j = j;
      }

    }
  }

  // Actual swap if the cost/fee got better
*/
 // Expensive but easier version
  vector<size_t> new_sequence = solution.getSolution();
  vector<size_t> best_sequence;

  // Save first solution cost
  double first_cost = solution.getSolutionFee();
  double old_cost = first_cost;
  double new_cost;

  // Change from first element because it's the first arc, exhaustive in that it tries every single combination
  for(int i = 1; i < (int)instance.getQuantityOfRequests(); i++){
    for(int j = i + 2; j < (int)instance.getQuantityOfRequests(); j++){
      // Reverse subsequence in fruit order
      reverse(new_sequence.begin() + i, new_sequence.begin() + j);

      // Calculate new cost
      new_cost = solution.recalculateSolution(instance, new_sequence);

      // Compare costs, and attribute new_cost and new_sequence if new_cost is lower
      if(new_cost < old_cost){
        old_cost = new_cost;
        best_sequence = new_sequence;
      }
    }
  }

  // After testing, change solution to the lowest cost found, if it got any lower than when the solution came in as input
  if(old_cost < first_cost){
    solution.setSolutionFee(solution.recalculateSolution(instance, best_sequence));
    solution.setSequence(best_sequence);

    return true;
  }

  return false;
}

// Each BestImprovement changes the solution itself and returns as bool if the cost is lower
/**
 * @brief Random Variant Neighborhood Descent Local Search. Checks multiple
 * different neighborhood structures from a prebuilt solution and only returns
 * after none of the neighborhodd tests have lowered the solution's cost
 *
 * @param instance instance object
 * @param curr_solution pre-built solution
 */
void LocalSearchRVND(Instance &instance, Solution &curr_solution) {
  vector<int> neighborhood_structures = { SWAP, TWO_OPT, OR_OPT }; // Iterating through vec is O(n) but n = nh structures quantity
  bool has_solution_improved = false;

  while (!neighborhood_structures.empty()) {
    int rand_nh_num = rand() % neighborhood_structures.size(); // O(1)

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
 * @brief Disturbs the solution so as to make it not fall into a local best pitfall
 * 
 * @param instance  instance object 
 * @param solution  solution object
 * @return disturbed solution
 */
Solution Disturbance(Instance& instance, Solution& solution)
{

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
            // Preferably disturb the curr_best_solution, disturbing from curr_iter_solution causes fluctuations in the final solution
            // on big and heavy instances (gets always close to optimal answer, but never quite so)
            curr_iter_solution = Disturbance(instance, curr_best_solution);
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
