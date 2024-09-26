#include "calc/basic.h"
#include <gtest/gtest.h>

TEST(CalcTest, SumAddsTwoInts) {
  EXPECT_EQ(4, Calc::Add(2, 2));
}

TEST(CalcTest, SubtractsTwoInts) {
  EXPECT_EQ(6, Calc::Subtract(8, 2));
}
