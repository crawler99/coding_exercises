#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <queue>

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
class Solution_1 /* Not fully meet the complexity requirement, slow */
{
    public:
        double findMedianSortedArrays(const std::vector<int> &nums1, const std::vector<int> &nums2)
        {
            size_t nums { nums1.size() + nums2.size() };
            if (nums == 0) return 0.0;
            bool isEven { nums % 2 == 0 };

            auto *p1 = &nums1, *p2 = &nums2; // p1 always for target, and p2 always for base
            auto baseIt = p2->begin(), targetIt = p1->begin();
            size_t medianHIdx { nums / 2 + 1 }, ctr { 0 };
            int gap = medianHIdx - ctr;

            while (gap > 0)
            {
                if (baseIt == p2->end())
                {
                    targetIt += (gap - 1);
                    return (isEven ? (*targetIt + *(targetIt - 1)) / 2.0 : *targetIt);
                }
                else if (targetIt == p1->end())
                {
                    baseIt += (gap - 1);
                    return (isEven ? (*baseIt + (gap > 1 ? *(baseIt - 1) : *(targetIt - 1))) / 2.0 : *baseIt);
                }
                else
                {
                    auto oldTargetIt = targetIt;
                    targetIt = std::upper_bound(oldTargetIt, p1->end(), *baseIt);
                    ctr += (targetIt - oldTargetIt) + 1; // count in *baseIt
                }
                gap = medianHIdx - ctr;
                if (gap <= 0) break;

                std::swap(p1, p2);
                std::swap(++baseIt, targetIt);
            }

            targetIt -= (- gap + 1);
            if (gap == 0)
            {
                return (isEven ? (*targetIt + *baseIt) / 2.0 : *baseIt);
            }
            else
            {
                return (isEven ? (*targetIt + *(targetIt + 1)) / 2.0 : *(targetIt + 1));
            }
        }
};

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
class Solution_2 /* Call "find k'th element" twice, meet the complexity requirement */
{
    public:
        double findMedianSortedArrays(const std::vector<int> &nums1, const std::vector<int> &nums2)
        {
            auto m = nums1.size(), n = nums2.size();
            if ((m + n)&1)
                return findKthSortedArrays(nums1.begin(), m, nums2.begin(), n, (n + m) / 2 + 1);
            else
                return (findKthSortedArrays(nums1.begin(), m, nums2.begin(), n, (n + m) / 2 + 1) +
                        findKthSortedArrays(nums1.begin(), m, nums2.begin(), n, (n + m) / 2)) / 2.0;
        }

    private:
        double findKthSortedArrays(std::vector<int>::const_iterator it1, int m,
                                   std::vector<int>::const_iterator it2, int n,
                                   int k)
        {
            if (m > n)
                return findKthSortedArrays(it2, n, it1, m, k);
            if (m == 0)
                return *(it2 + k - 1);
            if (k == 1)
                return std::min(*it1, *it2);

            int pa = std::min(k / 2, m), pb = k - pa;
            if (*(it1 + pa - 1) < *(it2 + pb - 1))
                return findKthSortedArrays(it1 + pa, m - pa, it2, n, k - pa);
            else if (*(it1 + pa - 1) > *(it2 + pb - 1))
                return findKthSortedArrays(it1, m, it2 + pb, n - pb, k - pb);
            else
                return *(it1 + pa - 1);
        }
};

