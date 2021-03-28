#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "solution.h"

TEST(shortest_integer_ratio_representation, correctness)
{
    EXPECT_EQ("0", solution(0, 1));
    EXPECT_EQ("3", solution(3, 1));
    EXPECT_EQ("2", solution(4, 2));
    EXPECT_EQ("2.5", solution(5, 2));
    EXPECT_EQ("0.75", solution(3, 4));
    EXPECT_EQ("1.1", solution(11, 10));
    EXPECT_EQ("0.(3)", solution(1, 3));
    EXPECT_EQ("0.1(6)", solution(1, 6));
    EXPECT_EQ("0.(142857)", solution(1, 7));
    EXPECT_EQ("0.10(714285)", solution(3, 28));
}

