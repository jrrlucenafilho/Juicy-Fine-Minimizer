#include "Solution.hpp"
#include "Instance.hpp"
#include <algorithm>
#include <iostream>
#include <limits>

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
        if (this->fruit_order.find(j)) {
          continue;
        }

        fee_value = this->calculateFeeValue(
            instance.getLateFee(j),
            instance.getProductionTime(j) +
                instance.getTransitionTime(this->fruit_order.back()->value + 1,
                                           j) +
                this->elapsed_time,
            instance.getDeliveryTimeLimit(j));

        if (fee_value >= current_max_fee) {
          current_max_fee_index = j;
          current_max_fee = fee_value;
          current_elapsed_time =
              this->elapsed_time + instance.getProductionTime(j) +
              instance.getTransitionTime(this->fruit_order.back()->value + 1,
                                         j);
        }
      }
    }

    this->fruit_order.push_back(current_max_fee_index);
    this->solution_fee += 0 > current_max_fee ? 0 : current_max_fee;
    this->elapsed_time = current_elapsed_time;
  }
}

int32_t Solution::calculateFeeValue(int32_t fee_per_minute,
                                    int32_t conclusion_time,
                                    int32_t delivery_time_limit) {
  int32_t current_solution_fee =
      fee_per_minute * (conclusion_time - delivery_time_limit);
  return current_solution_fee;
}

int32_t Solution::getSolutionFee() { return this->solution_fee; }

void Solution::updateSolution(Instance &instance,
                              DoublyLinkedList new_solution) {
  this->fruit_order = new_solution;

  this->recalculateSolution(instance);
}

void Solution::updateSolution(Instance &instance, DoublyLinkedList new_solution,
                              float solution_fee) {
  this->fruit_order = new_solution;

  this->setSolutionFee(solution_fee);
}

void Solution::recalculateSolution(Instance &instance) {
  this->solution_fee = 0;
  this->elapsed_time = 0;
  int32_t current_solution_fee = 0;

  for (Node *i = this->fruit_order.front(); i != nullptr; i = i->next) {
    current_solution_fee = this->solution_fee;

    if (i == this->fruit_order.front()) {
      current_solution_fee +=
          calculateFeeValue(instance.getLateFee(i->value),
                            instance.getProductionTime(i->value) +
                                instance.getTransitionTime(0, i->value),
                            instance.getDeliveryTimeLimit(i->value));

      this->elapsed_time = instance.getProductionTime(i->value) +
                           instance.getTransitionTime(0, i->value);
    } else {
      current_solution_fee += calculateFeeValue(
          instance.getLateFee(i->value),
          instance.getProductionTime(i->value) +
              instance.getTransitionTime(i->prev->value + 1, i->value) +
              this->elapsed_time,
          instance.getDeliveryTimeLimit(i->value));

      this->elapsed_time +=
          instance.getProductionTime(i->value) +
          instance.getTransitionTime(i->prev->value + 1, i->value);
    }

    this->solution_fee = 0 > current_solution_fee ? 0 : current_solution_fee;
  }
}

int32_t Solution::recalculateSolution(Instance &instance,
                                      DoublyLinkedList &solution) {
  int32_t solution_fee = 0;
  int32_t elapsed_time = 0;
  int32_t current_solution_fee = 0;

  for (Node *i = solution.front(); i != nullptr; i = i->next) {
    current_solution_fee = solution_fee;

    if (i == solution.front()) {
      current_solution_fee +=
          calculateFeeValue(instance.getLateFee(i->value),
                            instance.getProductionTime(i->value) +
                                instance.getTransitionTime(0, i->value),
                            instance.getDeliveryTimeLimit(i->value));

      elapsed_time = instance.getProductionTime(i->value) +
                     instance.getTransitionTime(0, i->value);
    } else {
      current_solution_fee += calculateFeeValue(
          instance.getLateFee(i->value),
          instance.getProductionTime(i->value) +
              instance.getTransitionTime(i->prev->value + 1, i->value) +
              elapsed_time,
          instance.getDeliveryTimeLimit(i->value));

      elapsed_time += instance.getProductionTime(i->value) +
                      instance.getTransitionTime(i->prev->value + 1, i->value);
    }

    solution_fee = 0 > current_solution_fee ? 0 : current_solution_fee;
  }

  return solution_fee;
}

void Solution::setSolutionFee(int32_t new_fee) { this->solution_fee = new_fee; }

void Solution::setSequence(DoublyLinkedList new_sequence) {
  this->fruit_order = new_sequence;
}