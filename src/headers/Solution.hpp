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

  uint32_t calculateFeeValue(uint32_t fee_per_minute, uint32_t conclusion_time,
                         uint32_t delivery_time_limit);

  std::vector<size_t> getSolution();

  float_t getSolutionFee();

private:
  std::vector<size_t> fruit_order;
  uint32_t solution_fee;
  uint32_t elapsed_time;
};

#endif
