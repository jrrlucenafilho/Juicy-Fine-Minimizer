#include "Instance.hpp"
#include <gtest/gtest.h>

TEST(InstanceTest, InitializeInstanceFromFile) {
  Instance instance("../instances/ex_instance");

  ASSERT_TRUE(instance.isInstanceLoaded());
}

TEST(InstanceTest, InitializeLoadProductionTimesCorrectly) {
  Instance instance("../instances/ex_instance");

  ASSERT_EQ(instance.getProductionTime(0), 15);
  ASSERT_EQ(instance.getProductionTime(1), 25);
  ASSERT_EQ(instance.getProductionTime(2), 20);
  ASSERT_EQ(instance.getProductionTime(3), 30);
  ASSERT_EQ(instance.getProductionTime(4), 20);
}

TEST(InstanceTest, InitializeDeliveryTimeLimitsCorrectly) {
  Instance instance("../instances/ex_instance");

  ASSERT_EQ(instance.getDeliveryTimeLimit(0), 25);
  ASSERT_EQ(instance.getDeliveryTimeLimit(1), 45);
  ASSERT_EQ(instance.getDeliveryTimeLimit(2), 75);
  ASSERT_EQ(instance.getDeliveryTimeLimit(3), 120);
  ASSERT_EQ(instance.getDeliveryTimeLimit(4), 135);
}

TEST(InstanceTest, InitializeLateFeesCorrectly) {
  Instance instance("../instances/ex_instance");

  ASSERT_FLOAT_EQ(instance.getLateFee(0), 0.1);
  ASSERT_FLOAT_EQ(instance.getLateFee(1), 0.12);
  ASSERT_FLOAT_EQ(instance.getLateFee(2), 0.3);
  ASSERT_FLOAT_EQ(instance.getLateFee(3), 0.15);
  ASSERT_FLOAT_EQ(instance.getLateFee(4), 0.1);
}

TEST(InstanceTest, InitializeTransitionTimesCorrectly) {
  Instance instance("../instances/ex_instance");

  ASSERT_EQ(instance.getTransitionTime(0, 0), 0);
  ASSERT_EQ(instance.getTransitionTime(0, 1), 10);
  ASSERT_EQ(instance.getTransitionTime(0, 2), 15);
  ASSERT_EQ(instance.getTransitionTime(0, 3), 8);
  ASSERT_EQ(instance.getTransitionTime(0, 4), 21);

  ASSERT_EQ(instance.getTransitionTime(1, 0), 10);
  ASSERT_EQ(instance.getTransitionTime(1, 1), 0);
  ASSERT_EQ(instance.getTransitionTime(1, 2), 10);
  ASSERT_EQ(instance.getTransitionTime(1, 3), 13);
  ASSERT_EQ(instance.getTransitionTime(1, 4), 9);

  ASSERT_EQ(instance.getTransitionTime(2, 0), 17);
  ASSERT_EQ(instance.getTransitionTime(2, 1), 9);
  ASSERT_EQ(instance.getTransitionTime(2, 2), 0);
  ASSERT_EQ(instance.getTransitionTime(2, 3), 10);
  ASSERT_EQ(instance.getTransitionTime(2, 4), 14);

  ASSERT_EQ(instance.getTransitionTime(3, 0), 11);
  ASSERT_EQ(instance.getTransitionTime(3, 1), 13);
  ASSERT_EQ(instance.getTransitionTime(3, 2), 12);
  ASSERT_EQ(instance.getTransitionTime(3, 3), 0);
  ASSERT_EQ(instance.getTransitionTime(3, 4), 10);

  ASSERT_EQ(instance.getTransitionTime(4, 0), 5);
  ASSERT_EQ(instance.getTransitionTime(4, 1), 10);
  ASSERT_EQ(instance.getTransitionTime(4, 2), 15);
  ASSERT_EQ(instance.getTransitionTime(4, 3), 20);
  ASSERT_EQ(instance.getTransitionTime(4, 4), 0);
}
