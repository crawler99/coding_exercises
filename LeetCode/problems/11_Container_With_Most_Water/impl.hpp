#include <vector>
#include <algorithm>

class Solution1  /* Original soluition, beat ony 19% */
{
public:
    int maxArea(std::vector<int>& height)
    {
	int maxArea {0};
	for (int i = 0; static_cast<size_t>(i) < height.size() - 1; ++i)
	{
	    if (i > 0 && height[i] <= height[i-1]) 
            {
                continue;
            }
            int highestRightEdge {0};
	    for (int j = height.size() - 1; j > i; --j)
            {
		if (height[j] >= height[i])
                {
                    maxArea = std::max(maxArea, height[i] * (j - i));
                    break;
                }
                if (height[j] > highestRightEdge)
                {
                    highestRightEdge = height[j];
                    maxArea = std::max(maxArea, highestRightEdge * (j - i));
                }
            }
	}
        return maxArea;
    }
};

class Solution2  /* Posted solution on LeetCode, better than Solution1 but still beat only 23% */
{
public:
     int maxArea(std::vector<int>& height) 
     {
        int maxArea = 0, l = 0, r = height.size() - 1;
        while (l < r) 
        {
            maxArea = std::max(maxArea, std::min(height[l], height[r]) * (r - l));
            if (height[l] < height[r])
            {
                ++l;
            }
            else
            {
                --r;
            }
        }
        return maxArea;
    }
};
