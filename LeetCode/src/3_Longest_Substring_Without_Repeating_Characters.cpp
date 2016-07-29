#include <cstdio>
#include <string>
#include <cstring>
#include <vector>

class Solution_1
{
    public:
        int lengthOfLongestSubstring(std::string s)
        {
            if (s.empty()) return 0;

            std::vector<int> pMap(256, -1);

            int idx1 = 0;
            int idx2 = 0;
            int max = 1;
            pMap[s[idx1]] = 0;

            while (true)
            {
                while ((++idx2 < s.size()) && (-1 == pMap[s[idx2]]))
                {
                    pMap[s[idx2]] = idx2;
                }
                max = std::max(max, idx2 - idx1);
                if (idx2 < s.size())
                {
                    do
                    {
                        pMap[s[idx1]] = -1;
                    } while (++idx1 <= pMap[s[idx2]]);
                    pMap[s[idx2]] = idx2;
                }
                else
                {
                    return max;
                }
            }
        }
};

int main()
{
    std::string testStr("abcabcbb");

    Solution_1 slu1;
    printf("Result: %d\n", slu1.lengthOfLongestSubstring(testStr));

    return 0;
}

