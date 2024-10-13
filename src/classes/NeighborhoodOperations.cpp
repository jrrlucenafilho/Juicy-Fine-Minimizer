#include "NeighborhoodOperations.hpp"
#include "vector"
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

// Neighborhood structures best improvement calc
bool BestImprovementSwap(Instance &instance, Solution &curr_solution) {
  bool optimized = false;
  int32_t curr_solution_fee = curr_solution.getSolutionFee();
  int32_t new_solution_fee;

  Node *first_index_swap = 0;
  Node *last_index_swap = 0;
  int32_t best_solution_fee = curr_solution_fee;

  for (Node *i = curr_solution.fruit_order.front(); i != nullptr; i = i->next) {
    for (Node *j = i->next; j != nullptr; j = j->next) {
      curr_solution.fruit_order.swap(i, j);

      curr_solution.recalculateSolution(instance);

      new_solution_fee = curr_solution.getSolutionFee();

      if (new_solution_fee < best_solution_fee) {
        first_index_swap = i;
        last_index_swap = j;
        best_solution_fee = new_solution_fee;

        optimized = true;
      }

      curr_solution.fruit_order.swap(i, j);
    }
  }

  if (first_index_swap != last_index_swap && optimized) {
    curr_solution.fruit_order.swap(first_index_swap, last_index_swap);
  }

  curr_solution.setSolutionFee(best_solution_fee);

  return optimized;
}

bool BestImprovementOrOpt(Instance &instance, Solution &curr_solution) {
  bool optimized = false;

  Node *index_to_remove = nullptr;
  Node *index_to_reinsert = nullptr;

  int32_t curr_solution_fee = curr_solution.getSolutionFee();

  int32_t optimum_solution_fee = curr_solution_fee;

  for (Node *i = curr_solution.fruit_order.front(); i != nullptr; i = i->next) {
    for (Node *j = curr_solution.fruit_order.front();
         j != curr_solution.fruit_order.back(); j = j->next) {
      if (i == j)
        continue;

      Node *reinsertion_insert_index = j;
      Node *initial_front_node = i->next;
      Node *initial_back_node = i->prev;

      curr_solution.fruit_order.reinsert_before(j, i);

      curr_solution.recalculateSolution(instance);

      if (curr_solution.getSolutionFee() < optimum_solution_fee) {
        index_to_remove = i;
        index_to_reinsert = reinsertion_insert_index;
        optimum_solution_fee = curr_solution.getSolutionFee();

        optimized = true;
      }

      if (initial_front_node) {
        curr_solution.fruit_order.reinsert_before(initial_front_node, i);
      } else {
        curr_solution.fruit_order.reinsert_after(initial_back_node, i);
      }
    }
  }

  if (index_to_remove != index_to_reinsert && optimized) {
    curr_solution.fruit_order.reinsert_before(index_to_reinsert,
                                              index_to_remove);
  }

  curr_solution.setSolutionFee(optimum_solution_fee);

  return optimized;
}

