#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "impl.hpp"

template <typename Solution>
void TestCorrectness()
{
    Solution s;

    EXPECT_EQ(0, s.myAtoi(""));
    EXPECT_EQ(0, s.myAtoi("ab123"));
    EXPECT_EQ(0, s.myAtoi("- 123"));

    EXPECT_EQ(123, s.myAtoi("123"));
    EXPECT_EQ(123, s.myAtoi("0123"));
    EXPECT_EQ(123, s.myAtoi("  +0123"));
    EXPECT_EQ(123, s.myAtoi("  0123"));
    EXPECT_EQ(123, s.myAtoi("  +123"));
    EXPECT_EQ(123, s.myAtoi("123.5"));
    EXPECT_EQ(-12, s.myAtoi("  -0012a42"));
    EXPECT_EQ(-123, s.myAtoi(" -123"));
    EXPECT_EQ(-123, s.myAtoi(" -0123"));
    EXPECT_EQ(-123, s.myAtoi(" -0123"));
    EXPECT_EQ(0, s.myAtoi("+0"));
    EXPECT_EQ(0, s.myAtoi("-0"));
    EXPECT_EQ(-2147483648, s.myAtoi("-2147483648"));
    EXPECT_EQ(2147483647, s.myAtoi("2147483648"));
    EXPECT_EQ(2147483647, s.myAtoi("    10522545459"));
}

TEST(Correctness, Solution1)
{
    TestCorrectness<Solution1>();
}

TEST(Correctness, Solution2)
{
    TestCorrectness<Solution2>();
}

