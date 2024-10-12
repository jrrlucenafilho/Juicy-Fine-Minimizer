#include "Solution.hpp"
#include "Instance.hpp"
#include "Benchmarker.hpp"
#include <algorithm>
#include <iostream>
#include <limits>

extern benchmarker_t benchmarker;

const char *InstanceNotLoadedException::what() {
  return "Instance is not loaded!";
}

Solution::Solution() {
  this->solution_fee = 0;
  this->elapsed_time = 0;
}

void Solution::createSolution(Instance &instance) {
  if (!instance.isInstanceLoaded()) {
    throw InstanceNotLoadedException();
  }

  benchmarker.start_time = std::chrono::high_resolution_clock::now();

  this->solution_fee = 0;
  this->elapsed_time = 0;
  this->fruit_order.clear();

  for (int i = 0; i < instance.getQuantityOfRequests(); i++) {
    size_t current_max_fee_index = 0;
    int32_t current_max_fee = std::numeric_limits<int32_t>::min();
    int32_t current_elapsed_time = this->elapsed_time;
    int32_t fee_value = 0;

    if (i == 0) {
      for (size_t j = 0; j < instance.getQuantityOfRequests(); j++) {
        fee_value = this->calculateFeeValue(
            instance.getLateFee(j),
            instance.getProductionTime(j) + instance.getTransitionTime(0, j),
            instance.getDeliveryTimeLimit(j));

        if (fee_value >= current_max_fee) {
          current_max_fee_index = j;
          current_max_fee = fee_value;
          current_elapsed_time =
              instance.getProductionTime(j) + instance.getTransitionTime(0, j);
        }
      }
    } else {
      for (int j = 0; j < instance.getQuantityOfRequests(); j++) {
        // If the element is already in the solution then does not use it
        if (std::find(this->fruit_order.begin(), this->fruit_order.end(), j) !=
            this->fruit_order.end()) {
          continue;
        }

        fee_value = this->calculateFeeValue(
            instance.getLateFee(j),
            instance.getProductionTime(j) +
                instance.getTransitionTime(this->fruit_order.back() + 1, j) +
                this->elapsed_time,
            instance.getDeliveryTimeLimit(j));

        if (fee_value >= current_max_fee) {
          current_max_fee_index = j;
          current_max_fee = fee_value;
          current_elapsed_time =
              this->elapsed_time + instance.getProductionTime(j) +
              instance.getTransitionTime(this->fruit_order.back() + 1, j);
        }
      }
    }

    this->fruit_order.push_back(current_max_fee_index);
    this->solution_fee += 0 > current_max_fee ? 0 : current_max_fee;
    this->elapsed_time = current_elapsed_time;
  }

  benchmarker.end_time = std::chrono::high_resolution_clock::now();
  benchmarker.constructive_heuristic_avg_elapsed_time += benchmarker.end_time - benchmarker.start_time;
}

int32_t Solution::calculateFeeValue(int32_t fee_per_minute,
                                    int32_t conclusion_time,
                                    int32_t delivery_time_limit) {
  int32_t current_solution_fee =
      fee_per_minute * (conclusion_time - delivery_time_limit);
  return current_solution_fee;
}

std::vector<size_t> Solution::getSolution() { return this->fruit_order; }

int32_t Solution::getSolutionFee() { return this->solution_fee; }

void Solution::updateSolution(Instance &instance,
                              std::vector<size_t> new_solution) {
  this->fruit_order = new_solution;

  this->recalculateSolution(instance);
}

void Solution::updateSolution(Instance &instance,
                              std::vector<size_t> new_solution,
                              float solution_fee) {
  this->fruit_order = new_solution;

  this->setSolutionFee(solution_fee);
}

void Solution::recalculateSolution(Instance &instance) {
  this->solution_fee = 0;
  this->elapsed_time = 0;
  int32_t current_solution_fee = 0;

  for (size_t i = 0; i < this->fruit_order.size(); i++) {
    current_solution_fee = this->solution_fee;

    if (i == 0) {
      current_solution_fee += calculateFeeValue(
          instance.getLateFee(this->fruit_order[0]),
          instance.getProductionTime(this->fruit_order[0]) +
              instance.getTransitionTime(0, this->fruit_order[0]),
          instance.getDeliveryTimeLimit(this->fruit_order[0]));

      this->elapsed_time = instance.getProductionTime(this->fruit_order[0]) +
                            instance.getTransitionTime(0, this->fruit_order[0]);
    } else {
      current_solution_fee += calculateFeeValue(
          instance.getLateFee(this->fruit_order[i]),
          instance.getProductionTime(fruit_order[i]) +
              instance.getTransitionTime(this->fruit_order[i - 1] + 1,
                                         this->fruit_order[i]) +
              this->elapsed_time,
          instance.getDeliveryTimeLimit(this->fruit_order[i]));

      this->elapsed_time +=
          instance.getProductionTime(this->fruit_order[i]) +
          instance.getTransitionTime(this->fruit_order[i - 1] + 1,
                                     this->fruit_order[i]);
    }

    this->solution_fee = 0 > current_solution_fee ? 0 : current_solution_fee;
  }
}

int32_t Solution::recalculateSolution(Instance &instance,
                                      std::vector<size_t> solution) {
  int32_t solution_fee = 0;
  int32_t elapsed_time = 0;
  int32_t current_solution_fee = 0;

  for (size_t i = 0; i < this->fruit_order.size(); i++) {
    current_solution_fee = solution_fee;

    if (i == 0) {
      current_solution_fee +=
          calculateFeeValue(instance.getLateFee(solution[0]),
                            instance.getProductionTime(solution[0]) +
                                instance.getTransitionTime(0, solution[0]),
                            instance.getDeliveryTimeLimit(solution[0]));

      elapsed_time = instance.getProductionTime(solution[0]) +
                           instance.getTransitionTime(0, solution[0]);
    } else {
      current_solution_fee += calculateFeeValue(
          instance.getLateFee(solution[i]),
          instance.getProductionTime(solution[i]) +
              instance.getTransitionTime(solution[i - 1] + 1, solution[i]) +
              elapsed_time,
          instance.getDeliveryTimeLimit(solution[i]));

      elapsed_time +=
          instance.getProductionTime(solution[i]) +
          instance.getTransitionTime(solution[i - 1] + 1, solution[i]);
    }

    solution_fee = 0 > current_solution_fee ? 0 : current_solution_fee;
  }

  return solution_fee;
}

void Solution::setSolutionFee(int32_t new_fee) { this->solution_fee = new_fee; }

// Returns time passed up to a fruit located in index (in solution sequence)
int Solution::getConclusionTimeUpToIndex(int index, Instance &instance) {
  int conclusion_time = 10; // Constant first-fruit production time
  std::vector<size_t> &sequence = this->fruit_order;

  // Add up first fruit's production time
  conclusion_time += instance.getProductionTime(sequence[0]);

  for (int i = 1; i <= index; i++) {
    conclusion_time += instance.getTransitionTime(sequence[i - 1], sequence[i]);
  }

  return conclusion_time;
}

void Solution::reverseSubsequence(int index_begin, int index_end) {
  reverse(fruit_order.begin() + index_begin, fruit_order.begin() + index_end);
}
