#ifndef _FOR_SIG_SOLUTION_H_
#define _FOR_SIG_SOLUTION_H_

#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>

using namespace std;

/**
 * Problem: Find the cheapest way to divide an integer sequence to three non-adjacent sub-sequences.
 *          For example, divide A to A[0],...A[p],....,A[q],..,A[last] where A[p] + A[q] is minimum.
 */

// Brute-force.
int solution(vector<int> &A)
{
    if (A.size() < 5)
    {
        return 0; // cannot divide as requested.
    }

    int min_sum{INT_MAX};
    for (size_t i = 1; i < A.size() - 3; ++i)
    {
        for (size_t j = A.size() - 2; j > i + 1; --j)
        {
            min_sum = std::min(A[i] + A[j], min_sum);
        }
    }
    return min_sum;
}

// Find the smallest 3 numbers.
int insert_sort(vector<int> &vect, vector<int> &A, int last_idx, int num_idx)
{
    if (last_idx == -1)
    {
        vect[++last_idx] = num_idx;
        return last_idx;
    }

    if (last_idx == 2 && A[vect[last_idx]] <= A[num_idx])
    {
        return last_idx;
    }

    int new_last_idx = last_idx + 1;
    if (new_last_idx > vect.size() - 1)
    {
        new_last_idx = vect.size() - 1;
    }

    while (last_idx >= 0 && A[vect[last_idx]] > A[num_idx])
    {
        if (last_idx < (vect.size() - 1))
        {
            vect[last_idx + 1] = vect[last_idx];
        }
        --last_idx;
    }
    vect[++last_idx] = num_idx;

    return new_last_idx;
}

int solution1(vector<int> &A)
{
    if (A.size() < 5)
    {
        return 0; // cannot divide as requested.
    }

    int last_idx = -1;
    vector<int> small_nums;
    small_nums.resize(3);
    for (size_t i = 1; i < A.size() - 1; ++i)
    {
        last_idx = insert_sort(small_nums, A, last_idx, i);
    }

    return abs(small_nums[1] - small_nums[0]) > 1 ? (A[small_nums[0]] + A[small_nums[1]])
        : abs(small_nums[2] - small_nums[0]) > 1 ? (A[small_nums[0]] + A[small_nums[2]])
        : (A[small_nums[1]] + A[small_nums[2]]);
}

#endif
