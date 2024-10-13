/**
 * @file Solution.hpp
 * @brief Definition of the Solution class.
 */

#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include "DoublyLinkedList.hpp"
#include "Instance.hpp"
#include <cmath>
#include <cstddef>
#include <exception>
#include <vector>

/**
 * @class InstanceNotLoadedException
 * @brief Exception thrown when an instance is not loaded.
 */
class InstanceNotLoadedException : public std::exception {
public:
  /**
   * @brief Get the description of the exception.
   *
   * @return The description of the exception.
   */
  const char *what();
};

/**
 * @class Solution
 * @brief Definition of a solution to an instance.
 */
class Solution {
public:
  /**
   * @brief The vector of indices representing the solution.
   */
  DoublyLinkedList fruit_order;

  /**
   * @brief Default constructor.
   */
  Solution();

  /**
   * @brief Create a solution for an instance.
   *
   * @param instance The instance to create the solution for.
   */
  void createSolution(Instance &instance);

  /**
   * @brief Calculate the fee value of a conclusion time and delivery time
   * limit.
   *
   * @param fee_per_minute The fee per minute.
   * @param conclusion_time The conclusion time.
   * @param delivery_time_limit The delivery time limit.
   *
   * @return The calculated fee value.
   */
  int32_t calculateFeeValue(int32_t fee_per_minute, int32_t conclusion_time,
                            int32_t delivery_time_limit);

  /**
   * @brief Get the fee of the solution in float format.
   *
   * @return The fee of the solution in float format.
   */
  int32_t getSolutionFee();

  /**
   * @brief Update the solution with a new path.
   *
   * @param instance The instance associated with the solution.
   * @param new_solution The new vector of fruits representing the path.
   */
  void updateSolution(Instance &instance, DoublyLinkedList new_solution);

  /**
   * @brief Update the solution with a new path.
   *
   * @param instance The instance associated with the solution.
   * @param new_solution The new vector of fruits representing the path.
   * @param solution_fee The solution fee of the new path
   */
  void updateSolution(Instance &instance, DoublyLinkedList new_solution,
                      float solution_fee);

  /**
   * @brief Recalculate the solution based on the current internal path.
   *
   * @param instance The instance associated with the solution.
   */
  void recalculateSolution(Instance &instance);

  /**
   * @brief Recalculate the solution with a given path.
   *
   * @param instance The instance associated with the solution.
   * @param solution The vector of fruits representing the path.
   * @return The new solution fee.
   */
  int32_t recalculateSolution(Instance &instance, DoublyLinkedList &solution);

  /**
   * @brief Set the solution fee.
   *
   * @param solution_fee The new solution fee.
   */
  void setSolutionFee(int32_t new_fee);

  void setSequence(DoublyLinkedList new_sequence);

private:
  /**
   * @brief The total fee of the solution.
   */
  int32_t solution_fee;

  /**
   * @brief The elapsed time of the solution.
   */
  int32_t elapsed_time;

  DoublyLinkedList cached_greedy_solution;
  int32_t cached_solution_fee;
  int32_t cached_elapsed_time;
};

#endif
