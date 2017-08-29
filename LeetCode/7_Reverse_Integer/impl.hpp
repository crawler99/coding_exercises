//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
class Solution
{
public:
    int reverse(int n) // n is a 32-bit signed integer
    {
        int level = 0;
        return do_reverse(n, level);
    }

    int do_reverse(int n, int &level)
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
            return (residual * level) + left;
        }
    }
};
