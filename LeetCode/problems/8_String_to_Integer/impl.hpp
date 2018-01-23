#include <string>
#include <climits>

class Solution1  /* beat ony 20% */
{
public:
    int myAtoi(std::string str)
    {
        unsigned long num { 0 };
        if (!str.empty())
        {
            auto cit = str.cbegin();
            while(cit != str.cend() && *cit == ' ' ) ++cit;
            if (cit != str.cend())
            {
                bool negative { false };
                switch (*cit)
                {
                    case '-':
                        negative = true;
                    case '+':
                        ++cit;
                        break;
                    default:
                        ;
                }

                while ((cit != str.cend()) && (*cit >= '0') && (*cit <= '9'))
                {
                    num = (10 * num + (*cit - '0'));
                    if (!negative && (num > INT_MAX))
                    {
                        return INT_MAX;
                    }
                    if (negative && (num > 0) && (num -1 > INT_MAX))
                    {
                        return INT_MIN;
                    }
                    ++cit;
                }

                if (negative) num *= -1;
            }
        }
        return static_cast<int>(num);
    }
};

class Solution2 /* beat 55% */
{
public:
    int myAtoi(std::string str)
    {
        int maxDiv10 { INT_MAX / 10 };
        int num = 0, sign = 1;

        size_t i = 0, n = str.size();
        while((i < n) && str[i] == ' ' ) ++i;

        if (i < n)
        {
            switch (str[i])
            {
                case '-':
                    sign = -1;
                case '+':
                    ++i;
                    break;
                defaule:
                    ;
            }

            while (i < n && (str[i] >= '0' && str[i] <= '9'))
            {
                int digit = str[i] - '0';
                if (num > maxDiv10 || (num == maxDiv10 && digit >= 8))
                {
                    return sign == 1 ? INT_MAX : INT_MIN;
                }
                num = num * 10 + digit;
                ++i;
            }
        }
        return sign * num;
    }
};

