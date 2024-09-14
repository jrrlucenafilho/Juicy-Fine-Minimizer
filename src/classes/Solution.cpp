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
  size_t current_max_fee_index = 0;
  float_t current_max_fee = std::numeric_limits<float_t>::min();

  for (int i = 0; i < instance.getQuantityOfRequests(); i++) {
    size_t current_max_fee_index = 0;
    float_t current_max_fee = std::numeric_limits<float_t>::min();
    uint32_t current_elapsed_time = this->elapsed_time;

    if (i == 0) {
      for (int j = 0; j < instance.getQuantityOfRequests(); j++) {
        float_t fee_value = this->calculateFeeValue(
            instance.getLateFee(j), instance.getProductionTime(j),
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
                instance.getTransitionTime(this->fruit_order.back(), j) +
                this->elapsed_time,
            instance.getDeliveryTimeLimit(j));

        if (fee_value >= current_max_fee) {
          current_max_fee_index = j;
          current_max_fee = fee_value;
          current_elapsed_time =
              this->elapsed_time + instance.getProductionTime(j) +
              instance.getTransitionTime(this->fruit_order.back(), j) +
              this->elapsed_time;
        }
      }
    }

    this->fruit_order.push_back(current_max_fee_index);
    this->solution_fee += 0 > current_max_fee ? 0 : current_max_fee;
    this->elapsed_time = current_elapsed_time;
  }
}

float_t Solution::calculateFeeValue(float_t fee_per_minute,
                                    uint32_t conclusion_time,
                                    uint32_t delivery_time_limit) {
  return fee_per_minute * (conclusion_time - delivery_time_limit);
}

std::vector<size_t> Solution::getSolution() { return this->fruit_order; }
