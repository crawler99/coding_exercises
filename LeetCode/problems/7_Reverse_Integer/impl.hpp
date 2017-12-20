#include <limits>
#include <cmath>

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
class Solution1  /* poor performance */
{
public:
    int reverse(int n) // n is a 32-bit signed integer
    {
        int level = 0;
        int64_t limit = n < 0 ? std::numeric_limits<int32_t>::min() 
                              : std::numeric_limits<int32_t>::max();
        int64_t rst = do_reverse(n, level);
        return std::abs(rst) > std::abs(limit) ? 0 : rst;
    }

    int64_t do_reverse(int n, int &level)
    {
        int quotient = n / 10;
        int residual = n % 10;

        if (quotient == 0)
        {
            level = 1;
            return residual;
        }
        else
        {
            int left = do_reverse(quotient, level);
            level *= 10;
            return int64_t(residual) * level + left;
        }
    }
};

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
class Solution2  /* this solution doesn't use any wider or promoted integer type, e.g. int64_t */
{
public:
    int reverse(int x)
    {
        int ret = 0;
        while (x != 0)
        {
            if (abs(ret) > 214748364)
            {
                return 0;
            }
            ret = ret * 10 + x % 10;
            x /= 10;
        }
        return ret;
    }
};
