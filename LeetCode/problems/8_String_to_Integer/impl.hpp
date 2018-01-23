#include <string>
#include <climits>

class Solution1
{
public:
    int myAtoi(std::string str)
    {
	unsigned long num { 0 };
	if (!str.empty())
        {
		auto cit = str.cbegin();
                while(*cit == ' ' ) ++cit;
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

class Solution2
{
public:
    int myAtoi(std::string str)
    {
	return 0;
    }
};

