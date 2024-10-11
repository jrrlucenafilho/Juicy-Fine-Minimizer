#include "NeighborhoodOperations.hpp"
#include "Instance.hpp"
#include "Solution.hpp"
#include "gtest/gtest.h"

TEST(NoTest, ShouldReturnFalseIfCostIsHigherAfterOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.createSolution(instance);

  bool res = BestImprovementSwap(instance, solution);

  ASSERT_FALSE(res);
}

TEST(NoTest, ShouldNotSwapIfCostIsHigherAfterOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.createSolution(instance);

  BestImprovementSwap(instance, solution);

  ASSERT_EQ(solution.getSolution()[0], 0);
  ASSERT_EQ(solution.getSolution()[1], 1);
  ASSERT_EQ(solution.getSolution()[2], 2);
  ASSERT_EQ(solution.getSolution()[3], 3);
  ASSERT_EQ(solution.getSolution()[4], 4);
}

TEST(NoTest, ShouldReturnTrueIfCostIsHigherAfterOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.updateSolution(instance, {4, 3, 2, 1, 0});

  bool res = BestImprovementSwap(instance, solution);

  ASSERT_TRUE(res);
}

TEST(NoTest, ShouldSwapIfCostIsHigherAfterOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.updateSolution(instance, {4, 3, 2, 1, 0});

  BestImprovementSwap(instance, solution);

  ASSERT_EQ(solution.getSolution()[0], 2);
  ASSERT_EQ(solution.getSolution()[1], 1);
  ASSERT_EQ(solution.getSolution()[2], 0);
  ASSERT_EQ(solution.getSolution()[3], 3);
  ASSERT_EQ(solution.getSolution()[4], 4);
}
