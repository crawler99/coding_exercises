#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "impl.hpp"

TEST(Correctness, SimpleInput)
{
    Solution s;

    ASSERT_EQ("bab", s.longestPalindrome("babad"));
    ASSERT_EQ("bb", s.longestPalindrome("cbbd"));
    ASSERT_EQ("bb", s.longestPalindrome("bb"));
    ASSERT_EQ("ccc", s.longestPalindrome("ccc"));
    ASSERT_EQ("a", s.longestPalindrome("a"));
    ASSERT_EQ("a", s.longestPalindrome("abc"));
    ASSERT_EQ("", s.longestPalindrome(""));
}

