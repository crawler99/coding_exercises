#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "impl.hpp"

TEST(Correctness, SimpleInput)
{
    Solution s;

    EXPECT_EQ("PAHNAPLSIIGYIR", s.convert("PAYPALISHIRING", 3));
    EXPECT_EQ("PINALSIGYAHRPI", s.convert("PAYPALISHIRING", 4));
}

