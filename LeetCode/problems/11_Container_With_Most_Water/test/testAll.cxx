#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "impl.hpp"

TEST(Correctness, SimpleInput)
{
    Solution1 s1;
    Solution2 s2;

    std::vector<int> vect {1,1};
    EXPECT_EQ(1, s1.maxArea(vect));
    EXPECT_EQ(1, s2.maxArea(vect));

    vect = {1,2,3};
    EXPECT_EQ(2, s1.maxArea(vect));
    EXPECT_EQ(2, s2.maxArea(vect));

    vect = {3,2,1,3};
    EXPECT_EQ(9, s1.maxArea(vect));
    EXPECT_EQ(9, s2.maxArea(vect));
}

