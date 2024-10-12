#include "Instance.hpp"
#include "Solution.hpp"
#include "gtest/gtest.h"

TEST(SolutionTest, ShouldCreateSolution) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.createSolution(instance);

  ASSERT_EQ(solution.fruit_order.size(), 5);
}

TEST(SolutionTest, ShouldUseGreedyAlgorithmWhenCreateSolution) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.createSolution(instance);

  ASSERT_EQ(solution.fruit_order.front()->value, 0);
  ASSERT_EQ(solution.fruit_order.front()->next->value, 1);
  ASSERT_EQ(solution.fruit_order.front()->next->next->value, 2);
  ASSERT_EQ(solution.fruit_order.front()->next->next->next->value, 3);
  ASSERT_EQ(solution.fruit_order.front()->next->next->next->next->value, 4);
}

TEST(SolutionTest, ShouldUseGreedyAlgorithmAndCorrectFeeWhenCreateSolution) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.createSolution(instance);

  ASSERT_EQ(solution.getSolutionFee(), 360);
}
