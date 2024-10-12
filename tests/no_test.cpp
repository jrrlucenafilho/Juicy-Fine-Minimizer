#include "Instance.hpp"
#include "NeighborhoodOperations.hpp"
#include "Solution.hpp"
#include "gtest/gtest.h"

TEST(NoTest, ShouldReturnFalseIfCostIsHigherAfterSwapOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.createSolution(instance);

  bool res = BestImprovementSwap(instance, solution);

  ASSERT_FALSE(res);
}

TEST(NoTest, ShouldNotSwapIfCostIsHigherAfterSwapOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.createSolution(instance);

  BestImprovementSwap(instance, solution);

  ASSERT_EQ(solution.fruit_order.front()->value, 0);
  ASSERT_EQ(solution.fruit_order.front()->next->value, 1);
  ASSERT_EQ(solution.fruit_order.front()->next->next->value, 2);
  ASSERT_EQ(solution.fruit_order.front()->next->next->next->value, 3);
  ASSERT_EQ(solution.fruit_order.front()->next->next->next->next->value, 4);
}

TEST(NoTest, ShouldReturnTrueIfCostIsHigherAfterSwapOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.fruit_order.push_back(4);
  solution.fruit_order.push_back(3);
  solution.fruit_order.push_back(2);
  solution.fruit_order.push_back(1);
  solution.fruit_order.push_back(0);

  solution.recalculateSolution(instance);

  bool res = BestImprovementSwap(instance, solution);

  ASSERT_TRUE(res);
}

TEST(NoTest, ShouldSwapIfCostIsHigherAfterSwapOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.fruit_order.push_back(4);
  solution.fruit_order.push_back(3);
  solution.fruit_order.push_back(2);
  solution.fruit_order.push_back(1);
  solution.fruit_order.push_back(0);

  solution.recalculateSolution(instance);

  BestImprovementSwap(instance, solution);

  ASSERT_EQ(solution.fruit_order.front()->value, 0);
  ASSERT_EQ(solution.fruit_order.front()->next->value, 3);
  ASSERT_EQ(solution.fruit_order.front()->next->next->value, 2);
  ASSERT_EQ(solution.fruit_order.front()->next->next->next->value, 1);
  ASSERT_EQ(solution.fruit_order.front()->next->next->next->next->value, 4);
}

TEST(NoTest, NoTest_ShouldReturnFalseIfCostIsHigherAfterOrOptOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.createSolution(instance);

  bool res = BestImprovementOrOpt(instance, solution);

  ASSERT_FALSE(res);
}

TEST(NoTest, NoTest_ShouldNotChangeIfCostIsHigherAfterOrOptOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.createSolution(instance);

  bool res = BestImprovementOrOpt(instance, solution);

  ASSERT_EQ(solution.fruit_order.front()->value, 0);
  ASSERT_EQ(solution.fruit_order.front()->next->value, 1);
  ASSERT_EQ(solution.fruit_order.front()->next->next->value, 2);
  ASSERT_EQ(solution.fruit_order.front()->next->next->next->value, 3);
  ASSERT_EQ(solution.fruit_order.front()->next->next->next->next->value, 4);
}

TEST(NoTest, ShouldReturnTrueIfCostIsHigherAfterOrOptOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.fruit_order.push_back(4);
  solution.fruit_order.push_back(3);
  solution.fruit_order.push_back(2);
  solution.fruit_order.push_back(1);
  solution.fruit_order.push_back(0);

  solution.recalculateSolution(instance);

  bool res = BestImprovementOrOpt(instance, solution);

  ASSERT_TRUE(res);
}

TEST(NoTest, ShouldSwapIfCostIsHigherAfterOrOptOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.fruit_order.push_back(4);
  solution.fruit_order.push_back(3);
  solution.fruit_order.push_back(2);
  solution.fruit_order.push_back(1);
  solution.fruit_order.push_back(0);

  solution.recalculateSolution(instance);

  BestImprovementOrOpt(instance, solution);

  ASSERT_EQ(solution.fruit_order.front()->value, 3);
  ASSERT_EQ(solution.fruit_order.front()->next->value, 2);
  ASSERT_EQ(solution.fruit_order.front()->next->next->value, 1);
  ASSERT_EQ(solution.fruit_order.front()->next->next->next->value, 4);
  ASSERT_EQ(solution.fruit_order.front()->next->next->next->next->value, 0);
}

TEST(NoTest, ShouldReturnFalseIfCostIsHigherAfter2OptOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.createSolution(instance);

  bool res = BestImprovement2Opt(instance, solution);

  ASSERT_FALSE(res);
}

TEST(NoTest, ShouldNotChangeIfCostIsHigherAfter2OptOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.createSolution(instance);

  bool res = BestImprovement2Opt(instance, solution);

  ASSERT_EQ(solution.fruit_order.front()->value, 0);
  ASSERT_EQ(solution.fruit_order.front()->next->value, 1);
  ASSERT_EQ(solution.fruit_order.front()->next->next->value, 2);
  ASSERT_EQ(solution.fruit_order.front()->next->next->next->value, 3);
  ASSERT_EQ(solution.fruit_order.front()->next->next->next->next->value, 4);
}

TEST(NoTest, ShouldReturnTrueIfCostIsHigherAfter2OptOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.fruit_order.push_back(4);
  solution.fruit_order.push_back(3);
  solution.fruit_order.push_back(2);
  solution.fruit_order.push_back(1);
  solution.fruit_order.push_back(0);

  solution.recalculateSolution(instance);

  bool res = BestImprovement2Opt(instance, solution);

  ASSERT_TRUE(res);
}

TEST(NoTest, ShouldSwapIfCostIsHigherAfter2OptOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.fruit_order.push_back(4);
  solution.fruit_order.push_back(3);
  solution.fruit_order.push_back(2);
  solution.fruit_order.push_back(1);
  solution.fruit_order.push_back(0);

  solution.recalculateSolution(instance);

  BestImprovement2Opt(instance, solution);

  ASSERT_EQ(solution.fruit_order.front()->value, 0);
  ASSERT_EQ(solution.fruit_order.front()->next->value, 1);
  ASSERT_EQ(solution.fruit_order.front()->next->next->value, 2);
  ASSERT_EQ(solution.fruit_order.front()->next->next->next->value, 3);
  ASSERT_EQ(solution.fruit_order.front()->next->next->next->next->value, 4);
}