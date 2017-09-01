#include <limits>
#include <cmath>
#include <string>

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
class Solution
{
public:
    std::string convert(std::string s, int numRows) 
    {
	std::string rst;

        int divider = numRows > 1 ? (2 * (numRows - 1)) : 1;
        int numVerticalCols = ceil(double(s.size()) / divider);

	auto appendChar = [&s,&rst](int idx)
        {
            if ((idx >=0) && (idx < s.size()))
            {
                rst.push_back(s[idx]);
            }
        };

        for (int i = 0; i < numRows; ++i)
        {
            for (int j = 0; j <= numVerticalCols; ++j)
            {
                int idx1 = j * divider;
                int idx0 = idx1 - i;
                int idx2 = idx1 + i;
                if ((i > 0) && (i < numRows - 1))
                {
                    appendChar(idx0);
                }
                appendChar(idx2);
            }
        }

        return rst;
    }
};
