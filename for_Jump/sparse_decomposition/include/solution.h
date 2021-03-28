#ifndef _FOR_JUMP_SHORTEST_INTEGER_RATIO_REPRESENTATION_SOLUTION_H_
#define _FOR_JUMP_SHORTEST_INTEGER_RATIO_REPRESENTATION_SOLUTION_H_

#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

/**
 * Problem: A non-negative integer is called sparse if its binary-representation has no consecutive 1.
 *          If non-negative integers N, P, Q meet the following conditions:
 *             1. N = P + Q
 *             2. P and Q are both sparse intergers.
 *          we call it a sparse decomposition of N.
 *          Given an non-negative integer N, return P or Q or -1(no sparse decomposition can be found).
 */

/*
// Solution1 O(N)
bool IsSparse(unsigned int n)
{
    int count = 0;
    while (n != 0)
    {
        // This operation reduces length of every sequence of 1s by one.
        n = (n & (n << 1));
        if (++count > 1)
        {
            return false;
        }
    }
    return true;
}

int solution(int N)
{
    if (N < 0)
    {
        return -1;
    }

    for (int i = 0; i <= N / 2; ++i)
    {
        if (IsSparse(i) && IsSparse(N - i))
        {
            return i;
        }
    }
    return -1;
}
*/

/*
// Solution2 O(Log(N))
int solution(int N)
{
    if (N < 0)
    {
        return -1;
    }

    unsigned int n = N;
    int ret = 0;
    int left_bit_mask = 0x80000000;
    int last_bit = 0;
    for (unsigned int i = 0; i < 8 * sizeof(n); ++i)
    {
        int cur_left = (n & left_bit_mask) >> 31;
        ret = ret << 1;
        if (cur_left == 1 && last_bit == 0)
        {
            ret += 1;
            last_bit = cur_left;
        }
        else
        {
            last_bit = 0;
        }
        n = n << 1;
    }
    return ret;
}
*/

// Solution3 O(1)
int solution(int N)
{
    if (N < 0)
    {
        return -1;
    }

    return N & 0xAAAAAAAA;
}

#endif
