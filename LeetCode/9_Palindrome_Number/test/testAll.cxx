#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "impl.hpp"

TEST(Correctness, SimpleInput)
{
    Solution s;

    EXPECT_TRUE(false == s.isPalindrome(-2147483648));
    EXPECT_TRUE(false == s.isPalindrome(-1));
    EXPECT_TRUE(true == s.isPalindrome(0));
    EXPECT_TRUE(true == s.isPalindrome(1934554391));
}

