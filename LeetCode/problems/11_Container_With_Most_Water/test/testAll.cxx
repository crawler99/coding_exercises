#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "impl.hpp"

TEST(Correctness, SimpleInput)
{
    Solution s;

    std::vector<int> vect {1,1};
    // EXPECT_EQ(1, s.maxArea(vect));
    vect = {1,2,3};
    // EXPECT_EQ(2, s.maxArea(vect));
    vect = {3,2,1,3};
    EXPECT_EQ(9, s.maxArea(vect));
}

