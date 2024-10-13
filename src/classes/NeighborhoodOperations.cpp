#include "NeighborhoodOperations.hpp"
#include "Benchmarker.hpp"
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

extern benchmarker_t benchmarker;

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

bool BestImprovementOrOpt2(Instance &instance, Solution &solution)
{
  vector<size_t> curr_sequence = solution.getSolution();

  // Sequence that'll yield the lowest cost among all others in this neighborhood
  vector<size_t> best_sequence = curr_sequence;

  // Holds the sequence that'll be reinserted somewhere else
  vector<size_t> re_subseq(2);

  int32_t initial_cost = solution.getSolutionFee();
  int32_t best_cost = initial_cost;
  int32_t new_cost;

  for(int i = 0; i < (int)instance.getQuantityOfRequests() - 1; i++){
    for(int j = 0; j <= (int)instance.getQuantityOfRequests(); j++){
      // Skip invalid positions
      if((j == i) || (j == i + 1)){
        continue;
      }
      // First attribute subseq that'll be removed
      re_subseq[0] = curr_sequence[i];
      re_subseq[1] = curr_sequence[i + 1];

      // Calculate distances to curr_sequence.begin()
      auto dist_j = std::distance(curr_sequence.begin(), curr_sequence.begin() + j);

      // Erase the subsequence
      curr_sequence.erase(curr_sequence.begin() + i, curr_sequence.begin() + i + 2);

      // Adjust the insertion point if necessary
      if(j > i){
          dist_j -= 2;
      }

      // Insert the subseq at new position
      curr_sequence.insert(curr_sequence.begin() + dist_j, re_subseq.begin(), re_subseq.end());

      // Getting new cost after this move
      new_cost = solution.recalculateSolution(instance, curr_sequence);

      // Keep track of best sequence and it's cost
      if(new_cost < best_cost){
        best_cost = new_cost;
        best_sequence = curr_sequence;
      }

      // Revert the changes to curr_sequence
      curr_sequence = solution.getSolution();
    }
  }

  // Update the solution if it's found a cost better than when it came in as input
  // So i only need to change it once
  if(best_cost < initial_cost){
    solution.updateSolution(instance, best_sequence, best_cost);
    return true;
  }

  return false;
}

