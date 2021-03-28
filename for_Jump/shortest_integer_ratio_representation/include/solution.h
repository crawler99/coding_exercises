#ifndef _FOR_JUMP_SHORTEST_INTEGER_RATIO_REPRESENTATION_SOLUTION_H_
#define _FOR_JUMP_SHORTEST_INTEGER_RATIO_REPRESENTATION_SOLUTION_H_

#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

/**
 * Problem: Given non-negative integer A and positive integer B, represent A/B as R.P(Q),
 *          where R is integral part, P is non-repeating fractional part and Q is repeating fractional part.
 *          For example, 2/1 = 2, 1/2 = 0.5, 1/3 = 0.(3), 1/6 = 0.1(6), 1/7 = 0.(142857), 3/28 = 0.10(714285)
 */

string solution(int A, int B)
{
    int integral = A / B;
    int residual = A % B;
    string result = to_string(integral);

    if (residual == 0)
    {
        return result;
    }

    unordered_map<int, int> residual_map;
    string fractional;
    int rem = residual % B;
    while ((rem != 0) && (residual_map.find(rem) == residual_map.end()))
    {
        residual_map[rem] = fractional.length();
        rem *= 10;
        fractional += to_string(rem / B);
        rem = rem % B;
    }

    if (rem == 0)
    {
        return result + "." + fractional;
    }
    return result + "." + fractional.substr(0, residual_map[rem]) + "(" + fractional.substr(residual_map[rem]) + ")";
}

#endif
