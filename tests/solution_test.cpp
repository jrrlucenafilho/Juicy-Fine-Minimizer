#include "Instance.hpp"
#include "Solution.hpp"
#include "gtest/gtest.h"

TEST(SolutionTest, ShouldCreateSolution) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.createSolution(instance);

  ASSERT_EQ(solution.getSolution().size(), 5);
}