bool BestImprovementOrOpt3(Instance &instance, Solution &solution) {
    vector<size_t> curr_sequence = solution.getSolution();
    vector<size_t> best_sequence = curr_sequence;
    vector<size_t> re_subseq(3);

    int32_t initial_cost = solution.getSolutionFee();
    int32_t best_cost = initial_cost;
    int32_t new_cost;

    for(int i = 0; i < (int)instance.getQuantityOfRequests() - 2; ++i){
        for(int j = 0; j <= (int)instance.getQuantityOfRequests(); ++j){
            if((j == i) || (j == i + 1) || (j == i + 2)){
              continue;
            }

            // First attribute subseq that'll be removed
            re_subseq[0] = curr_sequence[i];
            re_subseq[1] = curr_sequence[i + 1];
            re_subseq[2] = curr_sequence[i + 2];

            // Calculate distances to curr_sequence.begin()
            auto dist_j = std::distance(curr_sequence.begin(), curr_sequence.begin() + j);

            // Erase the subsequence
            curr_sequence.erase(curr_sequence.begin() + i, curr_sequence.begin() + i + 3);

            // Adjust the insertion point if necessary
            if (j > i) {
               dist_j -= 3;
            }

            // Insert the subseq at new position
            curr_sequence.insert(curr_sequence.begin() + dist_j, re_subseq.begin(), re_subseq.end());

            // Getting new cost after this move
            new_cost = solution.recalculateSolution(instance, curr_sequence);

            // Update the best sequence if the new cost is lower
            if(new_cost < best_cost){
                best_cost = new_cost;
                best_sequence = curr_sequence;
            }

            // Revert the changes to curr_sequence
            curr_sequence = solution.getSolution();
        }
    }

    if(best_cost < initial_cost){
        solution.updateSolution(instance, best_sequence, best_cost);
        return true;
    }

    return false;
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
  int32_t best_cost = first_cost;
  int32_t new_cost;

  // Change from first element because it's the first arc, exhaustive in that it
  // tries every single combination
  for (int i = 1; i < (int)instance.getQuantityOfRequests(); i++) {
    for (int j = i + 2; j < (int)instance.getQuantityOfRequests(); j++) {
      // Reverse subsequence in fruit order
      reverse(new_sequence.begin() + i, new_sequence.begin() + j);

      // Calculate new cost
      new_cost = solution.recalculateSolution(instance, new_sequence);

      // Compare costs, and attribute new_cost and new_sequence if new_cost is
      // lower
      if (new_cost < best_cost) {
        best_cost = new_cost;
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
  if (best_cost < first_cost) {
    solution.updateSolution(instance, best_sequence, best_cost);

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
  vector<int> neighborhood_structures = {SWAP, TWO_OPT, OR_OPT, OR_OPT_2, OR_OPT_3};
  bool has_solution_improved = false;

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
    case OR_OPT_2:
      has_solution_improved = BestImprovementOrOpt2(instance, curr_solution);
      break;
    case OR_OPT_3:
      has_solution_improved = BestImprovementOrOpt3(instance, curr_solution);
      break;
    }

    // If sol has improved on any of these structures, it means there might
    // still be room for it to improve more
    if (has_solution_improved) {
      neighborhood_structures = {SWAP, TWO_OPT, OR_OPT, OR_OPT_2, OR_OPT_3};
    } else {
      neighborhood_structures.erase(neighborhood_structures.begin() +
                                    rand_nh_num);
    }
  }
}

/**
 * @brief Returns a radnom value inbetween min and max
 * @param min min value
 * @param max max value
 * @return int 
 */
int BoundedRand(int min, int max)
{
  return min + rand() % (max - min + 1);
}

/**
 * @brief Disturbs the solution so as to make it not fall into a local best
 * pitfall (Double Bridge disturbance)
 *
 * @param instance  instance object
 * @param solution  solution object
 * @return disturbed solution
 */
Solution Disturbance(Instance &instance, Solution &solution)
{
  Solution disturbed_solution;
  vector<size_t> copied_sequence = solution.getSolution();
  int sequence_size = instance.getQuantityOfRequests();

  // Lengh should vary from 2 to (dimension / 10)
  int segment_max_length = ceil(instance.getQuantityOfRequests() / 10.0);

  // Indexes of subsequences
  int subseq_1_begin_index, subseq_1_end_index;
  int subseq_2_begin_index, subseq_2_end_index;

  // First attributing indexes randomly
  subseq_1_begin_index = BoundedRand(0, sequence_size - segment_max_length - segment_max_length);
  subseq_1_end_index = BoundedRand(subseq_1_begin_index, subseq_1_begin_index + segment_max_length);
  subseq_2_begin_index = BoundedRand(subseq_1_end_index, sequence_size - segment_max_length);
  subseq_2_end_index = BoundedRand(subseq_2_begin_index, subseq_2_begin_index + segment_max_length);

  // Making subsequences with randomly-chosen indexes
  vector<int> subseq_1(copied_sequence.begin() + subseq_1_begin_index, copied_sequence.begin() + subseq_1_end_index);
  vector<int> subseq_2(copied_sequence.begin() + subseq_2_begin_index, copied_sequence.begin() + subseq_2_end_index);

  //Calc'ing lengths of subseqs and space among them
  //int subseq_1_length = subseq_1_end_index - subseq_1_begin_index; //not needed for calcs
  int inbetween_subseqs_length = subseq_2_begin_index - subseq_1_end_index;
  int subseq_2_length = subseq_2_end_index - subseq_2_begin_index;

  // Actually swapping subsequences
  // Putting subseq_2 into subseq_1's previous space
  copied_sequence.erase(copied_sequence.begin() + subseq_1_begin_index, copied_sequence.begin() + subseq_1_end_index);
  copied_sequence.insert(copied_sequence.begin() + subseq_1_begin_index, subseq_2.begin(), subseq_2.end());

  // Putting subseq_1 into subseq_2's previous space
  copied_sequence.erase(copied_sequence.begin() + subseq_1_begin_index + subseq_2_length + inbetween_subseqs_length,
                        copied_sequence.begin() + subseq_1_begin_index + subseq_2_length + inbetween_subseqs_length + subseq_2_length);

  copied_sequence.insert(copied_sequence.begin() + subseq_1_begin_index + subseq_2_length + inbetween_subseqs_length,
                         subseq_1.begin(), subseq_1.end());

  // Recalculating fee/cost with disturbed sol
  disturbed_solution.updateSolution(instance, copied_sequence);

  return disturbed_solution;
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

  for (int i = 0; i < max_iters; i++) {
    // First build a viable solution
    Solution curr_iter_solution;
    Solution curr_best_solution;

    benchmarker.constr_heuristic_start_time = std::chrono::high_resolution_clock::now();
    curr_iter_solution.createSolution(instance);
    benchmarker.constr_heuristic_end_time = std::chrono::high_resolution_clock::now();

    benchmarker.constructive_heuristic_avg_elapsed_time += (benchmarker.constr_heuristic_end_time 
                                                         - benchmarker.constr_heuristic_start_time);

    benchmarker.constructive_heuristic_avg_cost += curr_iter_solution.getSolutionFee();

    curr_best_solution = curr_iter_solution; // In the beginning, first sol is
                                             // currently the best one

    int curr_iter_counter_ILS = 0;

    while (curr_iter_counter_ILS <= max_iters_ILS) {
      benchmarker.rvnd_start_time = std::chrono::high_resolution_clock::now();

      // Do the local search, small modifs to current iteration's solution
      LocalSearchRVND(instance, curr_iter_solution);

      benchmarker.rvnd_end_time = std::chrono::high_resolution_clock::now();
      benchmarker.rvnd_avg_elapsed_time += (benchmarker.rvnd_end_time - benchmarker.rvnd_start_time);

      benchmarker.rvnd_avg_cost += curr_iter_solution.getSolutionFee();

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