#include <vector>
#include <algorithm>
#include <cstdio>

class Solution_1
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

class Solution_2
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

            auto comp1 = [&](const size_t &idx1, const size_t &idx2)
            {
                return nums[idx1] < nums[idx2];
            };
            std::sort(pos.begin(), pos.end(), comp1);

            auto comp2 = [&](int target, const size_t &idx)
            {
                return target < nums[idx];
            };
			auto bit = pos.cbegin();
			auto rit = std::upper_bound(pos.cbegin(), pos.cend(), target - nums[*bit], comp2);

			if (--rit <= bit) return rst;

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

template<class T>
void dumpVect(const std::vector<T> &vec)
{
	for (auto i : vec)
	{
		printf("%d ", i);
	}
	printf("\n");
}

int main()
{
	std::vector<int> nums {3,2,4};
	int target = 6;

	Solution_1 slu1;
	Solution_2 slu2;

	auto rst = slu1.twoSum(nums, target);
    dumpVect(rst);

	rst = slu2.twoSum(nums, target);
    dumpVect(rst);
}

