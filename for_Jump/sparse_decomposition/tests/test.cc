#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "solution.h"

TEST(sparse_decomposition, correctness)
{
    EXPECT_EQ(solution(26), 10);
    EXPECT_EQ(solution(346), 10);
    EXPECT_EQ(solution(14), 10);
    EXPECT_EQ(solution(12345), 8232);
}

