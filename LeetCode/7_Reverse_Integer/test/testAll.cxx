#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "impl.hpp"

TEST(Correctness, SimpleInput)
{
    Solution1 s1;
    Solution2 s2;

    EXPECT_EQ(321, s1.reverse(123));
    EXPECT_EQ(321, s2.reverse(123));
    EXPECT_EQ(-321, s1.reverse(-123));
    EXPECT_EQ(-321, s2.reverse(-123));

    EXPECT_EQ(301, s1.reverse(103));
    EXPECT_EQ(301, s2.reverse(103));
    EXPECT_EQ(-301, s1.reverse(-103));
    EXPECT_EQ(-301, s2.reverse(-103));

    EXPECT_EQ(3, s1.reverse(300));
    EXPECT_EQ(3, s2.reverse(300));
    EXPECT_EQ(-3, s1.reverse(-300));
    EXPECT_EQ(-3, s2.reverse(-300));

    EXPECT_EQ(0, s1.reverse(2147483647));
    EXPECT_EQ(0, s2.reverse(2147483647));
}

