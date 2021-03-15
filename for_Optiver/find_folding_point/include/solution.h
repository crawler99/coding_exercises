#pragma once

#include <set>
#include <vector>

/**
 * Problem: Given a string, find all the char indexes where if you fold the string from one of these indexes, the shorter side totally overlaps
 *          the longer side. For example:
 *   "" => {}
 *   "a" => {}
 *   "aa" =>  {0}
 *   "aba" => {1}
 *   "aaaab" => {0, 1, 2}
 */

void ExpandAroundCenter(const std::string &s, int leftIdx, int rightIdx, std::set<int> &rstIdxes)
{
    int L = leftIdx;
    int R = rightIdx;
    int extended = 0;
    while((L >= 0) && (R < s.size()) && (s[L] == s[R]))
    {
        --L;
        ++R;
        ++extended;
    }
    if ((L < 0 || R >= s.size()) && ((leftIdx != rightIdx) || (extended > 1)))
    {
        rstIdxes.insert(leftIdx);
    }
}

std::set<int> Solution(const std::string &s)
{
    if (s.size() <= 1) return {};

    std::set<int> rst;
    for (int i = 0; i < s.size() - 1; ++i)
    {
        ExpandAroundCenter(s, i, i, rst);
        ExpandAroundCenter(s, i, i + 1, rst);
    }
    return rst;
}
