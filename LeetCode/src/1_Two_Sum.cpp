#include <vector>
#include <algorithm>
#include <cstdio>
#include <unordered_map>

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

class Solution_3
{
    public:
        std::vector<int> twoSum(std::vector<int>& nums, int target)
        {
            std::vector<int> rst;

            if (nums.size() > 1)
            {
                std::unordered_map<int, size_t> hashMap;

                for (size_t i = 0; i < nums.size(); ++i)
                {
                    hashMap[nums[i]] = i;
                }

                for (size_t i = 0; i < nums.size(); ++i)
                {
                    auto it = hashMap.find(target - nums[i]);
                    if (it != hashMap.end())
                    {
                        if (it->second != i)
                        {
                            rst.push_back(i);
                            rst.push_back(it->second);
                            break;
                        }
                    }
                }
            }

            return rst;
        }
};

class Solution_4
{
    public:
        std::vector<int> twoSum(std::vector<int>& nums, int target)
        {
            std::vector<int> rst;

            if (nums.size() > 1)
            {
                std::unordered_map<int, size_t> hashMap;

                for (size_t i = 0; i < nums.size(); ++i)
                {
                    auto it = hashMap.find(target - nums[i]);
                    if (it != hashMap.end())
                    {
                        if (it->second != i)
                        {
                            rst.push_back(it->second);
                            rst.push_back(i);
                            break;
                        }
                    }
                    hashMap[nums[i]] = i;
                }
            }

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
}

