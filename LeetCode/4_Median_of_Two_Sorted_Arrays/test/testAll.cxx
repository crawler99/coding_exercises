#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "impl.hpp"

TEST(Correctness, SimpleInput)
{
    std::vector<int> nums1 {1, 2};
    std::vector<int> nums2 {3, 4};

    std::vector<int> nums3 {1, 3, 10, 15};
    std::vector<int> nums4 {2, 12};

    std::vector<int> nums5 {};
    std::vector<int> nums6 {1};

    std::vector<int> nums7 {1, 2};
    std::vector<int> nums8 {3, 5, 10, 20, 40};

    std::vector<int> nums9 {1};
    std::vector<int> nums10 {1};

    std::vector<int> nums11 {1, 2};
    std::vector<int> nums12 {1, 2, 3};

    std::vector<int> nums13 {100001};
    std::vector<int> nums14 {100000};

    std::vector<int> nums15 {1};
    std::vector<int> nums16 {2, 3, 4};

    Solution_2 slu;
    printf("Median1: %f\n", slu.findMedianSortedArrays(nums1, nums2));
    printf("Median2: %f\n", slu.findMedianSortedArrays(nums3, nums4));
    printf("Median3: %f\n", slu.findMedianSortedArrays(nums5, nums6));
    printf("Median4: %f\n", slu.findMedianSortedArrays(nums7, nums8));
    printf("Median5: %f\n", slu.findMedianSortedArrays(nums9, nums10));
    printf("Median6: %f\n", slu.findMedianSortedArrays(nums11, nums12));
    printf("Median7: %f\n", slu.findMedianSortedArrays(nums13, nums14));
    printf("Median8: %f\n", slu.findMedianSortedArrays(nums15, nums16));
}

