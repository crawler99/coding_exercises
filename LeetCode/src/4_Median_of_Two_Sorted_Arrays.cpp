#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <queue>

class Solution_1
{
    public:
        double findMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2)
        {
            size_t nums { nums1.size() + nums2.size() }, medianHIdx { nums / 2 + 1 };
            if (nums == 0) return 0.0;
            bool isEven { nums % 2 == 0 };

            auto *p1 = &nums1, *p2 = &nums2; // p1 always for target, and p2 always for base
            auto baseIt = p2->begin(), targetIt = p1->begin();
            size_t ctr { 0 };
            int exceed  = ctr - medianHIdx;

            while ((baseIt != p2->end()) && (targetIt != p1->end()))
            {
                auto oldTargetIt = targetIt;

                printf("Trying to find a number no less than %d ...\n", *baseIt);

                targetIt = std::lower_bound(oldTargetIt, p1->end(), *baseIt);
                ctr += (targetIt - oldTargetIt) + 1; // count in only *baseIt

                printf("Ctr becomes %d while medianHIdx is %d\n", ctr, medianHIdx);

                exceed = ctr - medianHIdx;
                if (exceed >= 0) break;

                std::swap(p1, p2);
                std::swap(++baseIt, targetIt);
            }

            if (baseIt == p2->end()) { while (exceed < 0) { ++targetIt; ++exceed; } }
            if (targetIt == p1->end()) { while (exceed < 0) { ++baseIt; ++exceed; } }

            printf("Ctr exceeds higher median idx, step back taregetIt by %d steps ...\n", exceed + 1);
            targetIt -= (exceed + 1);
            if (exceed == 0)
            {
                return (isEven ? (*targetIt + *baseIt) / 2.0 : *baseIt);
            }
            else
            {
                return (isEven ? (*targetIt + *(targetIt + 1)) / 2.0 : *targetIt);
            }
        }
};

class Solution_2 /* Slow and can't meet the complexity requirement */
{
    public:
        double findMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2)
        {
            size_t nums { nums1.size() + nums2.size() }, medianHIdx { nums / 2 + 1 }, ctr { 0 };
            if (nums == 0) return 0.0;
            bool isEven { nums % 2 == 0 };

            std::priority_queue<int> pq;
            auto it1 = nums1.cbegin(), it2 = nums2.cbegin(), ite1 = nums1.cend(), ite2 = nums2.cend();
            for (; ctr < medianHIdx; ++ctr)
            {
                if (it1 == ite1) pq.emplace(*(it2++));
                else if (it2 == ite2) pq.emplace(*(it1++));
                else if (*it1 < *it2) pq.emplace(*(it1++));
                else pq.emplace(*(it2++));
            }

            auto top = pq.top();
            if (!isEven) return top;
            pq.pop();
            return (top + pq.top()) / 2.0;
        }
};

int main()
{
    std::vector<int> nums1 {1, 2};
    std::vector<int> nums2 {3, 4};

    std::vector<int> nums3 {1, 3, 10, 15};
    std::vector<int> nums4 {2, 12};

    std::vector<int> nums5 {};
    std::vector<int> nums6 {1};

    std::vector<int> nums7 {1, 2};
    std::vector<int> nums8 {3, 5, 10, 20, 40};

    Solution_1 slu;
    printf("Median: %f\n", slu.findMedianSortedArrays(nums1, nums2));
    printf("Median: %f\n", slu.findMedianSortedArrays(nums3, nums4));
    printf("Median: %f\n", slu.findMedianSortedArrays(nums5, nums6));
    printf("Median: %f\n", slu.findMedianSortedArrays(nums7, nums8));

    return 0;
}