bool BestImprovementOrOpt2(Instance &instance, Solution &solution) {
  int32_t initial_cost = solution.getSolutionFee();

  int32_t best_cost = initial_cost;
  Node *best_first_el = nullptr;
  Node *best_reinsertion_position = nullptr;

  int32_t new_cost;

  for (Node *i = solution.fruit_order.front(); i != solution.fruit_order.back();
       i = i->next) {
    for (Node *j = solution.fruit_order.front(); j != nullptr; j = j->next) {
      // Skip invalid positions
      if ((j == i) || (j == i->next)) {
        continue;
      }
      Node *next_value = i->next;
      Node *initial_next_value = nullptr;

      if (i != solution.fruit_order.back()->prev)
        initial_next_value = i->next->next;

      Node *initial_back_node = i->prev;

      solution.fruit_order.reinsert_before(j, i);
      solution.fruit_order.reinsert_before(j, next_value);

      // Getting new cost after this move
      new_cost = solution.recalculateSolution(instance, solution.fruit_order);

      // Keep track of best sequence and it's cost
      if (new_cost < best_cost) {
        best_cost = new_cost;
        best_first_el = i;
        best_reinsertion_position = j;
      }

      if (initial_next_value) {
        // Redo the reinsertion operation
        solution.fruit_order.reinsert_before(initial_next_value, i);
        solution.fruit_order.reinsert_before(initial_next_value, next_value);
      } else {
        solution.fruit_order.reinsert_after(initial_back_node, next_value);
        solution.fruit_order.reinsert_after(initial_back_node, i);
      }
    }
  }

  // Update the solution if it's found a cost better than when it came in as
  // input So i only need to change it once
  if (best_cost < initial_cost) {
    Node *next_value = best_first_el->next;

    solution.fruit_order.reinsert_before(best_reinsertion_position,
                                         best_first_el);
    solution.fruit_order.reinsert_before(best_reinsertion_position, next_value);

    solution.setSolutionFee(best_cost);

    return true;
  }

  solution.setSolutionFee(best_cost);

  return false;
}

