#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "impl.hpp"

TEST(Correctness, SimpleInput)
{
    Solution_1 slu1;
    Solution_2 slu2;

    EXPECT_EQ(2.5, slu1.findMedianSortedArrays({1,2}, {3,4}));
    EXPECT_EQ(2.5, slu2.findMedianSortedArrays({1,2}, {3,4}));

    std::vector<int> nums3 {1, 3, 10, 15};
    std::vector<int> nums4 {2, 12};
    EXPECT_EQ(6.5, slu1.findMedianSortedArrays({1,3,10,15}, {2,12}));
    EXPECT_EQ(6.5, slu2.findMedianSortedArrays({1,3,10,15}, {2,12}));

    std::vector<int> nums5 {};
    std::vector<int> nums6 {1};
    EXPECT_EQ(1, slu1.findMedianSortedArrays({}, {1}));
    EXPECT_EQ(1, slu2.findMedianSortedArrays({}, {1}));

    std::vector<int> nums7 {1, 2};
    std::vector<int> nums8 {3, 5, 10, 20, 40};
    EXPECT_EQ(5, slu1.findMedianSortedArrays({1,2}, {3,5,10,20,40}));
    EXPECT_EQ(5, slu2.findMedianSortedArrays({1,2}, {3,5,10,20,40}));

    std::vector<int> nums9 {1};
    std::vector<int> nums10 {1};
    EXPECT_EQ(1, slu1.findMedianSortedArrays({1}, {1}));
    EXPECT_EQ(1, slu2.findMedianSortedArrays({1}, {1}));

    std::vector<int> nums11 {1, 2};
    std::vector<int> nums12 {1, 2, 3};
    EXPECT_EQ(2, slu1.findMedianSortedArrays({1,2}, {1,2,3}));
    EXPECT_EQ(2, slu2.findMedianSortedArrays({1,2}, {1,2,3}));

    std::vector<int> nums13 {100001};
    std::vector<int> nums14 {100000};
    EXPECT_EQ(100000.5, slu1.findMedianSortedArrays({100001}, {100000}));
    EXPECT_EQ(100000.5, slu2.findMedianSortedArrays({100001}, {100000}));

    std::vector<int> nums15 {1};
    std::vector<int> nums16 {2, 3, 4};
    EXPECT_EQ(2.5, slu1.findMedianSortedArrays({1}, {2,3,4}));
    EXPECT_EQ(2.5, slu2.findMedianSortedArrays({1}, {2,3,4}));
}

