#include "Instance.hpp"
#include "Solution.hpp"
#include "gtest/gtest.h"

TEST(SolutionTest, ShouldCreateSolution) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.createSolution(instance);

  ASSERT_EQ(solution.getSolution().size(), 5);
}

TEST(SolutionTest, ShouldUseGreedyAlgorithmWhenCreateSolution) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.createSolution(instance);
  
  std::vector<size_t> sol = solution.getSolution();

  ASSERT_EQ(sol[0], 0);
  ASSERT_EQ(sol[1], 1);
  ASSERT_EQ(sol[2], 2);
  ASSERT_EQ(sol[3], 3);
  ASSERT_EQ(sol[4], 4);
}

TEST(SolutionTest, ShouldUseGreedyAlgorithmAndCorrectFeeWhenCreateSolution) {
  Instance instance("../instances/ex_instance");
  Solution solution;

  solution.createSolution(instance);

  ASSERT_EQ(solution.getSolutionFee(), 360);
}
