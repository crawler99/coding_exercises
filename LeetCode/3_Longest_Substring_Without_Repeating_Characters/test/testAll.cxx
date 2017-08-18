#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "impl.hpp"

TEST(Correctness, SimpleInput)
{
    std::string testStr("c");

    Solution_1 slu1;
    printf("Result: %d\n", slu1.lengthOfLongestSubstring(testStr));

    Solution_2 slu2;
    printf("Result: %d\n", slu2.lengthOfLongestSubstring(testStr));
}

