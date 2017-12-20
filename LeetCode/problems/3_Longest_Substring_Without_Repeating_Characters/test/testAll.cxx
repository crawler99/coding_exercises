#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "impl.hpp"

TEST(Correctness, SimpleInput)
{
    std::string testStr("c");

    Solution_1 slu1;
    EXPECT_EQ(1, slu1.lengthOfLongestSubstring(testStr));

    Solution_2 slu2;
    EXPECT_EQ(1, slu2.lengthOfLongestSubstring(testStr));
}

