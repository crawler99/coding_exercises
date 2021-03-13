#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "solution.h"

TEST(Solution, Correctness)
{
    vector<int> vect = { 0,0,0 };
    printf("solution = %d\n", solution(vect));
    EXPECT_EQ(0, solution(vect));
	vect = { 0,0,0,1,1 };
    printf("solution = %d\n", solution(vect));
    EXPECT_EQ(1, solution(vect));
	vect = { 7,6,5,4,3,2,1,-1 };
    printf("solution = %d\n", solution(vect));
    EXPECT_EQ(4, solution(vect));
    printf("solution = %d\n", solution(vect));
	vect = { 1,1,1,-1,1,1,1,0 };
    EXPECT_EQ(0, solution(vect));
}