bool BestImprovementOrOpt3(Instance &instance, Solution &solution) {
  int32_t initial_cost = solution.getSolutionFee();

  int32_t best_cost = initial_cost;
  Node *best_first_el = nullptr;
  Node *best_reinsertion_position = nullptr;

  int32_t new_cost;

  for (Node *i = solution.fruit_order.front();
       i != solution.fruit_order.back()->prev; i = i->next) {
    for (Node *j = solution.fruit_order.front(); j != nullptr; j = j->next) {
      // Skip invalid positions
      if ((j == i) || (j == i->next) || (j == i->next->next)) {
        continue;
      }
      Node *initial_next_value = i->next->next->next;
      Node *initial_back_node = i->prev;
      Node *next_value_1 = i->next;
      Node *next_value_2 = i->next->next;

      solution.fruit_order.reinsert_before(j, i);
      solution.fruit_order.reinsert_before(j, next_value_1);
      solution.fruit_order.reinsert_before(j, next_value_2);

      // Getting new cost after this move
      new_cost = solution.recalculateSolution(instance, solution.fruit_order);

      // Keep track of best sequence and it's cost
      if (new_cost < best_cost) {
        best_cost = new_cost;
        best_first_el = i;
        best_reinsertion_position = j;
      }

      if (initial_next_value) {
        // Redo the reinsertion operation
        // Redo the reinsertion operation
        solution.fruit_order.reinsert_before(initial_next_value, i);
        solution.fruit_order.reinsert_before(initial_next_value, next_value_1);
        solution.fruit_order.reinsert_before(initial_next_value, next_value_2);
      } else {
        solution.fruit_order.reinsert_after(initial_back_node, next_value_2);
        solution.fruit_order.reinsert_after(initial_back_node, next_value_1);
        solution.fruit_order.reinsert_after(initial_back_node, i);
      }
    }
  }

  // Update the solution if it's found a cost better than when it came in as
  // input So i only need to change it once
  if (best_cost < initial_cost) {
    Node *next_value_1 = best_first_el->next;
    Node *next_value_2 = best_first_el->next->next;

    solution.fruit_order.reinsert_before(best_reinsertion_position,
                                         best_first_el);
    solution.fruit_order.reinsert_before(best_reinsertion_position,
                                         next_value_1);
    solution.fruit_order.reinsert_before(best_reinsertion_position,
                                         next_value_2);

    solution.setSolutionFee(best_cost);

    return true;
  }

  solution.setSolutionFee(best_cost);

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
  // Save first solution cost
  int32_t first_cost = solution.getSolutionFee();
  int32_t best_cost = first_cost;
  int32_t new_cost;

  Node *begin_reverse_best = nullptr;
  Node *end_reverse_best = nullptr;

  // Change from first element because it's the first arc, exhaustive in that it
  // tries every single combination
  for (Node *i = solution.fruit_order.front()->next;
       i != solution.fruit_order.back(); i = i->next) {
    for (Node *j = i->next->next; j != nullptr; j = j->next) {
      solution.fruit_order.reverse(i, j);

      // Calculate new cost
      new_cost = solution.recalculateSolution(instance, solution.fruit_order);

      // Compare costs, and attribute new_cost and new_sequence if new_cost is
      // lower
      if (new_cost < best_cost) {
        best_cost = new_cost;
        begin_reverse_best = i;
        end_reverse_best = j;
      }

      solution.fruit_order.reverse(i, j);
    }
  }

  // After testing, change solution to the lowest cost found, if it got any
  // lower than when the solution came in as input
  if (best_cost < first_cost) {
    solution.fruit_order.reverse(begin_reverse_best, end_reverse_best);
    solution.setSolutionFee(best_cost);

    return true;
  }

  solution.setSolutionFee(best_cost);

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
  vector<int> neighborhood_structures = {SWAP, TWO_OPT, OR_OPT, OR_OPT_2,
                                         OR_OPT_3};
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
int BoundedRand(int min, int max) { return min + rand() % (max - min + 1); }

/**
 * @brief Disturbs the solution so as to make it not fall into a local best
 * pitfall (Double Bridge disturbance)
 *
 * @param instance  instance object
 * @param solution  solution object
 * @return disturbed solution
 */
Solution Disturbance(Instance &instance, Solution &solution) {
  Solution disturbed_solution = solution;
  // DoublyLinkedList copied_sequence = solution.fruit_order;
  int sequence_size = instance.getQuantityOfRequests();

  int32_t max_distance_swap_exchange = sequence_size / 5;

  int32_t first_adj_swap_index = rand() % (sequence_size - 1);

  int32_t second_adj_swap_index;
  while (true) {
    second_adj_swap_index = rand() % (sequence_size - 1);

    if (second_adj_swap_index == first_adj_swap_index ||
        second_adj_swap_index == first_adj_swap_index + 1 ||
        second_adj_swap_index == first_adj_swap_index - 1) {
      second_adj_swap_index = rand() % (sequence_size - 1);
    } else {
      break;
    }
  }

  int32_t first_exchange_swap_index = rand() % (sequence_size - 1);

  int32_t second_exchange_swap_index = 0;
  while (true) {
    int32_t second_exchange_swap_index =
        (first_exchange_swap_index - max_distance_swap_exchange) +
        rand() % (first_exchange_swap_index + max_distance_swap_exchange);

    if (second_exchange_swap_index != first_exchange_swap_index) {
      break;
    }
  }

  Node *first_adj_swap_node = nullptr;
  Node *second_adj_swap_node = nullptr;

  Node *first_exchange_swap_node = nullptr;
  Node *second_exchange_swap_node = nullptr;

  Node *it = disturbed_solution.fruit_order.front();
  int32_t counter = 0;
  while (it != nullptr) {
    if (counter == first_adj_swap_index) {
      first_adj_swap_node = it;
    }

    if (counter == second_adj_swap_index) {
      second_adj_swap_node = it;
    }

    if (counter == first_exchange_swap_index) {
      first_exchange_swap_node = it;
    }

    if (counter == second_exchange_swap_index) {
      second_exchange_swap_node = it;
    }

    if (first_adj_swap_node != nullptr && second_adj_swap_node != nullptr &&
        first_exchange_swap_node != nullptr &&
        second_exchange_swap_node != nullptr) {
      break;
    }

    counter++;
    it = it->next;
  }

  disturbed_solution.fruit_order.swap(first_adj_swap_node,
                                      first_adj_swap_node->next);
  disturbed_solution.fruit_order.swap(second_adj_swap_node,
                                      second_adj_swap_node->next);

  disturbed_solution.fruit_order.swap(first_exchange_swap_node,
                                      second_exchange_swap_node);

  // Recalculating fee/cost with disturbed sol
  disturbed_solution.recalculateSolution(instance);

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
