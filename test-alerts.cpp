
#include "typewise-alert.h"

#include "gtest/gtest.h"

TEST(TypewiseAlert, InferBreachAsPerLimits) {
  ASSERT_TRUE(inferBreach(12.0, 20.0, 30.0) == TOO_LOW);
}
