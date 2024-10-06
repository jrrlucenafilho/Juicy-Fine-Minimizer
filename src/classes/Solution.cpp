#include "Solution.hpp"
#include "Instance.hpp"
#include <algorithm>
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
    uint32_t current_max_fee = std::numeric_limits<uint32_t>::min();
    uint32_t current_elapsed_time = this->elapsed_time;

    if (i == 0) {
      for (int j = 0; j < instance.getQuantityOfRequests(); j++) {
        float_t fee_value = this->calculateFeeValue(
            instance.getLateFee(j),
            instance.getProductionTime(j) + instance.getTransitionTime(0, j),
            instance.getDeliveryTimeLimit(j));

        if (fee_value >= current_max_fee) {
          current_max_fee_index = j;
          current_max_fee = fee_value;
          current_elapsed_time =
              this->elapsed_time + instance.getProductionTime(j);
        }
      }
    } else {
      for (int j = 0; j < instance.getQuantityOfRequests(); j++) {
        // If the element is already in the solution then does not use it
        if (std::find(this->fruit_order.begin(), this->fruit_order.end(), j) !=
            this->fruit_order.end()) {
          continue;
        }

        float_t fee_value = this->calculateFeeValue(
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
              instance.getTransitionTime(this->fruit_order.back() + 1, j) +
              this->elapsed_time;
        }
      }
    }

    this->fruit_order.push_back(current_max_fee_index);
    this->solution_fee += 0 > current_max_fee ? 0 : current_max_fee;
    this->elapsed_time = current_elapsed_time;
  }
}

uint32_t Solution::calculateFeeValue(uint32_t fee_per_minute,
                                     uint32_t conclusion_time,
                                     uint32_t delivery_time_limit) {
  return fee_per_minute * (conclusion_time - delivery_time_limit);
}

std::vector<size_t> Solution::getSolution() { return this->fruit_order; }

float_t Solution::getSolutionFee() { return this->solution_fee / 100.0; }

void Solution::setSolutionFee(uint32_t solution_fee) {
  this->solution_fee = solution_fee;
}

void Solution::updateSolution(Instance &instance,
                              std::vector<size_t> new_solution) {
  this->fruit_order = new_solution;

  this->recalculateSolution(instance);
}

void Solution::recalculateSolution(Instance &instance) {
  this->solution_fee = 0;
  this->elapsed_time = 0;

  for (size_t i = 0; i < this->fruit_order.size(); i++) {
    if (i == 0) {
      this->solution_fee += calculateFeeValue(
          instance.getLateFee(this->fruit_order[0]),
          instance.getProductionTime(this->fruit_order[0]) +
              instance.getTransitionTime(0, this->fruit_order[0]),
          instance.getDeliveryTimeLimit(this->fruit_order[0]));

      this->elapsed_time += instance.getProductionTime(this->fruit_order[0]) +
                            instance.getTransitionTime(0, this->fruit_order[0]);
    }

    this->solution_fee += calculateFeeValue(
        instance.getLateFee(this->fruit_order[i]),
        instance.getProductionTime(i) +
            instance.getTransitionTime(this->fruit_order[i - 1],
                                       this->fruit_order[i]) +
            this->elapsed_time,
        instance.getDeliveryTimeLimit(this->fruit_order[i]));

    this->elapsed_time += instance.getProductionTime(this->fruit_order[i]) +
                          instance.getTransitionTime(0, this->fruit_order[i]);
  }
}

uint32_t Solution::recalculateSolution(Instance &instance,
                                       std::vector<size_t> solution) {
  uint32_t solution_fee = 0;
  uint32_t elapsed_time = 0;

  for (size_t i = 0; i < this->fruit_order.size(); i++) {
    if (i == 0) {
      this->solution_fee += calculateFeeValue(
          instance.getLateFee(this->fruit_order[0]),
          instance.getProductionTime(this->fruit_order[0]) +
              instance.getTransitionTime(0, this->fruit_order[0]),
          instance.getDeliveryTimeLimit(this->fruit_order[0]));

      this->elapsed_time += instance.getProductionTime(this->fruit_order[0]) +
                            instance.getTransitionTime(0, this->fruit_order[0]);
    }

    this->solution_fee += calculateFeeValue(
        instance.getLateFee(this->fruit_order[i]),
        instance.getProductionTime(i) +
            instance.getTransitionTime(this->fruit_order[i - 1],
                                       this->fruit_order[i]) +
            this->elapsed_time,
        instance.getDeliveryTimeLimit(this->fruit_order[i]));

    this->elapsed_time += instance.getProductionTime(this->fruit_order[i]) +
                          instance.getTransitionTime(0, this->fruit_order[i]);
  }

  return solution_fee;
}
