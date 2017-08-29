#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "impl.hpp"

TEST(Correctness, SimpleInput)
{
    Solution s;

    EXPECT_EQ(321, s.reverse(123));
    EXPECT_EQ(-321, s.reverse(-123));
    EXPECT_EQ(301, s.reverse(103));
    EXPECT_EQ(-301, s.reverse(-103));
    EXPECT_EQ(3, s.reverse(300));
    EXPECT_EQ(-3, s.reverse(-300));
}

