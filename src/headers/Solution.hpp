#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include "Instance.hpp"
#include <cmath>
#include <cstddef>
#include <exception>
#include <vector>

class InstanceNotLoadedException : public std::exception {
  const char *what();
};

class Solution {
public:
  Solution();

  void createSolution(Instance &instance);

  float_t calculateFeeValue(float_t fee_per_minute, uint32_t conclusion_time,
                         uint32_t delivery_time_limit);

  std::vector<size_t> getSolution();

private:
  std::vector<size_t> fruit_order;
  float_t solution_fee;
  uint32_t elapsed_time;
};

#endif
