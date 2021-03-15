#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "solution.h"

TEST(Solution, Correctness)
{
    std::vector<std::string> inputs = {"", "a", "aa", "aba", "aaaab"};
    std::vector<std::set<int>> outputs = {{}, {}, {0}, {1}, {0, 1}};
    for (int i = 0; i < inputs.size(); ++i)
    {
        auto rst = Solution(inputs[i]);
        EXPECT_EQ(rst, outputs[i]);
    }
}

