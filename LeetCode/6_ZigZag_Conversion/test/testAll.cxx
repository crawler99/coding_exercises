#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "impl.hpp"

TEST(Correctness, SimpleInput)
{
    Solution s;

    EXPECT_EQ("PAHNAPLSIIGYIR", s.convert("PAYPALISHIRING", 3));
    EXPECT_EQ("PINALSIGYAHRPI", s.convert("PAYPALISHIRING", 4));
    EXPECT_EQ("", s.convert("", 1));
    EXPECT_EQ("", s.convert("", 3));
    EXPECT_EQ("A", s.convert("A", 1));
    EXPECT_EQ("AB", s.convert("AB", 1));
    EXPECT_EQ("ABDC", s.convert("ABCD", 3));
}

