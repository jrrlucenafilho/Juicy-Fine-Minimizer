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

  ASSERT_EQ(solution.getSolution()[0], 0);
  ASSERT_EQ(solution.getSolution()[1], 1);
  ASSERT_EQ(solution.getSolution()[2], 2);
  ASSERT_EQ(solution.getSolution()[3], 3);
  ASSERT_EQ(solution.getSolution()[4], 4);
}

TEST(NoTest, ShouldReturnTrueIfCostIsHigherAfterSwapOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.updateSolution(instance, {4, 3, 2, 1, 0});

  bool res = BestImprovementSwap(instance, solution);

  ASSERT_TRUE(res);
}

TEST(NoTest, ShouldSwapIfCostIsHigherAfterSwapOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.updateSolution(instance, {4, 3, 2, 1, 0});

  BestImprovementSwap(instance, solution);

  ASSERT_EQ(solution.getSolution()[0], 0);
  ASSERT_EQ(solution.getSolution()[1], 3);
  ASSERT_EQ(solution.getSolution()[2], 2);
  ASSERT_EQ(solution.getSolution()[3], 1);
  ASSERT_EQ(solution.getSolution()[4], 4);
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

  ASSERT_EQ(solution.getSolution()[0], 0);
  ASSERT_EQ(solution.getSolution()[1], 1);
  ASSERT_EQ(solution.getSolution()[2], 2);
  ASSERT_EQ(solution.getSolution()[3], 3);
  ASSERT_EQ(solution.getSolution()[4], 4);
}

TEST(NoTest, ShouldReturnTrueIfCostIsHigherAfterOrOptOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.updateSolution(instance, {4, 3, 2, 1, 0});

  bool res = BestImprovementOrOpt(instance, solution);

  ASSERT_TRUE(res);
}

TEST(NoTest, ShouldSwapIfCostIsHigherAfterOrOptOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.updateSolution(instance, {4, 3, 2, 1, 0});

  BestImprovementOrOpt(instance, solution);

  ASSERT_EQ(solution.getSolution()[0], 3);
  ASSERT_EQ(solution.getSolution()[1], 2);
  ASSERT_EQ(solution.getSolution()[2], 1);
  ASSERT_EQ(solution.getSolution()[3], 4);
  ASSERT_EQ(solution.getSolution()[4], 0);
}

TEST(NoTest, NoTest_ShouldReturnFalseIfCostIsHigherAfter2OptOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.createSolution(instance);

  bool res = BestImprovement2Opt(instance, solution);

  ASSERT_FALSE(res);
}

TEST(NoTest, NoTest_ShouldNotChangeIfCostIsHigherAfter2OptOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.createSolution(instance);

  bool res = BestImprovement2Opt(instance, solution);

  ASSERT_EQ(solution.getSolution()[0], 0);
  ASSERT_EQ(solution.getSolution()[1], 1);
  ASSERT_EQ(solution.getSolution()[2], 2);
  ASSERT_EQ(solution.getSolution()[3], 3);
  ASSERT_EQ(solution.getSolution()[4], 4);
}

TEST(NoTest, ShouldReturnTrueIfCostIsHigherAfter2OptOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.updateSolution(instance, {4, 3, 2, 1, 0});

  bool res = BestImprovement2Opt(instance, solution);

  ASSERT_TRUE(res);
}

TEST(NoTest, ShouldSwapIfCostIsHigherAfter2OptOperation) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.updateSolution(instance, {4, 3, 2, 1, 0});

  BestImprovement2Opt(instance, solution);

  ASSERT_EQ(solution.getSolution()[0], 4);
  ASSERT_EQ(solution.getSolution()[1], 2);
  ASSERT_EQ(solution.getSolution()[2], 3);
  ASSERT_EQ(solution.getSolution()[3], 1);
  ASSERT_EQ(solution.getSolution()[4], 0);
}