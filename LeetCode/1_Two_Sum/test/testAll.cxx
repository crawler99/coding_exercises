#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "impl.hpp"

TEST(Correctness, SimpleInput)
{
    std::vector<int> nums {3,2,4};
    int target = 6;

    Solution_1 slu1;
    Solution_2 slu2;
    Solution_3 slu3;
    Solution_4 slu4;

    auto rst = slu1.twoSum(nums, target);
    dumpVect(rst);

    rst = slu2.twoSum(nums, target);
    dumpVect(rst);

    rst = slu3.twoSum(nums, target);
    dumpVect(rst);

    rst = slu4.twoSum(nums, target);
    dumpVect(rst);


/*
  EXPECT_CALL(application, _ApplicationName())
    .Times(AtLeast(1));

  try {
    // constructors
    rsEventTimestampDynLoc loc, loc2(1234);

    // copy constructor
    ASSERT_NO_THROW(rsEventTimestampDynLoc loc3 = loc);
    // assignment
    ASSERT_NO_THROW(loc2 = loc);

  }
  catch(std::exception const & bad) {
    FAIL() << "Exception unexpected: " << bad.what();
  }
*/
}

