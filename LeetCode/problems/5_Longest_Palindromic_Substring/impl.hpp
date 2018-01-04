#include <string>
#include <iostream>

class Solution 
{
public:
    void findPalindromeLen(size_t leftIdx, size_t rightIdx, const std::string &s, size_t &leftMost, size_t &rightMost)
    {
        while((s[leftIdx] == s[rightIdx]) && (leftIdx >= 0) && (rightIdx < s.size()))
        {
            --leftIdx;
            ++rightIdx;
        }
        leftMost = ++leftIdx;
        rightMost = --rightIdx;
    }

    std::string longestPalindrome(std::string s) 
    {
        switch(s.size())
        {
            case 0: 
                return "";
            case 1:
                return &s[0];
            default:
                size_t l {0}, r {0}, finalL {0};
                size_t maxLen {0};
                for (size_t i = 1; i < s.size(); ++i)
                {
                    if (s[i] == s[i-1])
                    {
                        findPalindromeLen(i-1, i, s, l, r);
                    }

                    if (r -l + 1 > maxLen)
                    {
                        maxLen = r - l + 1;
                        finalL = l;
                    }

                    if (i > 1 && (s[i] == s[i - 2]))
                    {
                        findPalindromeLen(i-2, i, s, l, r);
                    }

                    if (r -l + 1 > maxLen)
                    {
                        maxLen = r - l + 1;
                        finalL = l;
                    }
                }
                return s.substr(finalL, maxLen);
        }
    }
};

