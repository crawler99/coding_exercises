#include <vector>
#include <algorithm>

class Solution
{
    public:
        std::vector<int> twoSum(std::vector<int>& nums, int target)
        {
            std::vector<int> rst;

            if (nums.size() < 2) return rst;

            std::vector<int> pos;
            for (size_t i = 0; i < nums.size(); ++i)
            {
                pos.push_back(i);
            }

            std::sort(pos.begin(), pos.end(), [&](const size_t &idx1, const size_t &idx2)
                    {
                        return nums[idx1] < nums[idx2];
                    });

            auto bit = pos.cbegin();
            auto rit = --pos.cend();

            while (bit != rit)
            {
                auto sum = nums[*bit] + nums[*rit];
                if (sum < target) ++bit;
                else if (sum > target) --rit;
                else
                {
                    rst.push_back(*bit);
                    rst.push_back(*rit);
                    break;
                }
            }

            std::sort(rst.begin(), rst.end());
            return rst;
        }
};
